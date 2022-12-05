#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/uaccess.h>              /* Se necesita para copy_from_user */
#include <asm/io.h>                     /* Se necesita para IO Read/Write Functions */
#include <linux/proc_fs.h>              /* Se necesita para Proc File System Functions */
#include <linux/seq_file.h>             /* Se necesita para Sequence File Operations */
#include <linux/platform_device.h>      /* Se necesita para Platform Driver Functions */
#include <linux/of_platform.h>          
#include <linux/cdev.h>                 /* Se necesita para crear el Char Device */
#include <linux/delay.h>
#include <linux/ktime.h>
#include <linux/interrupt.h>
#include <linux/wait.h>

#include <linux/of_gpio.h>
#include <linux/gpio.h>

#define DRIVER_NAME 			"hcsr04"
#define DEVICE_PARENT 		NULL
#define CLASS_NAME 				"hcsr04_class"
#define BASE_MINOR 				0
#define MINOR_COUNT 			1

#define GPIO_TRIGGER_HCSR04_1 "trig_hcsr04_1-gpios"
#define GPIO_TRIGGER_HCSR04_2 "trig_hcsr04_2-gpios"
#define GPIO_TRIGGER_HCSR04_3 "trig_hcsr04_3-gpios"
#define GPIO_ECHO_HCSR04_1    "echo_hcsr04_1-gpios"
#define GPIO_ECHO_HCSR04_2    "echo_hcsr04_2-gpios"
#define GPIO_ECHO_HCSR04_3    "echo_hcsr04_3-gpios"

#define HCSR04_IOC_NMAGICO 'c'
#define HCSR04_IOC_NUM_MAX 1
#define HCSR04_IOC_TRIGGER _IO(HCSR04_IOC_NMAGICO, 1)

#define DEBUG_HCSR04 1
#if defined(DEBUG_HCSR04) 
 	#define DEBUG_PRINT(fmt, args...) printk( "DEBUG: %s:%d:%s(): " fmt, \
																						__FILE__, __LINE__, __func__, ##args)
#else
	#define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
#endif

DECLARE_WAIT_QUEUE_HEAD(wq);

static struct state {
	dev_t devtype;          
  struct class *devclass; 
  struct device *dev;     
  struct cdev *chardev;   

  int trig_hcsr04_1_gpio, trig_hcsr04_2_gpio, trig_hcsr04_3_gpio;
  int echo_hcsr04_1_gpio, echo_hcsr04_2_gpio, echo_hcsr04_3_gpio;

  volatile ktime_t echo_start_1, echo_end_1;
  volatile ktime_t echo_start_2, echo_end_2;
  volatile ktime_t echo_start_3, echo_end_3; 
  volatile int echo_arrived_1; 
  volatile int echo_arrived_2;
  volatile int echo_arrived_3;
} state;

long int driver_ioctl(struct file *pfile, unsigned int command, unsigned long args) {
  //int ret;
  int counter;
  u64 time;

  if (_IOC_TYPE(command) != HCSR04_IOC_NMAGICO) {
    DEBUG_PRINT("Invalid command.\n");
    return -EINVAL;
  }
  if (_IOC_NR(command) > HCSR04_IOC_NUM_MAX) {
    DEBUG_PRINT("Invalid command.\n");
    return -EINVAL;
  } 

  switch(command) {
  case HCSR04_IOC_TRIGGER:
    switch (args) {
    case 1:
    DEBUG_PRINT("hcsr04 trigger 1.\n");
    state.echo_arrived_1 = 0;
    gpio_set_value(state.trig_hcsr04_1_gpio, 1);
    udelay(10);
    gpio_set_value(state.trig_hcsr04_1_gpio, 0);
    // Wait event or timeout
    //if(!wait_event_interruptible_timeout(wq, (state.echo_arrived_1 == 1), HZ))
    //  DEBUG_PRINT("hcsr04 sensor 1 timeout\n");
    counter=0;
    while (!state.echo_arrived_1) {
      if (++counter>100) {
        printk("Sensor 1: Out of range.\n");
        break;
      }
      mdelay(1);
    }
    time = ktime_to_us( ktime_sub(state.echo_end_1, state.echo_start_1));
    DEBUG_PRINT("Sensor 1. Time in kernel space: %llu.\n", time);
    return (time);
    case 2:
    DEBUG_PRINT("hcsr04 trigger 2.\n");
    state.echo_arrived_2 = 0;
    gpio_set_value(state.trig_hcsr04_2_gpio, 1);
    udelay(10);
    gpio_set_value(state.trig_hcsr04_2_gpio, 0);
    // Wait event or timeout
    //if(!wait_event_interruptible_timeout(wq, (state.echo_arrived_2 == 1), HZ))
    //  DEBUG_PRINT("hcsr04 sensor 2 timeout\n");
    counter=0;
    while (!state.echo_arrived_2) {
      if (++counter>100) {
        printk("Sensor 2: Out of range.\n");
        break;
      }
      mdelay(1);
    }
    time = ktime_to_us( ktime_sub(state.echo_end_2, state.echo_start_2));
    DEBUG_PRINT("Sensor 2. Time in kernel space: %llu.\n", time);
    return (time);
    case 3:
    DEBUG_PRINT("hcsr04 trigger 3.\n");
    state.echo_arrived_3 = 0;
    gpio_set_value(state.trig_hcsr04_3_gpio, 1);
    udelay(10);
    gpio_set_value(state.trig_hcsr04_3_gpio, 0);
    // Wait event or timeout
    //if(!wait_event_interruptible_timeout(wq, (state.echo_arrived_3 == 1), HZ))
    //  DEBUG_PRINT("hcsr04 sensor 3 timeout\n");
    counter=0;
    while (!state.echo_arrived_3) {
      if (++counter>100) {
        printk("Sensor 3: Out of range.\n");
        break;
      }
      mdelay(1);
    }
    time = ktime_to_us( ktime_sub(state.echo_end_3, state.echo_start_3));
    DEBUG_PRINT("Sensor 3. Time in kernel space: %llu.\n", time);
    return (time);
    default:
      DEBUG_PRINT("Invalid argument.\n");
      return -EINVAL;
    }
  break;
  default:
    return -EINVAL;
  }
  return 0;
}

static const struct file_operations hcsr04_file_operations = {
	//.owner = THIS_MODULE,
	//.open = driver_open,
	//.read = driver_read,
	//.write = driver_write,
	//.release = driver_release,
	.unlocked_ioctl = driver_ioctl,
};

static irqreturn_t echo_handler_1(int irq, void *data) {
  //DEBUG_PRINT("Interrupt echo 1!!!\n");
  int gpio;
  ktime_t time = ktime_get();
  gpio = gpio_get_value(state.echo_hcsr04_1_gpio);
  if (state.echo_arrived_1 == 0) {
    if(gpio) {
      // Echo is high
      state.echo_start_1 = time;
      //DEBUG_PRINT("Interrupt 1 high\n");
    }
    else {
      // Echo is low
      state.echo_end_1 = time;
      state.echo_arrived_1 = 1;
      //wake_up_interruptible(&wq);
      //DEBUG_PRINT("Interrupt 1 low\n");
    }
  }
  return IRQ_HANDLED;
}

static irqreturn_t echo_handler_2(int irq, void *data) {
  //DEBUG_PRINT("Interrupt echo 2!!!\n");
  int gpio;
  ktime_t time = ktime_get();
  gpio = gpio_get_value(state.echo_hcsr04_2_gpio);
  if (state.echo_arrived_2 == 0) {
    if(gpio) {
      // Echo is high
      state.echo_start_2 = time;
      //DEBUG_PRINT("Interrupt 2 high\n");
    }
    else {
      // Echo is low
      state.echo_end_2 = time;
      state.echo_arrived_2 = 1;
      //wake_up_interruptible(&wq);
      //DEBUG_PRINT("Interrupt 2 low\n");
    }
  }
  return IRQ_HANDLED;
}

static irqreturn_t echo_handler_3(int irq, void *data) {
  //DEBUG_PRINT("Interrupt echo 3!!!\n");
  int gpio;
  ktime_t time = ktime_get();
  gpio = gpio_get_value(state.echo_hcsr04_3_gpio);
  if (state.echo_arrived_3 == 0) {
    if(gpio) {
      // Echo is high
      state.echo_start_3 = time;
      //DEBUG_PRINT("Interrupt 3 high\n");
    }
    else {
      // Echo is low
      state.echo_end_3 = time;
      state.echo_arrived_3 = 1;
      //wake_up_interruptible(&wq);
      //DEBUG_PRINT("Interrupt 3 low\n");
    }
  }
  return IRQ_HANDLED;
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
}

#ifdef CONFIG_OF
static struct of_device_id hcsr04_of_match[] = {
	{ .compatible = DRIVER_NAME, },
	{ /* end of list */ },
};
MODULE_DEVICE_TABLE(of, hcsr04_of_match);
#else
# define hcsr04_of_match
#endif

static int hcsr04_probe(struct platform_device *pdev) {
  int err;

  state.trig_hcsr04_1_gpio = getGpioFromDbt(pdev, GPIO_TRIGGER_HCSR04_1, 0);
  if (state.trig_hcsr04_1_gpio < 0) {
    pr_err("Error trying to getGpioFromDbt: %s.\n", GPIO_TRIGGER_HCSR04_1);
    return state.trig_hcsr04_1_gpio;
  }

  state.trig_hcsr04_2_gpio = getGpioFromDbt(pdev, GPIO_TRIGGER_HCSR04_2, 0);
  if (state.trig_hcsr04_2_gpio < 0) {
    pr_err("Error trying to getGpioFromDbt: %s.\n", GPIO_TRIGGER_HCSR04_2);
    return state.trig_hcsr04_2_gpio;
  }

  state.trig_hcsr04_3_gpio = getGpioFromDbt(pdev, GPIO_TRIGGER_HCSR04_3, 0);
  if (state.trig_hcsr04_3_gpio < 0) {
    pr_err("Error trying to getGpioFromDbt: %s.\n", GPIO_TRIGGER_HCSR04_3);
    return state.trig_hcsr04_3_gpio;
  }

  state.echo_hcsr04_1_gpio = getGpioFromDbt(pdev, GPIO_ECHO_HCSR04_1, 1);
  if (state.echo_hcsr04_1_gpio < 0) {
    pr_err("Error trying to getGpioFromDbt: %s.\n", GPIO_ECHO_HCSR04_1);
    return state.echo_hcsr04_1_gpio;
  }

  state.echo_hcsr04_2_gpio = getGpioFromDbt(pdev, GPIO_ECHO_HCSR04_2, 1);
  if (state.echo_hcsr04_2_gpio < 0) {
    pr_err("Error trying to getGpioFromDbt: %s.\n", GPIO_ECHO_HCSR04_2);
    return state.echo_hcsr04_2_gpio;
  }

  state.echo_hcsr04_3_gpio = getGpioFromDbt(pdev, GPIO_ECHO_HCSR04_3, 1);
  if (state.echo_hcsr04_3_gpio < 0) {
    pr_err("Error trying to getGpioFromDbt: %s.\n", GPIO_ECHO_HCSR04_3);
    return state.echo_hcsr04_3_gpio;
  }

  // Echos with interrupt

  if((err = request_irq(gpio_to_irq(state.echo_hcsr04_1_gpio), echo_handler_1, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING , pdev->name, NULL)) != 0) {
    pr_err("Error trying to request gpio interrupt for: %s.\n", GPIO_ECHO_HCSR04_1);
    gpio_free(state.trig_hcsr04_1_gpio);
    gpio_free(state.trig_hcsr04_2_gpio);
    gpio_free(state.trig_hcsr04_3_gpio);
    gpio_free(state.echo_hcsr04_1_gpio);
    gpio_free(state.echo_hcsr04_2_gpio);
    gpio_free(state.echo_hcsr04_3_gpio);	
    return err;
  }

  if((err = request_irq(gpio_to_irq(state.echo_hcsr04_2_gpio), echo_handler_2, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING , pdev->name, NULL)) != 0) {
    pr_err("Error trying to request gpio interrupt for: %s.\n", GPIO_ECHO_HCSR04_2);
    gpio_free(state.trig_hcsr04_1_gpio);
    gpio_free(state.trig_hcsr04_2_gpio);
    gpio_free(state.trig_hcsr04_3_gpio);
    gpio_free(state.echo_hcsr04_1_gpio);
    gpio_free(state.echo_hcsr04_2_gpio);
    gpio_free(state.echo_hcsr04_3_gpio);
    return err;
  }

  if((err = request_irq(gpio_to_irq(state.echo_hcsr04_3_gpio), echo_handler_3, IRQF_TRIGGER_RISING | IRQF_TRIGGER_FALLING , pdev->name, NULL)) != 0) {
    pr_err("Error trying to request gpio interrupt for: %s.\n", GPIO_ECHO_HCSR04_3);
    gpio_free(state.trig_hcsr04_1_gpio);
    gpio_free(state.trig_hcsr04_2_gpio);
    gpio_free(state.trig_hcsr04_3_gpio);
    gpio_free(state.echo_hcsr04_1_gpio);
    gpio_free(state.echo_hcsr04_2_gpio);
    gpio_free(state.echo_hcsr04_3_gpio);	
    return err;
  }
	return 0;
}

static int hcsr04_remove(struct platform_device *pdev) {
  gpio_free(state.trig_hcsr04_1_gpio);
  gpio_free(state.trig_hcsr04_2_gpio);
  gpio_free(state.trig_hcsr04_3_gpio);
  gpio_free(state.echo_hcsr04_1_gpio);
  gpio_free(state.echo_hcsr04_2_gpio);
  gpio_free(state.echo_hcsr04_3_gpio);
	return 0;
}

static struct platform_driver hcsr04_driver = {
	.driver = {
		.name = DRIVER_NAME,
		.owner = THIS_MODULE,
		.of_match_table	= hcsr04_of_match,
	},
	.probe		= hcsr04_probe,
	.remove		= hcsr04_remove,
};

static int __init hcsr04_init(void) {
  int err;

  DEBUG_PRINT("Init hcsr04 driver.\n");

  DEBUG_PRINT("Ask for mem to alloc cdev struct.\n");
  state.chardev = cdev_alloc();   

  DEBUG_PRINT("Alloc cdev.\n");
  err = alloc_chrdev_region(&state.devtype, BASE_MINOR, MINOR_COUNT, DRIVER_NAME);
	if (err != 0) {
    pr_err("Error trying to alloc chrdev region.\n");
    return err;  // Device or resource busy 
  }

  DEBUG_PRINT("Register the device.\n");

  DEBUG_PRINT("Init chrdev struct\n");
  cdev_init(state.chardev, &hcsr04_file_operations);

	err = cdev_add(state.chardev, state.devtype, MINOR_COUNT);
  if (err != 0) {
    pr_err("Error trying to add cdev\n");
    unregister_chrdev_region(state.devtype, MINOR_COUNT);
    return err;   
  }

  DEBUG_PRINT("Create class.\n");
  state.devclass = class_create(THIS_MODULE, CLASS_NAME);
  if (IS_ERR(state.devclass)) {
    pr_err("Error trying to create class.\n");
    unregister_chrdev_region(state.devtype, MINOR_COUNT);
    cdev_del(state.chardev);
    return PTR_ERR(state.devclass); 
  }

  DEBUG_PRINT("Create device.\n");
  state.dev = device_create(state.devclass, DEVICE_PARENT, state.devtype, NULL, DRIVER_NAME);
  if (IS_ERR(state.dev)) {
    pr_err("Error trying to create device.\n");
    unregister_chrdev_region(state.devtype, MINOR_COUNT);
    cdev_del(state.chardev);
    class_destroy(state.devclass);
    return PTR_ERR(state.dev);
  }

  DEBUG_PRINT("Register platform driver.\n");
  if(platform_driver_register(&hcsr04_driver) < 0) {
    pr_err("Error trying to register the platform driver.\n");
    unregister_chrdev_region(state.devtype, MINOR_COUNT);
    cdev_del(state.chardev);
    class_destroy(state.devclass);                  
    device_destroy(state.devclass, state.devtype);  
    return PTR_ERR(state.dev);
  }

  DEBUG_PRINT("hcsr04 initialized.\n");
  return 0;
}


static void __exit hcsr04_exit(void) {
  DEBUG_PRINT("Exit hcsr04 driver.\n");

  DEBUG_PRINT("Unregister the platform driver.\n"); 
  platform_driver_unregister(&hcsr04_driver);
  DEBUG_PRINT("Destroy device.\n");  
  device_destroy(state.devclass, state.devtype);  
  DEBUG_PRINT("Destroy class.\n");
  class_destroy(state.devclass); 
  DEBUG_PRINT("Delete cdev.\n");
  cdev_del(state.chardev);       
  DEBUG_PRINT("Unregister chrdev region.\n");
  unregister_chrdev_region(state.devtype, MINOR_COUNT);

	DEBUG_PRINT("hcsr04 closed.\n");
}

module_init(hcsr04_init);
module_exit(hcsr04_exit);

/* Standard module information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Fuschetto Martin");
MODULE_DESCRIPTION("hcsr04 - driver");