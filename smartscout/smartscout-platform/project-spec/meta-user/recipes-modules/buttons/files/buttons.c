#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/uaccess.h>             
#include <linux/proc_fs.h>              
#include <linux/seq_file.h>            
#include <linux/platform_device.h>      
#include <linux/of_platform.h>          
#include <linux/cdev.h>                 
#include <linux/delay.h>
#include <linux/ktime.h>
#include <linux/interrupt.h>
#include <linux/wait.h>

#include <linux/of_gpio.h>
#include <linux/gpio.h>
#include <buttons.h>

#define DRIVER_NAME 			"buttons"
#define DEVICE_PARENT 		NULL
#define CLASS_NAME 				"buttons_class"
#define BASE_MINOR 				0
#define MINOR_COUNT 			1

#define BUTTONS_NUM 4
#define BUTTONS_0_GPIO "buttons_0-gpios"
#define BUTTONS_1_GPIO "buttons_1-gpios"
#define BUTTONS_2_GPIO "buttons_2-gpios"
#define BUTTONS_3_GPIO "buttons_3-gpios"

#define DEBUG_BUTTONS 1
#if defined(DEBUG_BUTTONS) 
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

	volatile int gpio_0_val;
  volatile int gpio_1_val; 
  volatile int gpio_2_val;
  volatile int gpio_3_val;

  int irq[BUTTONS_NUM];
} state = { .gpio_0_val = 0, .gpio_1_val = 0, .gpio_2_val = 0, .gpio_3_val = 0 };

long int driver_ioctl(struct file *pfile, unsigned int command, unsigned long args) {
  int ret = 0;
  enum ButtonNum msg = NON_EXISTENT;

  if (_IOC_TYPE(command) != BUTTONS_IOC_NMAGICO) {
    DEBUG_PRINT("Invalid command.\n");
    return -EINVAL;
  }
  if (_IOC_NR(command) > BUTTONS_IOC_NUM_MAX) {
    DEBUG_PRINT("Invalid command.\n");
    return -EINVAL;
  } 
  switch(command) {
  case BUTTONS_IOC_WAIT_BLOCKING:
    DEBUG_PRINT("Waitting interrupts.\n");
    state.gpio_0_val = 0;
    state.gpio_1_val = 0;
    state.gpio_2_val = 0;
    state.gpio_3_val = 0;
    wait_event_interruptible(wq, ((state.gpio_0_val == 1) || (state.gpio_1_val == 1) ||
      (state.gpio_2_val == 1) || (state.gpio_3_val == 1)));
    DEBUG_PRINT("Interrupts arrived, gpios: %d, %d, %d, %d.\n", state.gpio_0_val, state.gpio_1_val,
        state.gpio_2_val, state.gpio_3_val);
    if(state.gpio_0_val)
      msg = BUTTON_0;
    else if(state.gpio_1_val)
      msg = BUTTON_1;
    else if(state.gpio_2_val)
      msg = BUTTON_2;
    else if(state.gpio_3_val)
      msg = BUTTON_3;
    else  
      msg = NON_EXISTENT;
    DEBUG_PRINT("sizeof(enum ButtonNum): %d.\n", sizeof(int));
    DEBUG_PRINT("sizeof(int): %d.\n", sizeof(int));
    if( (access_ok(VERIFY_WRITE, (void *)args, sizeof(int))) == 0) {
      pr_info("Failed: access_ok.\n");  
      return -1;
    }
    if (put_user(msg, (int *)args) != 0) {
      pr_info("Failed: __copy_to_user.\n");
      return -1;
    }
    break;
	default:
    ret = -1;
    break;
  }
  DEBUG_PRINT("Ret: %d.\n", ret);
  return ret;
}

static irqreturn_t buttons_0_handler(int irq, void *data) {
  DEBUG_PRINT("IRQ button 0.\n");
  state.gpio_0_val = 1;
  wake_up_interruptible(&wq);
  DEBUG_PRINT("gpio_0_val: %d.\n", state.gpio_0_val);
  return IRQ_HANDLED;
}

static irqreturn_t buttons_1_handler(int irq, void *data) {
  DEBUG_PRINT("IRQ button 1.\n");
  state.gpio_1_val = 1;
  wake_up_interruptible(&wq);
  DEBUG_PRINT("gpio_1_val: %d.\n", state.gpio_1_val);
  return IRQ_HANDLED;
}

static irqreturn_t buttons_2_handler(int irq, void *data) {
  DEBUG_PRINT("IRQ button 2.\n");
  state.gpio_2_val = 1;
  wake_up_interruptible(&wq);
  DEBUG_PRINT("gpio_2_val: %d.\n", state.gpio_2_val);
  return IRQ_HANDLED;
}

static irqreturn_t buttons_3_handler(int irq, void *data) {
  DEBUG_PRINT("IRQ button 3.\n");
  state.gpio_3_val = 1;
  wake_up_interruptible(&wq);
  DEBUG_PRINT("gpio_3_val: %d.\n", state.gpio_3_val);
  return IRQ_HANDLED;
}

static const struct file_operations buttons_file_operations = {
	//.owner = THIS_MODULE,
	//.open = driver_open,
	//.read = driver_read,
	//.write = driver_write,
	//.release = driver_release,
	.unlocked_ioctl = driver_ioctl,
};

static int buttons_probe(struct platform_device *pdev) {
  int err;

  DEBUG_PRINT("Buttons probe.\n");
  if ((state.irq[0] = platform_get_irq(pdev, 0)) < 0) {
    pr_err("The ISR could not be gotten from dbt.\n");
    return state.irq[0];    
  }
  if ((state.irq[1] = platform_get_irq(pdev, 1)) < 0) {
    pr_err("The ISR could not be gotten from dbt.\n");
    return state.irq[1];    
  }
  if ((state.irq[2] = platform_get_irq(pdev, 2)) < 0) {
    pr_err("The ISR could not be gotten from dbt.\n");
    return state.irq[2];    
  }
  if ((state.irq[3] = platform_get_irq(pdev, 3)) < 0) {
    pr_err("The ISR could not be gotten from dbt.\n");
    return state.irq[3];    
  }
	if((err = request_irq(state.irq[0], buttons_0_handler, IRQF_TRIGGER_RISING, pdev->name, NULL)) != 0) {
    pr_err("Error trying to request gpio interrupt for: %s.\n", BUTTONS_0_GPIO);
    return err;
  }
	if((err = request_irq(state.irq[1], buttons_1_handler, IRQF_TRIGGER_RISING, pdev->name, NULL)) != 0) {
    pr_err("Error trying to request gpio interrupt for: %s.\n", BUTTONS_1_GPIO);
    return err;
  }
	if((err = request_irq(state.irq[2], buttons_2_handler, IRQF_TRIGGER_RISING, pdev->name, NULL)) != 0) {
    pr_err("Error trying to request gpio interrupt for: %s.\n", BUTTONS_2_GPIO);
    return err;
  }
	if((err = request_irq(state.irq[3], buttons_3_handler, IRQF_TRIGGER_RISING, pdev->name, NULL)) != 0) {
    pr_err("Error trying to request gpio interrupt for: %s.\n", BUTTONS_3_GPIO);
    return err;
  }
  DEBUG_PRINT("Buttons probed.\n");
	return 0;
}

static int buttons_remove(struct platform_device *pdev) {
	return 0;
}

static struct of_device_id buttons_of_match[] = {
	{ .compatible = DRIVER_NAME, },
	{ /* end of list */ },
};
MODULE_DEVICE_TABLE(of, buttons_of_match);

static struct platform_driver buttons_driver = {
	.driver = {
		.name = DRIVER_NAME,
		.owner = THIS_MODULE,
		.of_match_table	= buttons_of_match,
	},
	.probe		= buttons_probe,
	.remove		= buttons_remove,
};

static int __init buttons_init(void) {
  int err;

  DEBUG_PRINT("Init buttons driver.\n");

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
  cdev_init(state.chardev, &buttons_file_operations);

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
  if(platform_driver_register(&buttons_driver) < 0) {
    pr_err("Error trying to register the platform driver.\n");
    unregister_chrdev_region(state.devtype, MINOR_COUNT);
    cdev_del(state.chardev);
    class_destroy(state.devclass);                  
    device_destroy(state.devclass, state.devtype);  
    return PTR_ERR(state.dev);
  }

  DEBUG_PRINT("buttons initialized.\n");
  return 0;
}

static void __exit buttons_exit(void) {
  DEBUG_PRINT("Exit buttons driver.\n");

  DEBUG_PRINT("Unregister the platform driver.\n"); 
  platform_driver_unregister(&buttons_driver);
  DEBUG_PRINT("Destroy device.\n");  
  device_destroy(state.devclass, state.devtype);  
  DEBUG_PRINT("Destroy class.\n");
  class_destroy(state.devclass); 
  DEBUG_PRINT("Delete cdev.\n");
  cdev_del(state.chardev);       
  DEBUG_PRINT("Unregister chrdev region.\n");
  unregister_chrdev_region(state.devtype, MINOR_COUNT);

	DEBUG_PRINT("buttons closed.\n");
}

module_init(buttons_init);
module_exit(buttons_exit);

/* Standard module information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Fuschetto Martin");
MODULE_DESCRIPTION("buttons");