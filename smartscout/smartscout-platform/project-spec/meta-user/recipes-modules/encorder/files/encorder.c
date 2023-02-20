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
MODULE_DESCRIPTION("encoder");

#define DRIVER_NAME "encoder"
#define DEVICE_PARENT NULL
#define CLASS_NAME "encoder_class"

#define BASE_MINOR  	0
#define MINOR_COUNT		1

