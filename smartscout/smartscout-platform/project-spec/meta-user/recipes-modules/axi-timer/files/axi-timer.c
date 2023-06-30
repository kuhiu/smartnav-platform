#include <linux/cdev.h>
#include <linux/of_platform.h>   
#include <linux/proc_fs.h>      
#include <linux/init.h>        
#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/kdev_t.h>
#include <linux/types.h>
#include <linux/fs.h>
#include <linux/of_gpio.h>
#include <linux/gpio.h>
#include <linux/ktime.h>
#include <linux/delay.h>
#include <linux/uaccess.h>                         
#include <linux/seq_file.h>   
#include <linux/platform_device.h>       
#include <linux/of.h>       

/* Standard module information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Fuschetto Martin. Email: marfus@hotmail.es");
MODULE_DESCRIPTION("axi-timer");

#define AXI_TIMER_IOC_NMAGICO 'v'
#define AXI_TIMER_IOC_NUM_MAX 1
#define AXI_TIMER_IOC_T_ON _IO(AXI_TIMER_IOC_NMAGICO, 1)

#define DEVICE_NAME "axi_timer_pwm"              
#define DEVICE_CLASS_NAME "axi_timer_pwm_class"

#define BASE_MINOR 0                                      
#define MAX_DEVICES 4     // Max number of the devices                                        
#define DEVICE_PARENT NULL

// Timer 0
#define OFFSET_TCSR0    0x00000000  // Control and Status Register
#define OFFSET_TLR0     0x00000004  // Load Register
#define OFFSET_TCR0     0x00000008  // Counter Register
// Timer 1
#define OFFSET_TCSR1    0x00000010  // Control and Status Register
#define OFFSET_TLR1     0x00000014  // Load Register
#define OFFSET_TCR1     0x00000018  // Counter Register

//#define DEBUG_AXI_TIMER 1
#if defined(DEBUG_AXI_TIMER) 
 	#define DEBUG_PRINT(fmt, args...) printk( "DEBUG: %s:%d:%s(): " fmt, \
																						__FILE__, __LINE__, __func__, ##args)
#else
	#define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
#endif

void setRegister (volatile void *base, uint32_t offset, uint32_t mask, uint32_t value) {
  uint32_t old_value = ioread32 (base + offset);  
  old_value = old_value & ~(mask);  
  value = value & mask;   
  value = value | old_value;
  iowrite32(value, base + offset);
  return;
}

int getGpioFromDbt(struct platform_device *pdev, const char *gpio_dbt_name, int is_input) {
  int gpio, err;
  struct device_node *dev_node = pdev->dev.of_node;

  gpio = of_get_named_gpio(dev_node, gpio_dbt_name, 0);
  if (gpio < 0) {
    pr_err("Error trying to get: %s gpio from dbt.\n", gpio_dbt_name);
    return gpio;
  }
  err = gpio_request(gpio, gpio_dbt_name);
  if (err < 0 ) {
    pr_err("Error trying to request gpio: %s.\n", gpio_dbt_name);
    return err;
  }

  if(is_input) {
    err = gpio_direction_input(gpio); 
    if (err < 0 ) {
      pr_err("Error trying to request gpio direction as input.\n");
      return err;
    }
  }
  else {
    err = gpio_direction_output(gpio, 0); 
    if (err < 0 ) {
      pr_err("Error trying to request gpio direction as output.\n");
      return err;
    }
  }
  return gpio;
};

typedef struct axiTimerMemory {
  void __iomem *__base_addr;             
  struct resource *__resource;         
  unsigned long __remap_size;   
} axiTimerMemory_t;

static struct state {
  // Device number from alloc_chrdev_region
  dev_t __device_number;
  // New devices (mayor-minor) from mkdev
  dev_t __new_devices[MAX_DEVICES];
  // Resources for char device creation    
  struct class *__devclass; 
  struct device *__dev[MAX_DEVICES];     
  struct cdev __chardev[MAX_DEVICES];   
  // Dinamic creation for each pwm in hardware
  axiTimerMemory_t axi_timer_mem[MAX_DEVICES];
  // EMIO GPIOS to reset the hardware (one per axi timer) 
  int __gpios_reset[MAX_DEVICES];
  // AXI clock frequency
  int __axi_clk_freq;
  // PWM output frequency
  int __pwm_out_freq;

} state;

static const struct of_device_id driverOfMatch[] = {
  { .compatible = DEVICE_NAME },

};

static int driver_probe (struct platform_device *pdev) {
  int i;
  int ret;
  char gpio_name[64];

  DEBUG_PRINT(" Driver probed! \n");
  for (i=0; i<MAX_DEVICES ;i++) {
    // Get mem from dbt
    DEBUG_PRINT("Get res.\n");
    state.axi_timer_mem[i].__resource = platform_get_resource(pdev, IORESOURCE_MEM, i);
    if(!state.axi_timer_mem[i].__resource) {
      pr_err("platform_get_resources: c Resource ould not be get.\n");
      return -ENODEV;
    } 
    state.axi_timer_mem[i].__remap_size = state.axi_timer_mem[i].__resource->end \
    - state.axi_timer_mem[i].__resource->start + 1;
    DEBUG_PRINT("Req mem.\n");
    if (!request_mem_region(state.axi_timer_mem[i].__resource->start, \
    state.axi_timer_mem[i].__remap_size, pdev->name)) {
      pr_err("request_mem_region: No se pudo conseguir I/O\n");
      return -ENODEV;
    }
    DEBUG_PRINT("ioremap.\n");
    state.axi_timer_mem[i].__base_addr = ioremap(state.axi_timer_mem[i].__resource->start, \
    state.axi_timer_mem[i].__remap_size);
    if (state.axi_timer_mem[i].__base_addr == NULL) {
      pr_err("No se pudo conseguir ioremap memory\n");
      return -ENODEV;
    }
    // Get gpio from dbt
    sprintf(gpio_name, "reset-%d-gpios", i);
    state.__gpios_reset[i] = getGpioFromDbt(pdev, gpio_name, 0);
    if (state.__gpios_reset[i] < 0) {
      pr_err("Error trying to get gpio from dbt: %s.\n", gpio_name);
      return state.__gpios_reset[i];
    }
    // Get AXI clk frequency from dbt 
    ret = of_property_read_u32(pdev->dev.of_node, "clock-frequency", &state.__axi_clk_freq);
    if (ret) {
      pr_err("Error trying to get AXI clk frequency from dbt.\n");
      return ret;
    }
    // Get PWM output frequency from dbt
    ret = of_property_read_u32(pdev->dev.of_node, "pwm-frequency", &state.__pwm_out_freq);
    if (ret) {
      pr_err("Error trying to get pwm output frequency from dbt.\n");
      return ret;
    }
    DEBUG_PRINT("End for.\n");
  }
  return 0;
};

static int driver_remove(struct platform_device *pdev) {
  int i;
  
  pr_info("driver_remove!\n");
  for (i=0; i<MAX_DEVICES ;i++) {
    // Release mapped virtual address 
    iounmap(state.axi_timer_mem[i].__base_addr);
    // Release the region 
    release_mem_region(state.axi_timer_mem[i].__resource->start, state.axi_timer_mem[i].__remap_size);
  }
  return 0;
};

static struct platform_driver axiTimerPlatformDriver = {
  .probe      = driver_probe,				                              
  .remove     = driver_remove, 
  .driver = {
    .name  = DEVICE_NAME,	
    .owner = THIS_MODULE,
    .of_match_table = of_match_ptr(driverOfMatch),
  },                             
};

static int driver_open(struct inode *inode, struct file *file) {
  int i;
  
  if ((file->private_data = kmalloc(sizeof(dev_t), GFP_KERNEL)) == NULL) {
    pr_err ("Kmalloc failed askig for mem to allocate device number.\n");
    return -ENODEV; /* No such device */
  }

  pr_info("Driver open. Resetting... \n");
  for(i=0; i<MAX_DEVICES; i++) {
    if (inode->i_rdev == state.__new_devices[i]) {
      DEBUG_PRINT("The device %d was opened.\n", i);
      // Save the device number for others callback
      *(dev_t*)(file->private_data) = state.__new_devices[i];
      // Reset active low
      gpio_set_value(state.__gpios_reset[i], 0);
      mdelay(100);
      gpio_set_value(state.__gpios_reset[i], 1);
      // Load Register for Timer 0
      setRegister(  state.axi_timer_mem[i].__base_addr, 
                    OFFSET_TLR0, 
                    (uint32_t) 0xFFFFFFFF, 
                    (uint32_t)( (state.__axi_clk_freq/state.__pwm_out_freq)-1 ) );
      // Load Register for Timer 1
      setRegister(  state.axi_timer_mem[i].__base_addr,
                    OFFSET_TLR1, 
                    (uint32_t) 0xFFFFFFFF , 
                    (uint32_t)( (state.__axi_clk_freq/state.__pwm_out_freq)-1 ) );
      // Set Load Timer 0
      setRegister(  state.axi_timer_mem[i].__base_addr, 
                    OFFSET_TCSR0, 
                    (0x1<<5), 
                    (0x1<<5) );
      // Set Load Timer 1
      setRegister(  state.axi_timer_mem[i].__base_addr, 
                    OFFSET_TCSR1, 
                    (0x1<<5), 
                    (0x1<<5) );
      // Clear Load Timer 0 
      setRegister(  state.axi_timer_mem[i].__base_addr, 
                    OFFSET_TCSR0, 
                    (0x1<<5), 
                    (0x0<<5));
      // Clear Load Timer 1
      setRegister(  state.axi_timer_mem[i].__base_addr, 
                    OFFSET_TCSR1, 
                    (0x1<<5), 
                    (0x0<<5));
      // Set to 0 bit MDT (Timer mode is generate) for Timer 0
      setRegister(  state.axi_timer_mem[i].__base_addr, 
                    OFFSET_TCSR0, 
                    0x1, 
                    0x0);
      // Set to 0 bit MDT (Timer mode is generate) for Timer 1
      setRegister(  state.axi_timer_mem[i].__base_addr, 
                    OFFSET_TCSR1, 
                    0x1, 
                    0x0);
      // PWMA0 bit set to 1 to enable PWM for Timer 0
      setRegister(  state.axi_timer_mem[i].__base_addr, 
                    OFFSET_TCSR0, 
                    (0x1<<9), 
                    (0x1<<9));
      // PWMB0 bit set to 1 to enable PWM for Timer 1
      setRegister(  state.axi_timer_mem[i].__base_addr, 
                    OFFSET_TCSR1, 
                    (0x1<<9), 
                    (0x01<<9));
      // Enable GenerateOut signals for Timer 0
      setRegister(  state.axi_timer_mem[i].__base_addr, 
                    OFFSET_TCSR0, 
                    (0x1<<2),
                    (0x01<<2));
      // Enable GenerateOut signals for Timer 1
      setRegister(  state.axi_timer_mem[i].__base_addr, 
                    OFFSET_TCSR1, 
                    (0x1<<2), 
                    (0x01<<2));
      // Auto or Reload Mode for Timer 0
      setRegister(  state.axi_timer_mem[i].__base_addr, 
                    OFFSET_TCSR0, 
                    (0x1<<4), 
                    (0x01<<4));
      // Auto or Reload Mode for Timer 1
      setRegister(  state.axi_timer_mem[i].__base_addr, 
                    OFFSET_TCSR1, 
                    (0x1<<4), 
                    (0x01<<4));
      // Down Count for Timer 0
      setRegister(  state.axi_timer_mem[i].__base_addr, 
                    OFFSET_TCSR0, 
                    (0x1<<1), 
                    (0x01<<1));
      // Down Count for Timer 1
      setRegister(  state.axi_timer_mem[i].__base_addr, 
                    OFFSET_TCSR1,
                    (0x1<<1), 
                    (0x01<<1));
      // Enable Timer 0 and Timer 1 
      setRegister(  state.axi_timer_mem[i].__base_addr, 
                    OFFSET_TCSR0, 
                    (0x1<<10), 
                    (0x1<<10));
    }
  }
  return 0;
};

static int driver_release(struct inode *inode, struct file *file) {
  int i;

  for(i=0; i<MAX_DEVICES; i++) {
    gpio_free(state.__gpios_reset[i]);
  }
  return 0;
};

long int driver_ioctl(struct file *pfile, unsigned int command, unsigned long args) {
  int i;
  uint32_t duty_to_set;

  if (_IOC_TYPE(command) != AXI_TIMER_IOC_NMAGICO) {
    DEBUG_PRINT("Invalid command.\n");
    return -EINVAL;
  }
  if (_IOC_NR(command) > AXI_TIMER_IOC_NUM_MAX) {
    DEBUG_PRINT("Invalid command.\n");
    return -EINVAL;
  } 
  if (args > 100) {
    DEBUG_PRINT("Invalid argument. It could not be more than 100 percent.\n");
    return -EINVAL;
  }
  else if (args < 0) {
    DEBUG_PRINT("Invalid argument. It could not be less than 0 percent.\n");
    return -EINVAL;
  }
  switch (command) {
  case AXI_TIMER_IOC_T_ON:
    duty_to_set = args * ((state.__axi_clk_freq/state.__pwm_out_freq)-1) / 100;
    for(i=0; i<MAX_DEVICES; i++) {
      if (*(dev_t*)(pfile->private_data) == state.__new_devices[i]) {
        DEBUG_PRINT("The duty will be changed to the device: %d.\n", i);
        // Load Register for Timer 1. Timer 1 set the duty cicle, Timer 0 the period of the PWM signal.
        setRegister(  state.axi_timer_mem[i].__base_addr,
                      OFFSET_TLR1, 
                      (uint32_t) 0xFFFFFFFF, 
                      duty_to_set);
      }
    }
    break;
  default:
    return -EINVAL;
    break;
  }
  return 0;
};

static const struct file_operations axiTimerPlatformOps = {
    .owner = THIS_MODULE,
    .open = driver_open,
    //.read = driver_read,
    //.write = driver_write,
    .release = driver_release,
    .unlocked_ioctl = driver_ioctl,
};

static int __init axiTimer_init(void) {
  int i;
  int err;
  int major;

  DEBUG_PRINT("Alloc cdev.\n");
  err = alloc_chrdev_region(&state.__device_number, BASE_MINOR, MAX_DEVICES, DEVICE_NAME);
	if (err != 0) {
    pr_err("Error trying to alloc chrdev region.\n");
    return err;  
  }
  DEBUG_PRINT("Create class.\n");
  state.__devclass = class_create(THIS_MODULE, DEVICE_CLASS_NAME);
  if (IS_ERR(state.__devclass)) {
    pr_err("Error trying to create class.\n");
    unregister_chrdev_region(state.__device_number, MAX_DEVICES);
    return PTR_ERR(state.__devclass); 
  }
  major = MAJOR(state.__device_number);
  for (i = 0; i < MAX_DEVICES; i++) {
    state.__new_devices[i] = MKDEV(major, i);
    DEBUG_PRINT("Cdev init.\n");
    cdev_init(&state.__chardev[i], &axiTimerPlatformOps);
    DEBUG_PRINT("Cdev add.\n");
    err = cdev_add(&state.__chardev[i], state.__new_devices[i], 1);
    if (err) {
      pr_err("Error trying to add cdev\n");
      unregister_chrdev_region(state.__device_number, MAX_DEVICES);
      class_destroy(state.__devclass); 
      for ( ; i > 0; i--) {
        cdev_del(&state.__chardev[i]);
        // The device of this pass has not been created yet.
        if ((i-1) > 0)
          device_destroy(state.__devclass, state.__new_devices[i]);
      }
      return err;  
    }
    DEBUG_PRINT("Create device..\n");
    state.__dev[i] = device_create(state.__devclass, DEVICE_PARENT, state.__new_devices[i], NULL, "axi_timer_pwm_%d", i);
    if (IS_ERR(state.__dev[i])) {
      pr_err("Error trying to create device.\n");
      unregister_chrdev_region(state.__device_number, MAX_DEVICES);
      class_destroy(state.__devclass);
      for ( ; i > 0; i--) {
        // The device of this pass has not been created yet.
        if ((i-1) > 0)
          device_destroy(state.__devclass, state.__new_devices[i-1]);
        cdev_del(&state.__chardev[i]);
      }
      return PTR_ERR(state.__dev);
    }
  }
  DEBUG_PRINT("Register platform driver.\n");
  if(platform_driver_register(&axiTimerPlatformDriver) < 0) {
    pr_err("Error trying to register the platform driver.\n");
    unregister_chrdev_region(state.__device_number, MAX_DEVICES);
    class_destroy(state.__devclass);                  
    for (i = 0; i < MAX_DEVICES; i++) {
      device_destroy(state.__devclass, state.__new_devices[i]);
      cdev_del(&state.__chardev[i]);
    }
    return PTR_ERR(state.__dev);
  }
  DEBUG_PRINT("axiTimer initialized.\n");
  return 0;
}


static void __exit axiTimer_exit(void) {
  int i;

  DEBUG_PRINT("Exit axiTimer driver.\n");
  DEBUG_PRINT("Unregister the platform driver.\n"); 
  platform_driver_unregister(&axiTimerPlatformDriver);
  DEBUG_PRINT("Destroy class.\n");
  class_destroy(state.__devclass); 
  for (i = 0; i < MAX_DEVICES; i++) {
    device_destroy(state.__devclass, state.__new_devices[i]);
    cdev_del(&state.__chardev[i]);
  }  
  DEBUG_PRINT("Unregister chrdev region.\n");
  unregister_chrdev_region(state.__device_number, MAX_DEVICES);

	DEBUG_PRINT("axiTimer closed.\n");
}

module_init(axiTimer_init);
module_exit(axiTimer_exit);
