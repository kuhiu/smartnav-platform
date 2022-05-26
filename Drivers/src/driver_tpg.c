#include <linux/kernel.h>
#include <linux/module.h>
#include <asm/uaccess.h>                /* Se necesita para copy_from_user */
#include <asm/io.h>                     /* Se necesita para IO Read/Write Functions */
#include <linux/proc_fs.h>              /* Se necesita para Proc File System Functions */
#include <linux/seq_file.h>             /* Se necesita para Sequence File Operations */
#include <linux/platform_device.h>      /* Se necesita para Platform Driver Functions */
#include <linux/of_platform.h>          
#include <linux/cdev.h>                 /* Se necesita para crear el Char Device */
#include <linux/delay.h>
#include <linux/of_address.h>

#define DEVICE_NAME "xlnx,v-tpg-8.0"                		/* Define Driver Name */
#define DEVICE_CLASS_NAME "tpg_control_chardev_class"
//#define BYTE2READ 1*4                                     /* Cantidad de word de 32 bits que tengo que leer * 4 = Bytes 2 read */
#define BASE_MINOR  0                                       /* Base del numero menor */
#define MINOR_COUNT 1                                     	/* Cantidad de numeros menores que voy a usar */
#define DEVICE_PARENT NULL


/*************************************************************************************************/
/***************************************** Registros *********************************************/
/*************************************************************************************************/
#define OFFSET_TPG_COLOR_MASK 		(uint32_t) 0x30


static int driver_probe (struct platform_device *pdev);
static int driver_remove (struct platform_device *pdev);
/*************************************************************************************************/
/************************************* Estructuras  tpg_handle ****************************************/
/*************************************************************************************************/
static struct tpg_handle {

  /* TPG driver */
  void __iomem *base_addr_ctrl;     /* Vitual Base Address */
  struct resource *res_ctrl;        /* Device Resource Structure */
  unsigned long remap_size_ctrl;    /* Device Memory Size */

  /* GPIO rst */
  void __iomem *base_addr_rst;  	/* Vitual Base Address */
  struct resource *res_rst;       /* Device Resource Structure */
  unsigned long remap_size_rst;   /* Device Memory Size */

  /* Creacion del char device */
  dev_t devtype;          // numero mayor y menor
  struct class *devclass; // class_create()
  struct device *dev;     // device_create()
  struct cdev chardev;    // cdev_add()

} tpg_handle;




/*************************************************************************************************/
/**
  @brief Funcion para setear registros

  @param base
  @param offset
  @param mask
  @param value
  @param pdev

  @returns void
**/
/*************************************************************************************************/
void set_registers (volatile void *base, uint32_t offset, uint32_t mask, uint32_t value)
{
  uint32_t old_value = ioread32 (base + offset);  // Leo los datos del registro
  //pr_info(DEVICE_NAME": set_registers: Lei:  %#x\n", old_value);
  old_value = old_value & ~(mask);  // Borro los datos que voy a escribir
  value = value & mask;   // Me quedo con los valores que van
  value = value | old_value;
  //pr_info(DEVICE_NAME": set_registers: Escribo el registro con:  %#x\n", value);
  iowrite32(value, base + offset);
  return;
}
/*************************************************************************************************/
/*************************************************************************************************/


/*************************************************************************************************/
/**
  @brief Funcion para setear registros

  @param base
  @param offset
  @param mask
  @param value
  @param pdev

  @returns void
**/
/*************************************************************************************************/
volatile uint32_t get_register (uint32_t *reg, uint32_t offset)
{
  uint32_t out=0;

  out=ioread32(reg + offset);
  pr_info(DEVICE_NAME": get_register : Lei el registro:  %d\n", out);

  return out;
}
/*************************************************************************************************/
/*************************************************************************************************/






/*************************************************************************************************/
/********************************* Estructuras  of_device_id *************************************/

static const struct of_device_id driver_of_match[] = {
{ .compatible = "xlnx,v-tpg-8.0" },
{ }
};

/*************************************************************************************************/
/********************************* Estructuras  platform_driver **********************************/

static struct platform_driver mytpg_control_pdriver = {
  .probe      = driver_probe,				                              
  .remove     = driver_remove, 
  .driver = {
    .name  = DEVICE_NAME,	
    .owner = THIS_MODULE,
    .of_match_table = of_match_ptr(driver_of_match),
  },                             
};



/*************************************************************************************************/
/**
  @brief Funcion que se ejecutara con el uso de la syscall open()

  @returns 0: sin error, -1: error
**/
/*************************************************************************************************/

static int driver_open(struct inode *inode, struct file *file) 
{
    pr_info("Holaaaa! Entre a open! \n");

  	//Restart

    /* Escribo el dato del AXI GPIO (esta en la base de la pagina) */
	pr_info("Reseteando... \n");
    iowrite32( (uint32_t)0x00, tpg_handle.base_addr_rst );
	iowrite32( (uint32_t)0x01, tpg_handle.base_addr_rst );

  	// IDLE TPG
	//set_registers(tpg_handle.base_addr_ctrl, (uint32_t)0x00, (uint32_t)0xFF, (uint32_t)00);
  	set_registers(tpg_handle.base_addr_ctrl, (uint32_t)0x00, (uint32_t)0x01, (uint32_t)0x01);

	// Color mask
	set_registers(tpg_handle.base_addr_ctrl, OFFSET_TPG_COLOR_MASK, (uint32_t)0xFFFFFFFF, (uint32_t)0x0);

	// Motion Speed
	//set_registers(tpg_handle.base_addr_ctrl, (uint32_t)0x38, (uint32_t)0xFFFFFFFF, (uint32_t)0x4);

	// Cross Hairs Row
	//set_registers(tpg_handle.base_addr_ctrl, (uint32_t)0x48, (uint32_t)0xFFFFFFFF, (uint32_t)100);

	// Color Hair Column
	//set_registers(tpg_handle.base_addr_ctrl, (uint32_t)0x50, (uint32_t)0xFFFFFFFF, (uint32_t)100);

	// Zplate Horizontal
	//set_registers(tpg_handle.base_addr_ctrl, (uint32_t)0x58, (uint32_t)0xFFFFFFFF, (uint32_t)30);

	// Zplate Horizontal
	//set_registers(tpg_handle.base_addr_ctrl, (uint32_t)0x60, (uint32_t)0xFFFFFFFF, (uint32_t)0x0);

	// Zplate Vertical
	//set_registers(tpg_handle.base_addr_ctrl, (uint32_t)0x68, (uint32_t)0xFFFFFFFF, (uint32_t)0x1);

	// Zplate Vertical
	//set_registers(tpg_handle.base_addr_ctrl, (uint32_t)0x70, (uint32_t)0xFFFFFFFF, (uint32_t)0x0);

	// Box size
	//set_registers(tpg_handle.base_addr_ctrl, (uint32_t)0x78, (uint32_t)0xFFFFFFFF, (uint32_t)50);

	// Color
	//set_registers(tpg_handle.base_addr_ctrl, (uint32_t)0x80, (uint32_t)0xFFFFFFFF, (uint32_t)0x0);
	//set_registers(tpg_handle.base_addr_ctrl, (uint32_t)0x88, (uint32_t)0xFFFFFFFF, (uint32_t)0x0);
	//set_registers(tpg_handle.base_addr_ctrl, (uint32_t)0x90, (uint32_t)0xFFFFFFFF, (uint32_t)0x0);

	// Foregrownd Patter
	set_registers(tpg_handle.base_addr_ctrl, (uint32_t)0x28, (uint32_t)0xFFFFFFFF, (uint32_t)0x0);

	// Height
	set_registers(tpg_handle.base_addr_ctrl, (uint32_t)0x10, (uint32_t)0xFFFFFFFF, (uint32_t)480);
	// Width
	set_registers(tpg_handle.base_addr_ctrl, (uint32_t)0x18, (uint32_t)0xFFFFFFFF, (uint32_t)640);

	// RGB
	set_registers(tpg_handle.base_addr_ctrl, (uint32_t)0x40, (uint32_t)0xFFFFFFFF, (uint32_t)0x0);

	// Modo
	set_registers(tpg_handle.base_addr_ctrl, (uint32_t)0x20, (uint32_t)0xFFFFFFFF, 0x9);

	pr_info("El modo es = %08X \n", ioread32(tpg_handle.base_addr_ctrl + (uint32_t)0x20 ));


  	//set_registers(tpg_handle.base_addr_ctrl, (uint32_t)0x00, (uint32_t)0xFFFFFFFF, (uint32_t)0x10000000);

  	//Restart

    /* Escribo el dato del AXI GPIO (esta en la base de la pagina) */
	//pr_info("Reseteando... \n");
    //iowrite32( (uint32_t)0x00, tpg_handle.base_addr_rst );
	//iowrite32( (uint32_t)0x01, tpg_handle.base_addr_rst );


  	// Start TPG
	pr_info("Comenzando... \n");
  	set_registers(tpg_handle.base_addr_ctrl, (uint32_t)0x00, (uint32_t)0xFFFFFFFF, (uint32_t)0x1);

	pr_info("El Control es = %08X \n", ioread32(tpg_handle.base_addr_ctrl + (uint32_t)0x00 ));
    
	pr_info("Chau! Sali de open! \n");
    return 0;
} 





/*************************************************************************************************/
/******************************** Estructura file_operations *************************************/
/**
    @brief Implementacion de las funciones del driver open, read, write, close, ioctl, cada driver
    tiene su propia file_operations
**/

static const struct file_operations mytpg_control_operations = {
    //.owner = THIS_MODULE,
    .open = driver_open,
    //.read = driver_read,
    //.write = driver_write,
    //.release = driver_release,
    //.unlocked_ioctl = driver_ioctl,
};

/*************************************************************************************************/
/**
  @brief Todos los recursos que utiliza el driver registrados en probe()

  @param pdev Struct platform_device

  @returns Error Handling, predefined errors in the kernel tree
**/
/*************************************************************************************************/

static int driver_probe (struct platform_device *pdev)
{
    pr_info(" Hola! Entre a driver probed! \n");

    // Consigo informacion del devicetree DeviceTree
    tpg_handle.res_ctrl = platform_get_resource(pdev, IORESOURCE_MEM, 0);
    if(!tpg_handle.res_ctrl)
    {
        pr_err("platform_get_resources: No se pudo conseguir la memoria\n");
        return -ENODEV;
    } 

    pr_info("La memoria que voy a mapear en el kernel va desde: %08X a %08X \n", tpg_handle.res_ctrl->start, tpg_handle.res_ctrl->end);

    // Esta funcion solo preserva el area para que no sea usada, no hace ningun tipo de mapeo 
    tpg_handle.remap_size_ctrl = tpg_handle.res_ctrl->end - tpg_handle.res_ctrl->start + 1;
    if (!request_mem_region(tpg_handle.res_ctrl->start, tpg_handle.remap_size_ctrl, pdev->name)) 
    {
        pr_err("request_mem_region: No se pudo conseguir I/O\n");
        return -ENODEV;
    }

    //pr_info("La memoria que voy a mapear en el kernel va desde: %08X a %08X ", tpg_handle.res_ctrl->start, tpg_handle.res_ctrl->end);

    tpg_handle.base_addr_ctrl = ioremap(tpg_handle.res_ctrl->start, tpg_handle.remap_size_ctrl);
    if (tpg_handle.base_addr_ctrl == NULL) {
        pr_err("No se pudo conseguir ioremap memory\n");
        return -ENODEV;
    }

	printk(" base_Addr_Ctrl %lu - %p \n", (unsigned long)tpg_handle.base_addr_ctrl, tpg_handle.base_addr_ctrl);

	// Consigo informacion del devicetree DeviceTree
    tpg_handle.res_rst = platform_get_resource(pdev, IORESOURCE_MEM, 1);
    if(!tpg_handle.res_rst)
    {
        pr_err("platform_get_resources: No se pudo conseguir la memoria\n");
        return -ENODEV;
    } 

    pr_info("La memoria que voy a mapear en el kernel va desde: %08X a %08X \n", tpg_handle.res_rst->start, tpg_handle.res_rst->end);

    // Esta funcion solo preserva el area para que no sea usada, no hace ningun tipo de mapeo 
    tpg_handle.remap_size_rst = tpg_handle.res_rst->end - tpg_handle.res_rst->start + 1;
    if (!request_mem_region(tpg_handle.res_rst->start, tpg_handle.remap_size_rst, pdev->name)) 
    {
        pr_err("request_mem_region: No se pudo conseguir I/O\n");
    }

    //pr_info("La memoria que voy a mapear en el kernel va desde: %08X a %08X ", tpg_handle.res_rst->start, tpg_handle.res_rst->end);

    tpg_handle.base_addr_rst = ioremap(tpg_handle.res_rst->start, tpg_handle.remap_size_rst);
    if (tpg_handle.base_addr_rst == NULL) {
        pr_err("No se pudo conseguir ioremap memory\n");
        return -ENODEV;
    }



    pr_info("Chau! Salgo de driver probed! \n");

    return 0;
}

/*************************************************************************************************/
/**
  @brief 

  @param pdev

  @returns 0: sin error, -1: error
**/
/*************************************************************************************************/

 static int driver_remove(struct platform_device *pdev)
 {
     pr_info("driver_remove: Remuevo el dispositivo!\n");

    /* Release mapped virtual address */
    iounmap(tpg_handle.base_addr_ctrl);
    /* Release the region */
    release_mem_region(tpg_handle.res_ctrl->start, tpg_handle.remap_size_ctrl);

    /* Release mapped virtual address */
    iounmap(tpg_handle.base_addr_rst);
    /* Release the region */
    release_mem_region(tpg_handle.res_rst->start, tpg_handle.remap_size_rst);

    pr_info("driver_remove: Removi el dispositivo!\n");

    return 0;
 }




/*************************************************************************************************/
/********************** Register myvdma control platform driver **********************************/

static int __init my_pdrv_init (void) 
{
  pr_info("my_pdrv_init: Hola mundo!\n");

  //No es necesario allocar cdev porque lo defini como struct cdev no como struct *cdev !!!
  //pr_info("%s: Obtengo memoria para allocar cdev struct\n", pdev->name);
  //(tpg_handle.chardev) = cdev_alloc();    // Obtiene memoria para allocar la estructura 

  pr_info("my_pdrv_init: Intento allocar cdev\n");
  if (alloc_chrdev_region(&tpg_handle.devtype, BASE_MINOR, MINOR_COUNT, DEVICE_NAME) != 0) 
  {
    pr_err("alloc_chrdev_region: Error no es posible asignar numero mayor\n");
    return -EBUSY;  // Device or resource busy 
  }
  pr_info("my_pdrv_init: Cdev struct allocada\n");


  /* Procedemos a registrar el dispositivo en el sistema */
  pr_info("my_pdrv_init: Procedo a registrar el dispositivo en el sistema\n");

  /* Para inicializarla se puede inicializar a mano o bien una vez definida file_operations...  */
  pr_info("%my_pdrv_init: Cargo cdev struct\n");
  cdev_init(&tpg_handle.chardev, &mytpg_control_operations);

  /* Para agregarla al sistema */
  pr_info("my_pdrv_init: Procedo a agregar la estructura cdev al sistema\n");
  if (cdev_add(&tpg_handle.chardev, tpg_handle.devtype, MINOR_COUNT) != 0) 
  {
    pr_err("cdev_add: No se pude agregar el cdev\n");
    unregister_chrdev_region(tpg_handle.devtype, MINOR_COUNT);
    return -EPERM;    // -1
  }
  pr_info("my_pdrv_init: Estructura cdev agregada al sistema\n");

  /* Voy a crear la clase */
  pr_info("my_pdrv_init: Voy a crear la clase \n");
  tpg_handle.devclass = class_create(THIS_MODULE, DEVICE_CLASS_NAME);
  if (IS_ERR(tpg_handle.devclass)) 
  {
    pr_err("class_create: No se pudo crear la clase\n");
    unregister_chrdev_region(tpg_handle.devtype, MINOR_COUNT);
    cdev_del(&tpg_handle.chardev);
    return PTR_ERR(tpg_handle.devclass);   // Handling null pointer cap2 Linux Drivers Development
  }
  pr_info("my_pdrv_init: Clase creada \n");

  /* Voy a crear el dispositivo */
  pr_info("my_pdrv_init: Voy a crear el dispositivo \n");
  tpg_handle.dev = device_create(tpg_handle.devclass, DEVICE_PARENT, tpg_handle.devtype, NULL, DEVICE_NAME);
  if (IS_ERR(tpg_handle.dev)) 
  {
    pr_err("device_create: No se pudo crear el dispositivo\n");
    unregister_chrdev_region(tpg_handle.devtype, MINOR_COUNT);
    cdev_del(&tpg_handle.chardev);
    class_destroy(tpg_handle.devclass);  // Destruyo la clase creada en el paso previo
    return PTR_ERR(tpg_handle.dev);
  }
  pr_info("my_pdrv_init: Dispositivo creado \n");

  pr_info("my_pdrv_init: Finalmente platform_driver_register\n");
  if(platform_driver_register(&mytpg_control_pdriver) < 0)
  {
    pr_err("device_create: No se pudo crear el dispositivo\n");
    unregister_chrdev_region(tpg_handle.devtype, MINOR_COUNT);
    cdev_del(&tpg_handle.chardev);
    class_destroy(tpg_handle.devclass);                  // Destruyo la clase creada en el paso previo
    device_destroy(tpg_handle.devclass, tpg_handle.devtype);  // Destruyo el device creado en el paso previo
    return PTR_ERR(tpg_handle.dev);
  }

  pr_info("my_pdrv_init: Finalmente termine\n");
  return 0;
}
module_init(my_pdrv_init);


static void __exit my_pdrv_remove (void)    // se ejecuta cuando hago rmmod
{
  pr_info("my_pdrv_remove: Remuevo el dispositivo!\n");

  pr_info("my_pdrv_remove: DesRegistro el driver!\n"); 
  platform_driver_unregister(&mytpg_control_pdriver);
  pr_info("my_pdrv_remove: Destruyo el dispositivo!\n");  
  device_destroy(tpg_handle.devclass, tpg_handle.devtype);  
  pr_info("my_pdrv_remove: Destruyo la clase!\n");
  class_destroy(tpg_handle.devclass); 
  pr_info("my_pdrv_remove: Quito cdev del sistema!\n");
  cdev_del(&tpg_handle.chardev);       
  pr_info("my_pdrv_remove: Desaloco cdev!\n");
  unregister_chrdev_region(tpg_handle.devtype, MINOR_COUNT);
}
module_exit(my_pdrv_remove);

/*************************************************************************************************/
/************************************ Module Information *****************************************/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Martin Fuschetto");
MODULE_DESCRIPTION("My platform leds control");