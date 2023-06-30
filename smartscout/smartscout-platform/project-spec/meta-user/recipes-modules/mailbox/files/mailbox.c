/**
 * @file mailbox.c
 * @author your name (you@domain.com)
 * @brief This module assumes that the mailbox is initialized by the microblaze
 * @version 0.1
 * @date 2023-02-15
 * 
 * @copyright Copyright (c) 2023
 * 
 */

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
#include <linux/interrupt.h> 
#include "mailbox.h"

/* Standard module information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Fuschetto Martin. Email: marfus@hotmail.es");
MODULE_DESCRIPTION("axi-mailbox");

#define DEVICE_NAME "axi_mailbox"              
#define DEVICE_CLASS_NAME "axi_mailbox_class"

#define BASE_MINOR 0                                      
#define MAX_DEVICES 1     // Max number of the devices                                        
#define DEVICE_PARENT NULL

// Mailbox registers
#define XMB_WRITE_REG_OFFSET    0x00	// Mailbox write register 
#define XMB_READ_REG_OFFSET     0x08  // Mailbox read register
#define XMB_STATUS_REG_OFFSET   0x10	// Mailbox status register
#define XMB_ERROR_REG_OFFSET    0x14	// Mailbox error register
#define XMB_SIT_REG_OFFSET   		0x18	// Mailbox send interrupt threshold register
#define XMB_RIT_REG_OFFSET   		0x1C	// Mailbox receive interrupt threshold register
#define XMB_IS_REG_OFFSET   		0x20	// Mailbox interrupt status register
#define XMB_IE_REG_OFFSET   		0x24	// Mailbox interrupt enable register
#define XMB_IP_REG_OFFSET   		0x28	// Mailbox interrupt pending register
#define XMB_CTRL_REG_OFFSET   	0x2C	// Mailbox control register
// Status bits
#define XMB_STATUS_EMPTY			  0x01
#define XMB_STATUS_FULL			  	0x02
#define XMB_STATUS_STA			  	0x04
#define XMB_STATUS_RTA			  	0x08
#define XMB_IS_STI   		        0x01
#define XMB_IS_RTI   		        0x02
#define XMB_IS_ERR   		        0x04

#define DEBUG_AXI_MAILBOX 1
#if defined(DEBUG_AXI_MAILBOX) 
 	#define DEBUG_PRINT(fmt, args...) printk( "DEBUG: %s:%d:%s(): " fmt, \
																						__FILE__, __LINE__, __func__, ##args)
#else
	#define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
#endif

/** Wait queue */
static DECLARE_WAIT_QUEUE_HEAD(wait_queue);
/**
 * @brief Struct of requested memory 
 * 
 */
typedef struct axi_mail_box_memory {
  void __iomem *__base_addr;             
  struct resource *__resource;         
  unsigned long __remap_size;   
} axiMailBoxMemory;
/**
 * @brief Internal state struct 
 * 
 */
static struct state {
  // Device number from alloc_chrdev_region
  dev_t __device_number;
  // New devices (mayor-minor) from mkdev
  dev_t __new_devices[MAX_DEVICES];
  // Resources for char device creation    
  struct class *__devclass; 
  struct device *__dev[MAX_DEVICES];     
  struct cdev __chardev[MAX_DEVICES];   
	// Requested memory for each device
	axiMailBoxMemory axi_mailbox_memory[MAX_DEVICES];
  // irq
  int irq[MAX_DEVICES];
} state;
/**
 * @brief Set the register object
 * 
 * @param base 
 * @param offset 
 * @param mask 
 * @param value 
 */
void set_register (volatile void *base, uint32_t offset, uint32_t mask, uint32_t value) {
  uint32_t old_value = ioread32 (base + offset);  
  old_value = old_value & ~(mask);  
  value = value & mask;   
  value = value | old_value;
  iowrite32(value, base + offset);
  return;
}
/**
 * @brief Get the register object
 * 
 * @param base 
 * @param offset 
 * @return uint32_t 
 */
uint32_t get_register (volatile void *base, uint32_t offset) { return (ioread32 (base + offset)); }
/**
 * @brief Check if mailbox is empty
 * 
 * @return int 
 */
int isEmpty(int mb_index) {
	int ret;
	uint32_t status;

	status = get_register(state.axi_mailbox_memory[mb_index].__base_addr, XMB_STATUS_REG_OFFSET);
	if (status & XMB_STATUS_EMPTY)
		ret = 1;
	else
		ret = 0;
	return ret;
}
/**
 * @brief Check if the mailbox is full
 * 
 * @param mb_index 
 * @return int 
 */
int isFull(int mb_index) {
	int ret;
	uint32_t status;

	status = get_register(state.axi_mailbox_memory[mb_index].__base_addr, XMB_STATUS_REG_OFFSET);
	if (status & XMB_STATUS_FULL)
		ret = 1;
	else
		ret = 0;
	return ret;
}
/**
 * @brief Driver interrupt handler
 * 
 * @param irq 
 * @param data 
 * @return irqreturn_t 
 */
static irqreturn_t driver_isr(int irq, void *data) {
  int i;
  int mBox_index;
  uint32_t mask;

  // Get mailbox index
  for (i=0; i<MAX_DEVICES; i++) {
    if (irq == state.irq[i])
      mBox_index = i;
  }
  DEBUG_PRINT("mBox_index: %d.\n", mBox_index);
  
  mask = get_register( 
      state.axi_mailbox_memory[mBox_index].__base_addr, 
      XMB_IS_REG_OFFSET);

	if (mask & XMB_IS_STI) {
		DEBUG_PRINT("STI interrupt.\n");
	}
	else if (mask & XMB_IS_RTI) {
		DEBUG_PRINT("RTI interrupt.\n");
	}
	else if (mask & XMB_IS_ERR) {
		DEBUG_PRINT("ERR interrupt.\n");
	}
  else 
    DEBUG_PRINT("Unknown interrupt.\n");

  return IRQ_HANDLED;
}
/**
 * @brief Of device id
 * 
 */
static const struct of_device_id driverOfMatch[] = {
  { .compatible = DEVICE_NAME },

};
/**
 * @brief Platform probe
 * 
 * @param pdev 
 * @return int 
 */
static int driver_probe (struct platform_device *pdev) {
  int i;
  int ret;

  DEBUG_PRINT(" Driver probed! \n");
  for (i=0; i<MAX_DEVICES ;i++) {
    // Get mem from dbt
    DEBUG_PRINT("Get res.\n");
    state.axi_mailbox_memory[i].__resource = platform_get_resource(pdev, IORESOURCE_MEM, i);
    if(!state.axi_mailbox_memory[i].__resource) {
      pr_err("platform_get_resources: c Resource ould not be get.\n");
      return -ENODEV;
    } 
    state.axi_mailbox_memory[i].__remap_size = state.axi_mailbox_memory[i].__resource->end \
    - state.axi_mailbox_memory[i].__resource->start + 1;
    DEBUG_PRINT("Req mem.\n");
    if (!request_mem_region(state.axi_mailbox_memory[i].__resource->start, \
    state.axi_mailbox_memory[i].__remap_size, pdev->name)) {
      pr_err("request_mem_region: No se pudo conseguir I/O\n");
      return -ENODEV;
    }
    DEBUG_PRINT("ioremap.\n");
    state.axi_mailbox_memory[i].__base_addr = ioremap(state.axi_mailbox_memory[i].__resource->start, \
    state.axi_mailbox_memory[i].__remap_size);
    if (state.axi_mailbox_memory[i].__base_addr == NULL) {
      pr_err("No se pudo conseguir ioremap memory\n");
      return -ENODEV;
    }
    if ((state.irq[i] = platform_get_irq(pdev, i)) < 0) {
      pr_err("The ISR could not be gotten from dbt.\n");
      return state.irq[i];    
    }
    if ((ret = request_irq(state.irq[i], driver_isr, IRQF_TRIGGER_HIGH , pdev->name, NULL)) != 0) {
      pr_err("The ISR could not be gotten.\n");
      return ret;    
    }
    DEBUG_PRINT("End for.\n");
  }
  return 0;
};
/**
 * @brief Platform remove
 * 
 * @param pdev 
 * @return int 
 */
static int driver_remove(struct platform_device *pdev) {
  int i;
  
  pr_info("driver_remove!\n");
  for (i=0; i<MAX_DEVICES ;i++) {
    // Release mapped virtual address 
    iounmap(state.axi_mailbox_memory[i].__base_addr);
    // Release the region 
    release_mem_region(state.axi_mailbox_memory[i].__resource->start, state.axi_mailbox_memory[i].__remap_size);
    // Free irq
    free_irq(state.irq[i], driver_isr);
  }
  return 0;
};
/**
 * @brief Platform operations
 * 
 */
static struct platform_driver mailboxPlatformDriver = {
  .probe      = driver_probe,				                              
  .remove     = driver_remove, 
  .driver = {
    .name  = DEVICE_NAME,	
    .owner = THIS_MODULE,
    .of_match_table = of_match_ptr(driverOfMatch),
  },                             
};
/**
 * @brief Platform operation: OPEN
 * 
 * @param inode 
 * @param file 
 * @return int 
 */
static int driver_open(struct inode *inode, struct file *file) {
  file->private_data = (void*) iminor(inode);
  return 0;
};
/**
 * @brief Platform operation: IOCTL
 * 
 * @param file 
 * @param command 
 * @param args 
 * @return long int 
 */
long int driver_ioctl(struct file *file, unsigned int command, unsigned long args) {
	int ret = 0;
  int num_bytes = 0;
  uint32_t read_value;
	int mBox_index = (int) file->private_data;
  msgMailbox *msg = kmalloc(sizeof(msgMailbox), GFP_DMA);

  if (_IOC_TYPE(command) != AXI_MAILBOX_IOC_NMAGICO) {
    DEBUG_PRINT("Invalid command.\n");
    return -EINVAL;
  }
  if (_IOC_NR(command) > AXI_MAILBOX_IOC_NUM_MAX) {
    DEBUG_PRINT("Invalid command.\n");
    return -EINVAL;
  } 
  switch (command) {
  case AXI_MAILBOX_IOC_PUSH_BLOCKING:
    if( (access_ok(VERIFY_READ, (void *)args, sizeof(msgMailbox))) == 0) {
      pr_info("Failed: access_ok verifying read.\n");  
      return -1;
    }
    read_value = __copy_from_user(msg, (void *)args, sizeof(msgMailbox));
    if (read_value != 0) {
      pr_info("Failed: __copy_from_user.\n");
      return -1;
    }
		while (num_bytes < MSG_LENGTH) {
			/* Write a message to the mbox */
      if (isFull(mBox_index)) {
        DEBUG_PRINT("Waiting for STA...\n");
        wait_event_interruptible(wait_queue, !isFull(mBox_index));
      }
      DEBUG_PRINT("Not full mailbox...\n");
      DEBUG_PRINT("num_bytes: %d, to write %d.\n", num_bytes, *(msg->msg + (char)num_bytes));
      set_register( state.axi_mailbox_memory[mBox_index].__base_addr, 
                    XMB_WRITE_REG_OFFSET, 
                    0xFFFFFFFF, 
                    *(msg->msg + (char)num_bytes));
      num_bytes++;
		}
    break;
  case AXI_MAILBOX_IOC_POP_BLOCKING:
    if (isEmpty(mBox_index)) {
      DEBUG_PRINT("Waiting for RTA...\n");
      wait_event_interruptible(wait_queue, !isEmpty(mBox_index));
    }
    DEBUG_PRINT("RTA arrived.\n");
    while (num_bytes < MSG_LENGTH) {
      // Read the msg
      if (isEmpty(mBox_index)) {
        DEBUG_PRINT("Waiting for RTA...\n");
        wait_event_interruptible(wait_queue, !isEmpty(mBox_index));
      }
      msg->msg[num_bytes] = get_register( 
          state.axi_mailbox_memory[mBox_index].__base_addr, 
          XMB_READ_REG_OFFSET);
      num_bytes++;
    }
    if( (access_ok(VERIFY_WRITE, (void *)args, sizeof(msgMailbox))) == 0) {
      pr_info("Failed: access_ok.\n");  
      return -1;
    }
    if (__copy_to_user((void *)args, msg, sizeof(msgMailbox)) != 0) {
      pr_info("Failed: __copy_to_user.\n");
      return -1;
    }
    break;
  default:
    ret = -EINVAL;
    break;
  }
  return ret;
};
/**
 * @brief File operation functions 
 * 
 */
static const struct file_operations mailboxPlatformOps = {
    .owner = THIS_MODULE,
    .open = driver_open,
    //.read = driver_read,
    //.write = driver_write,
    //.release = driver_release,
    .unlocked_ioctl = driver_ioctl,
};
/**
 * @brief Driver init 
 * 
 * @return int 
 */
static int __init mailbox_init(void) {
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
    cdev_init(&state.__chardev[i], &mailboxPlatformOps);
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
    state.__dev[i] = device_create(state.__devclass, DEVICE_PARENT, state.__new_devices[i], NULL, "axi_mailbox_%d", i);
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
  if(platform_driver_register(&mailboxPlatformDriver) < 0) {
    pr_err("Error trying to register the platform driver.\n");
    unregister_chrdev_region(state.__device_number, MAX_DEVICES);
    class_destroy(state.__devclass);                  
    for (i = 0; i < MAX_DEVICES; i++) {
      device_destroy(state.__devclass, state.__new_devices[i]);
      cdev_del(&state.__chardev[i]);
    }
    return PTR_ERR(state.__dev);
  }
  DEBUG_PRINT("mailbox initialized.\n");
  return 0;
}
/**
 * @brief Driver exit
 * 
 */
static void __exit mailbox_exit(void) {
  int i;

  DEBUG_PRINT("Exit mailbox driver.\n");
  DEBUG_PRINT("Unregister the platform driver.\n"); 
  platform_driver_unregister(&mailboxPlatformDriver);
  DEBUG_PRINT("Destroy class.\n");
  class_destroy(state.__devclass); 
  for (i = 0; i < MAX_DEVICES; i++) {
    device_destroy(state.__devclass, state.__new_devices[i]);
    cdev_del(&state.__chardev[i]);
  }  
  DEBUG_PRINT("Unregister chrdev region.\n");
  unregister_chrdev_region(state.__device_number, MAX_DEVICES);

	DEBUG_PRINT("mailbox closed.\n");
}
// Load init and exit functions
module_init(mailbox_init);
module_exit(mailbox_exit);


