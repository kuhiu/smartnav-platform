#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/slab.h>
#include <linux/io.h>
#include <linux/interrupt.h>
#include <linux/of_gpio.h>
#include <linux/gpio.h>
#include <linux/of_address.h>
#include <linux/of_device.h>
#include <linux/of_platform.h>
#include <linux/cdev.h> 

/** Standard module information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Fuschetto Martin. Email: marfus@hotmail.es");
MODULE_DESCRIPTION("l298n");

#define DRIVER_NAME "l298n"
#define DEVICE_PARENT NULL
#define CLASS_NAME "l298n_class"

#define BASE_MINOR 				0
#define MINOR_COUNT 			1

#define L298N_IOC_NMAGICO 'c'
#define L298N_IOC_NUM_MAX 4
#define L298N_IOC_STOP _IO(L298N_IOC_NMAGICO, 0)
#define L298N_IOC_FORWARD _IO(L298N_IOC_NMAGICO, 1)
#define L298N_IOC_BACK _IO(L298N_IOC_NMAGICO, 2)
#define L298N_IOC_RIGHT _IO(L298N_IOC_NMAGICO, 3)
#define L298N_IOC_LEFT _IO(L298N_IOC_NMAGICO, 4)

#define GPIO_MOTOR_CTRL_0 "motor_ctrl_0-gpios"
#define GPIO_MOTOR_CTRL_1 "motor_ctrl_1-gpios"
#define GPIO_MOTOR_CTRL_2 "motor_ctrl_2-gpios"
#define GPIO_MOTOR_CTRL_3 "motor_ctrl_3-gpios"

//#define DEBUG_L298N 1
#if defined(DEBUG_L298N) 
 	#define DEBUG_PRINT(fmt, args...) printk( "DEBUG: %s:%d:%s(): " fmt, \
																						__FILE__, __LINE__, __func__, ##args)
#else
	#define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
#endif

static struct l298n_local {
	dev_t devtype;          
  struct class *devclass; 
  struct device *dev;     
  struct cdev *chardev;   

  int motor_ctrl_0_gpio;
	int motor_ctrl_1_gpio;
	int motor_ctrl_2_gpio;
	int motor_ctrl_3_gpio;
} state;

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

static const struct of_device_id driver_of_match[] = {
  { .compatible = DRIVER_NAME },

};

static int l298n_probe(struct platform_device *pdev) {
  state.motor_ctrl_0_gpio = getGpioFromDbt(pdev, GPIO_MOTOR_CTRL_0, 0);
  if (state.motor_ctrl_0_gpio < 0) {
    pr_err("Error trying to getGpioFromDbt: %s.\n", GPIO_MOTOR_CTRL_0);
    return state.motor_ctrl_0_gpio;
  }
  state.motor_ctrl_1_gpio = getGpioFromDbt(pdev, GPIO_MOTOR_CTRL_1, 0);
  if (state.motor_ctrl_1_gpio < 0) {
    pr_err("Error trying to getGpioFromDbt: %s.\n", GPIO_MOTOR_CTRL_1);
    return state.motor_ctrl_1_gpio;
  }
	state.motor_ctrl_2_gpio = getGpioFromDbt(pdev, GPIO_MOTOR_CTRL_2, 0);
  if (state.motor_ctrl_2_gpio < 0) {
    pr_err("Error trying to getGpioFromDbt: %s.\n", GPIO_MOTOR_CTRL_2);
    return state.motor_ctrl_2_gpio;
  }
  state.motor_ctrl_3_gpio = getGpioFromDbt(pdev, GPIO_MOTOR_CTRL_3, 0);
  if (state.motor_ctrl_3_gpio < 0) {
    pr_err("Error trying to getGpioFromDbt: %s.\n", GPIO_MOTOR_CTRL_3);
    return state.motor_ctrl_3_gpio;
  }
	return 0;
}

static int l298n_remove(struct platform_device *pdev) {
  gpio_free(state.motor_ctrl_0_gpio);
  gpio_free(state.motor_ctrl_1_gpio);
  gpio_free(state.motor_ctrl_2_gpio);
  gpio_free(state.motor_ctrl_3_gpio);
	return 0;
}

static struct platform_driver l298n_driver = {
	.driver = {
		.name = DRIVER_NAME,
		.owner = THIS_MODULE,
		.of_match_table	= driver_of_match,
	},
	.probe		= l298n_probe,
	.remove		= l298n_remove,
};

long int driver_ioctl(struct file *pfile, unsigned int command, unsigned long args) {

  if (_IOC_TYPE(command) != L298N_IOC_NMAGICO) {
    DEBUG_PRINT("Invalid command.\n");
    return -EINVAL;
  }
  if (_IOC_NR(command) > L298N_IOC_NUM_MAX) {
    DEBUG_PRINT("Invalid command.\n");
    return -EINVAL;
  } 

  switch (command) {
  case L298N_IOC_STOP:
    gpio_set_value(state.motor_ctrl_0_gpio, 0);
    gpio_set_value(state.motor_ctrl_1_gpio, 0);
		gpio_set_value(state.motor_ctrl_2_gpio, 0);
		gpio_set_value(state.motor_ctrl_3_gpio, 0);
    break;
  case L298N_IOC_FORWARD:
    gpio_set_value(state.motor_ctrl_0_gpio, 1);
    gpio_set_value(state.motor_ctrl_1_gpio, 0);
		gpio_set_value(state.motor_ctrl_2_gpio, 1);
		gpio_set_value(state.motor_ctrl_3_gpio, 0);
    break;
  case L298N_IOC_RIGHT:
    gpio_set_value(state.motor_ctrl_0_gpio, 1);
    gpio_set_value(state.motor_ctrl_1_gpio, 0);
		gpio_set_value(state.motor_ctrl_2_gpio, 0);
		gpio_set_value(state.motor_ctrl_3_gpio, 1);
    break;
  case L298N_IOC_LEFT:
    gpio_set_value(state.motor_ctrl_0_gpio, 0);
    gpio_set_value(state.motor_ctrl_1_gpio, 1);
		gpio_set_value(state.motor_ctrl_2_gpio, 1);
		gpio_set_value(state.motor_ctrl_3_gpio, 0);
    break;
  case L298N_IOC_BACK:
    gpio_set_value(state.motor_ctrl_0_gpio, 0);
    gpio_set_value(state.motor_ctrl_1_gpio, 1);
		gpio_set_value(state.motor_ctrl_2_gpio, 0);
		gpio_set_value(state.motor_ctrl_3_gpio, 1);
    break;
  default:
	  DEBUG_PRINT("Invalid command.\n");
    return -EINVAL;
    break;
  }
  return 0;
};

static const struct file_operations l298n_file_operations = {
    .owner = THIS_MODULE,
    //.open = driver_open,
    //.read = driver_read,
    //.write = driver_write,
    //.release = driver_release,
    .unlocked_ioctl = driver_ioctl,
};

static int __init l298n_init(void) {
  int err;

  DEBUG_PRINT("Init l298n driver.\n");
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
  cdev_init(state.chardev, &l298n_file_operations);
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
  if(platform_driver_register(&l298n_driver) < 0) {
    pr_err("Error trying to register the platform driver.\n");
    unregister_chrdev_region(state.devtype, MINOR_COUNT);
    cdev_del(state.chardev);
    class_destroy(state.devclass);                  
    device_destroy(state.devclass, state.devtype);  
    return PTR_ERR(state.dev);
  }
  DEBUG_PRINT("l298n initialized.\n");
  return 0;
}

static void __exit l298n_exit(void) {
  DEBUG_PRINT("Exit l298n driver.\n");
  DEBUG_PRINT("Unregister the platform driver.\n"); 
  platform_driver_unregister(&l298n_driver);
  DEBUG_PRINT("Destroy device.\n");  
  device_destroy(state.devclass, state.devtype);  
  DEBUG_PRINT("Destroy class.\n");
  class_destroy(state.devclass); 
  DEBUG_PRINT("Delete cdev.\n");
  cdev_del(state.chardev);       
  DEBUG_PRINT("Unregister chrdev region.\n");
  unregister_chrdev_region(state.devtype, MINOR_COUNT);
	DEBUG_PRINT("l298n closed.\n");
}

module_init(l298n_init);
module_exit(l298n_exit);