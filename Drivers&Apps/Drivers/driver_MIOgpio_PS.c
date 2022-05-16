#include <linux/kernel.h>
#include <linux/module.h>
#include <linux/uaccess.h>               /* Se necesita para copy_from_user */
#include <asm/io.h>                     /* Se necesita para IO Read/Write Functions */
#include <linux/proc_fs.h>              /* Se necesita para Proc File System Functions */
#include <linux/seq_file.h>             /* Se necesita para Sequence File Operations */
#include <linux/platform_device.h>      /* Se necesita para Platform Driver Functions */
#include <linux/of_platform.h>          
#include <linux/cdev.h>                 /* Se necesita para crear el Char Device */
#include <linux/delay.h>
#include <linux/ktime.h>
#include <linux/interrupt.h>
#include <linux/gpio.h>


#define DEVICE_NAME "chardev_MIOgpio_PS"                /* Define Driver Name */
#define DEVICE_CLASS_NAME "class_MIOgpio_PS"
#define BYTE2READ 6*4                                   /* Cantidad de word de 32 bits que tengo que leer * 4 = Bytes 2 read */
#define BASE_MINOR 0                                    /* Base del numero menor */
#define MINOR_COUNT 1                                   /* Cantidad de numeros menores que voy a usar */
#define DEVICE_PARENT NULL

#define  IRQF_DISABLED 0

//#define BASE_MIO_PIN_00      0xF8000000
#define OFFSET_MIO_PIN_00         (uint32_t) 0x00000700  // 0 Bank
#define OFFSET_MIO_PIN_00_9       (uint32_t) 0x00000700+0x4*9
#define OFFSET_MIO_PIN_00_12      (uint32_t) 0x00000700+0x4*12
#define OFFSET_MIO_PIN_00_13      (uint32_t) 0x00000700+0x4*13
#define OFFSET_MIO_PIN_00_14      (uint32_t) 0x00000700+0x4*14
#define OFFSET_MIO_PIN_00_15      (uint32_t) 0x00000700+0x4*15
#define OFFSET_GPIO_RST_CTRL      (uint32_t) 0x0000022C
#define APER_CLK_CTRL             (uint32_t) 0x0000012C
//#define BASE_XGPIOPS         0xE000A000
#define OFFSET_GPIO_DIRM_0        (uint32_t) 0x00000204  // Set as input or output
#define OFFSET_GPIO_OUTE_0        (uint32_t) 0x00000208  // Si es salida es necesario setear el pin correspondiente
#define OFFSET_GPIO_INT_MASK_0    (uint32_t) 0x0000020C
#define OFFSET_GPIO_INTTYPE_0     (uint32_t) 0x0000021C  // Tipo de interrupcion 
#define OFFSET_GPIO_INT_EN_0      (uint32_t) 0x00000210  // Habilita la interrupcion
#define OFFSET_GPIO_INT_DIS_0     (uint32_t) 0x00000214  // Deshabilita las interrupciones
#define OFFSET_GPIO_INT_STAT_0    (uint32_t) 0x00000218  // Estado de la interrupcion
#define OFFSET_GPIO_INT_POL_0     (uint32_t) 0x00000220  // Rising or falling?
#define OFFSET_GPIO_INT_ANY_0     (uint32_t) 0x00000224  // Rising and falling edge
#define OFFSET_GPIO_DATA_0        (uint32_t) 0x00000040  // Data to write in MIO pin
#define OFFSET_GPIO_DATA_0_RO     (uint32_t) 0x00000060  // Read-only

static int driver_probe (struct platform_device *pdev);
static int driver_remove (struct platform_device *pdev);


static int right_valid_value = 0;
static int center_valid_value = 0;
static int left_valid_value = 0;

static ktime_t right_echo_start = 0;
static ktime_t right_echo_end = 0;
static ktime_t center_echo_start = 0;
static ktime_t center_echo_end = 0;
static ktime_t left_echo_start = 0;
static ktime_t left_echo_end = 0;

static struct state {


  void __iomem *xgpiops_addr;   /* Vitual Base Address */
  void __iomem *mio_pin_addr;
  struct resource *res_mio_pin;       /* Device Resource Structure from device tree */
  struct resource *res_xgpiops;
  unsigned long remap_mio_pin_size;   /* Device Memory Size */
  unsigned long remap_xgpiops_size;

  dev_t devtype;          // numero mayor y menor
  struct class *devclass; // class_create()
  struct device *dev;     // device_create()
  struct cdev chardev;    // cdev_add()

  //void __iomem *_reg_cm_per;
  long long int *TX_buff;
  long long int *RX_buff;

  int irq;

} state;


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
  @brief Handler de interrupciones

  @param irq
  @param devid

  @returns 
**/
/*************************************************************************************************/
static irqreturn_t driver_isr(int irq, void *data)
{
	ktime_t right_ktime_dummy;
  ktime_t center_ktime_dummy;
  ktime_t left_ktime_dummy;

  //pr_info("Hola entre a driver_isr, interrupciones en: %08X \n", ((ioread32(state.xgpiops_addr + OFFSET_GPIO_INT_STAT_0) >> 12) & (uint32_t)0x01) );

  if (  ((ioread32(state.xgpiops_addr + OFFSET_GPIO_INT_STAT_0) >> 12) & (uint32_t)0x01) == (uint32_t)(0x1) )  // Hubo interrupcion en MIO-12
  {
      //pr_info("Hubo interrupcion en MIO-12 \n");
      if (right_valid_value==0) {
        right_ktime_dummy=ktime_get();
        //pr_info("Es 1 o 0? %08X \n", ioread32(state.xgpiops_addr + OFFSET_GPIO_DATA_0_RO) );
        if ( ((ioread32(state.xgpiops_addr + OFFSET_GPIO_DATA_0_RO) >> 12) & (uint32_t)0x01) == (uint32_t)(0x1) ) 
        {
            //pr_info("MIO-12 Es 1\n");  
            right_echo_start=right_ktime_dummy;
        }
        else 
        {
            //pr_info("MIO-12 Es 0\n");  
            right_echo_end=right_ktime_dummy;
            right_valid_value=1;
        }
      }

      set_registers(state.xgpiops_addr, OFFSET_GPIO_INT_STAT_0, (uint32_t)(0x1<<12), (uint32_t)(0x1<<12) );
  }

  if (  ((ioread32(state.xgpiops_addr + OFFSET_GPIO_INT_STAT_0) >> 14) & (uint32_t)0x01) == (uint32_t)(0x1) )  // Hubo interrupcion en MIO-12
  {
      //pr_info("Hubo interrupcion en MIO-14 \n");
      if (center_valid_value==0) {
        center_ktime_dummy=ktime_get();
        //pr_info("Es 1 o 0? %08X \n", ioread32(state.xgpiops_addr + OFFSET_GPIO_DATA_0_RO) );
        if ( ((ioread32(state.xgpiops_addr + OFFSET_GPIO_DATA_0_RO) >> 14) & (uint32_t)0x01) == (uint32_t)(0x1) ) 
        {
            //pr_info("MIO-14 Es 1\n");  
            center_echo_start=center_ktime_dummy;
        }
        else 
        {
            //pr_info("MIO-14 Es 0\n");  
            center_echo_end=center_ktime_dummy;
            center_valid_value=1;
        }
      }

      set_registers(state.xgpiops_addr, OFFSET_GPIO_INT_STAT_0, (uint32_t)(0x1<<14), (uint32_t)(0x1<<14) );
  }
    

  if (  ((ioread32(state.xgpiops_addr + OFFSET_GPIO_INT_STAT_0) >> 9) & (uint32_t)0x01) == (uint32_t)(0x1) )  // Hubo interrupcion en MIO-12
  {
      //pr_info("Hubo interrupcion en MIO-9 \n");
      if (left_valid_value==0) {
        left_ktime_dummy=ktime_get();
        //pr_info("Es 1 o 0? %08X \n", ioread32(state.xgpiops_addr + OFFSET_GPIO_DATA_0_RO) );
        if ( ((ioread32(state.xgpiops_addr + OFFSET_GPIO_DATA_0_RO) >> 9) & (uint32_t)0x01) == (uint32_t)(0x1) ) 
        {
            //pr_info("MIO-9 Es 1\n");  
            left_echo_start=left_ktime_dummy;
        }
        else 
        {
            //pr_info("MIO-9 Es 0\n");  
            left_echo_end=left_ktime_dummy;
            left_valid_value=1;
        }
      }

      set_registers(state.xgpiops_addr, OFFSET_GPIO_INT_STAT_0, (uint32_t)(0x1<<9), (uint32_t)(0x1<<9) );
  }

	return IRQ_HANDLED;
}
/*************************************************************************************************/
/*************************************************************************************************/


/*************************************************************************************************/
/********************************* Estructuras  of_device_id *************************************/

static const struct of_device_id driver_of_match[] = {
{ .compatible = "driver_MIOgpio_PS" },
{ }
};

/*************************************************************************************************/
/********************************* Estructuras  platform_driver **********************************/

static struct platform_driver myled_control_pdriver = {
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
    pr_info("Hola! Entre a open! \n");

    pr_info("Consigo memoria para el buffer de recepcion y de transmision\n");
    if ((state.RX_buff = (long long int *) kmalloc(BYTE2READ, GFP_KERNEL)) == NULL)
    {
      pr_err("Insuficiente memoria\n");
      return -ENODEV; /* No such device */
    }

    if ((state.TX_buff = (long long int *) kmalloc(BYTE2READ, GFP_KERNEL)) == NULL)
    {
      pr_err("Insuficiente memoria\n");
      return -ENODEV; /* No such device */
    }

    // Reset 
    set_registers(state.mio_pin_addr, OFFSET_GPIO_RST_CTRL, (uint32_t) 0x1, (uint32_t) 0x1);
    udelay(1);
    set_registers(state.mio_pin_addr, OFFSET_GPIO_RST_CTRL, (uint32_t) 0x1, (uint32_t) 0x0);

    // Unlock reg
    set_registers(state.mio_pin_addr, (OFFSET_MIO_PIN_00+0x8), (uint32_t) 0xFFFF, (uint32_t) 0xDF0D);

    pr_info("MIO programming options! \n");
    set_registers(state.mio_pin_addr, OFFSET_MIO_PIN_00, (uint32_t) 0xFF,      (uint32_t) 0x00);       // : Set L0_SEL, L1_SEL, L2_SEL, L3_SEL =0 y TRI_ENABLE = 0
    set_registers(state.mio_pin_addr, OFFSET_MIO_PIN_00, (uint32_t) (0x7<<9) , (uint32_t)(0x03<<9));   // : LVCMOS33
    set_registers(state.mio_pin_addr, OFFSET_MIO_PIN_00, (uint32_t) (0x1<<12), (uint32_t)(0x0<<12));   // : PULLUP disable
    set_registers(state.mio_pin_addr, OFFSET_MIO_PIN_00, (uint32_t) (0x1<<8) , (uint32_t)(0x0<<8));    // : Slow CMOS edge
    set_registers(state.mio_pin_addr, OFFSET_MIO_PIN_00, (uint32_t) (0x1<<13), (uint32_t)(0x1<<13));   // : Disable HSTL receiver

    set_registers(state.mio_pin_addr, OFFSET_MIO_PIN_00_9, (uint32_t) 0xFF,      (uint32_t) 0x00);       // : Set L0_SEL, L1_SEL, L2_SEL, L3_SEL =0 y TRI_ENABLE = 0
    set_registers(state.mio_pin_addr, OFFSET_MIO_PIN_00_9, (uint32_t) (0x7<<9) , (uint32_t)(0x03<<9));   // : LVCMOS33
    set_registers(state.mio_pin_addr, OFFSET_MIO_PIN_00_9, (uint32_t) (0x1<<12), (uint32_t)(0x0<<12));   // : PULLUP disable
    set_registers(state.mio_pin_addr, OFFSET_MIO_PIN_00_9, (uint32_t) (0x1<<8) , (uint32_t)(0x1<<8));    // : Fast CMOS edge
    set_registers(state.mio_pin_addr, OFFSET_MIO_PIN_00_9, (uint32_t) (0x1<<13), (uint32_t)(0x1<<13));   // : Disable HSTL receiver

    set_registers(state.mio_pin_addr, OFFSET_MIO_PIN_00_13, (uint32_t) 0xFF,      (uint32_t) 0x00);       // : Set L0_SEL, L1_SEL, L2_SEL, L3_SEL =0 y TRI_ENABLE = 0
    set_registers(state.mio_pin_addr, OFFSET_MIO_PIN_00_13, (uint32_t) (0x7<<9) , (uint32_t)(0x03<<9));   // : LVCMOS33
    set_registers(state.mio_pin_addr, OFFSET_MIO_PIN_00_13, (uint32_t) (0x1<<12), (uint32_t)(0x0<<12));   // : PULLUP disable
    set_registers(state.mio_pin_addr, OFFSET_MIO_PIN_00_13, (uint32_t) (0x1<<8) , (uint32_t)(0x0<<8));    // : Slow CMOS edge
    set_registers(state.mio_pin_addr, OFFSET_MIO_PIN_00_13, (uint32_t) (0x1<<13), (uint32_t)(0x1<<13));   // : Disable HSTL receiver

    set_registers(state.mio_pin_addr, OFFSET_MIO_PIN_00_14, (uint32_t) 0xFF,      (uint32_t) 0x00);       // : Set L0_SEL, L1_SEL, L2_SEL, L3_SEL =0 y TRI_ENABLE = 0
    set_registers(state.mio_pin_addr, OFFSET_MIO_PIN_00_14, (uint32_t) (0x7<<9) , (uint32_t)(0x03<<9));   // : LVCMOS33
    set_registers(state.mio_pin_addr, OFFSET_MIO_PIN_00_14, (uint32_t) (0x1<<12), (uint32_t)(0x0<<12));   // : PULLUP disable
    set_registers(state.mio_pin_addr, OFFSET_MIO_PIN_00_14, (uint32_t) (0x1<<8) , (uint32_t)(0x1<<8));    // : Fast CMOS edge
    set_registers(state.mio_pin_addr, OFFSET_MIO_PIN_00_14, (uint32_t) (0x1<<13), (uint32_t)(0x1<<13));   // : Disable HSTL receiver

    set_registers(state.mio_pin_addr, OFFSET_MIO_PIN_00_15, (uint32_t) 0xFF,      (uint32_t) 0x00);       // : Set L0_SEL, L1_SEL, L2_SEL, L3_SEL =0 y TRI_ENABLE = 0
    set_registers(state.mio_pin_addr, OFFSET_MIO_PIN_00_15, (uint32_t) (0x7<<9) , (uint32_t)(0x03<<9));   // : LVCMOS33
    set_registers(state.mio_pin_addr, OFFSET_MIO_PIN_00_15, (uint32_t) (0x1<<12), (uint32_t)(0x0<<12));   // : PULLUP disable
    set_registers(state.mio_pin_addr, OFFSET_MIO_PIN_00_15, (uint32_t) (0x1<<8) , (uint32_t)(0x0<<8));    // : Slow CMOS edge
    set_registers(state.mio_pin_addr, OFFSET_MIO_PIN_00_15, (uint32_t) (0x1<<13), (uint32_t)(0x1<<13));   // : Disable HSTL receiver

    set_registers(state.mio_pin_addr, OFFSET_MIO_PIN_00_12, (uint32_t) 0xFF,      (uint32_t) 0x00);       // : Set L0_SEL, L1_SEL, L2_SEL, L3_SEL =0 y TRI_ENABLE = 0
    set_registers(state.mio_pin_addr, OFFSET_MIO_PIN_00_12, (uint32_t) (0x7<<9) , (uint32_t)(0x03<<9));   // : LVCMOS33
    set_registers(state.mio_pin_addr, OFFSET_MIO_PIN_00_12, (uint32_t) (0x1<<12), (uint32_t)(0x0<<12));   // : PULLUP disable
    set_registers(state.mio_pin_addr, OFFSET_MIO_PIN_00_12, (uint32_t) (0x1<<8) , (uint32_t)(0x1<<8));    // : Fast CMOS edge
    set_registers(state.mio_pin_addr, OFFSET_MIO_PIN_00_12, (uint32_t) (0x1<<13), (uint32_t)(0x1<<13));   // : Disable HSTL receiver

    set_registers(state.mio_pin_addr, APER_CLK_CTRL, (uint32_t) (0x1<<22), (uint32_t)(0x1<<22));   // : Enable GPIO clk

    pr_info("GPIO Pin Configurations! \n");

    // Center hc-sr04 trigger
    set_registers(state.xgpiops_addr, OFFSET_GPIO_DIRM_0, (uint32_t)(0x1<<0), (uint32_t)(0x1<<0));    // PIN0 as output (0: input, 1: output)
    set_registers(state.xgpiops_addr, OFFSET_GPIO_OUTE_0, (uint32_t)(0x1<<0), (uint32_t)(0x1<<0));    // PIN0 Output enable

    // Right hc-sr04 trigger
    set_registers(state.xgpiops_addr, OFFSET_GPIO_DIRM_0, (uint32_t)(0x1<<15), (uint32_t)(0x1<<15));    // PIN15 as output (0: input, 1: output)
    set_registers(state.xgpiops_addr, OFFSET_GPIO_OUTE_0, (uint32_t)(0x1<<15), (uint32_t)(0x1<<15));    // PIN15 Output enable

    // Left hc-sr04 trigger
    set_registers(state.xgpiops_addr, OFFSET_GPIO_DIRM_0, (uint32_t)(0x1<<13), (uint32_t)(0x1<<13));    // PIN13 as output (0: input, 1: output)
    set_registers(state.xgpiops_addr, OFFSET_GPIO_OUTE_0, (uint32_t)(0x1<<13), (uint32_t)(0x1<<13));    // PIN13 Output enable

    // Deshabilito todas las interrupciones
    set_registers(state.xgpiops_addr, OFFSET_GPIO_INT_DIS_0, (uint32_t)(0xFFFFFFFF), (uint32_t)(0xFFFFFFFF));

    // Center hc-sr04 echo 
    set_registers(state.xgpiops_addr, OFFSET_GPIO_DIRM_0,    (uint32_t)(0x1<<12), (uint32_t)(0x0<<12));  // PIN12 as input (0: input, 1: output)
    set_registers(state.xgpiops_addr, OFFSET_GPIO_INTTYPE_0, (uint32_t)(0x1<<12), (uint32_t)(0x1<<12));  // 0: level-sensitive 1:Edge sensitive
    set_registers(state.xgpiops_addr, OFFSET_GPIO_INT_ANY_0, (uint32_t)(0x1<<12), (uint32_t)(0x1<<12));  // Trigger en both edge
    set_registers(state.xgpiops_addr, OFFSET_GPIO_INT_POL_0, (uint32_t)(0x1<<12), (uint32_t)(0x0<<12));  // cualquiera x

    // Right hc-sr04 echo  
    set_registers(state.xgpiops_addr, OFFSET_GPIO_DIRM_0,    (uint32_t)(0x1<<14), (uint32_t)(0x0<<14));  // PIN12 as input (0: input, 1: output)
    set_registers(state.xgpiops_addr, OFFSET_GPIO_INTTYPE_0, (uint32_t)(0x1<<14), (uint32_t)(0x1<<14));  // 0: level-sensitive 1:Edge sensitive
    set_registers(state.xgpiops_addr, OFFSET_GPIO_INT_ANY_0, (uint32_t)(0x1<<14), (uint32_t)(0x1<<14));  // Trigger en both edge
    set_registers(state.xgpiops_addr, OFFSET_GPIO_INT_POL_0, (uint32_t)(0x1<<14), (uint32_t)(0x0<<14));  // cualquiera x

    // Left hc-sr04 echo  
    set_registers(state.xgpiops_addr, OFFSET_GPIO_DIRM_0,    (uint32_t)(0x1<<9), (uint32_t)(0x0<<9));   // PIN12 as input (0: input, 1: output)
    set_registers(state.xgpiops_addr, OFFSET_GPIO_INTTYPE_0, (uint32_t)(0x1<<9), (uint32_t)(0x1<<9));   // 0: level-sensitive 1:Edge sensitive
    set_registers(state.xgpiops_addr, OFFSET_GPIO_INT_ANY_0, (uint32_t)(0x1<<9), (uint32_t)(0x1<<9));   // Trigger en both edge
    set_registers(state.xgpiops_addr, OFFSET_GPIO_INT_POL_0, (uint32_t)(0x1<<9), (uint32_t)(0x0<<9));   // cualquiera x

    udelay(1);

    // Habilito interrupciones de los pines de entrada
    set_registers(state.xgpiops_addr, OFFSET_GPIO_INT_EN_0,  (uint32_t)(0xFFFFFFFF), (uint32_t) ((0x1<<12) | (0x1<<14) | (0x1<<9)));

    udelay(1);
    pr_info("Los pines habilitados son: %08X\n", ioread32(state.xgpiops_addr + OFFSET_GPIO_INT_MASK_0) );  // 0: int enabled, 1: no enabled 
    
    return 0;
} 

/*************************************************************************************************/
/**
  @brief Funcion que se ejecutara con el uso de la syscall close()

  @param inode
  @param file

  @returns 0: sin error, -1: error
**/
/*************************************************************************************************/
static int driver_release(struct inode *inode, struct file *file) 
{
  pr_info("driver_release: Entre a driver_release\n");

  kfree(state.TX_buff);
  kfree(state.RX_buff);  

  pr_info("driver_release: Salgo a driver_release\n");

  return 0;
}

/*************************************************************************************************/
/**
  @brief Funcion que se ejecutara con el uso de la syscall read()

  @returns 0: sin error, -1: error
**/
/*************************************************************************************************/


static ssize_t driver_read(struct file *file, char __user *ubuff, size_t size, loff_t *offset) 
{
    int counter;

    //pr_info("Entre a driver_read\n"); 

    //pr_info("Verifico si es valido el tamanio del buffer\n");  
    if(size != BYTE2READ)
    {
        pr_info("El tamanio del buffer no es valido\n");
        return -1;
    }

    //pr_info("Verifico si es valido el buffer\n");  
    if( (access_ok(VERIFY_WRITE, ubuff, size)) == 0)
    {
        pr_info("access_ok: El buffer es invalido\n");  
        return -1;
    }

    right_valid_value=0;
    center_valid_value=0;
    left_valid_value=0;

    /* Trigger */
    //set_registers(state.xgpiops_addr, OFFSET_GPIO_DATA_0, (uint32_t) ((0x1<<0) | (0x1<<13) | (0x1<<15)), (uint32_t)((0x1<<0) | (0x1<<13) | (0x1<<15)) );
    //udelay(10);
    //set_registers(state.xgpiops_addr, OFFSET_GPIO_DATA_0, (uint32_t) ((0x1<<0) | (0x1<<13) | (0x1<<15)), (uint32_t) ((0x0<<0) | (0x0<<13) | (0x0<<15)) );


    set_registers(state.xgpiops_addr, OFFSET_GPIO_DATA_0, (uint32_t)(0x1<<0), (uint32_t)(0x1<<0) );
    udelay(10);
    set_registers(state.xgpiops_addr, OFFSET_GPIO_DATA_0, (uint32_t)(0x1<<0), (uint32_t)(0x0<<0) );

    // Tengo que esperar que interrumpa y tenga el resultado
    counter=0;
    while ( center_valid_value == 0 ) {
      //pr_info("Espero la interrupcion rv: %d, cv: %d, lv: %d\n", right_valid_value, center_valid_value, left_valid_value);  
      counter++;
      // Out of range
      if (counter>50000) {
        //*(state.RX_buff) = -1;
              break;
      }
      udelay(1);
	  }

    set_registers(state.xgpiops_addr, OFFSET_GPIO_DATA_0, (uint32_t)(0x1<<13), (uint32_t)(0x1<<13) );
    udelay(10);
    set_registers(state.xgpiops_addr, OFFSET_GPIO_DATA_0, (uint32_t)(0x1<<13), (uint32_t)(0x0<<13) );

    // Tengo que esperar que interrumpa y tenga el resultado
    counter=0;
    while ( left_valid_value == 0 ) {
      //pr_info("Espero la interrupcion rv: %d, cv: %d, lv: %d\n", right_valid_value, center_valid_value, left_valid_value);  
      counter++;
      // Out of range
      if (counter>50000) {
        //*(state.RX_buff) = -1;
              break;
      }
      udelay(1);
	  }

    set_registers(state.xgpiops_addr, OFFSET_GPIO_DATA_0, (uint32_t)(0x1<<15), (uint32_t)(0x1<<15) );
    udelay(10);
    set_registers(state.xgpiops_addr, OFFSET_GPIO_DATA_0, (uint32_t)(0x1<<15), (uint32_t)(0x0<<15) );

    // Tengo que esperar que interrumpa y tenga el resultado
    counter=0;
    while ( right_valid_value == 0 ) {
      //pr_info("Espero la interrupcion rv: %d, cv: %d, lv: %d\n", right_valid_value, center_valid_value, left_valid_value);  
      counter++;
      // Out of range
      if (counter>50000) {
        //*(state.RX_buff) = -1;
              break;
      }
      udelay(1);
	  }

    //pr_info("Llego la interrupcion. rv: %d, cv: %d, lv: %d\n", right_valid_value, center_valid_value, left_valid_value); 
    //pr_info("Sensores r c l %lld %lld %lld\n", ktime_to_us( ktime_sub(right_echo_end,  right_echo_start) ), ktime_to_us( ktime_sub(center_echo_end, center_echo_start) ),  ktime_to_us( ktime_sub(left_echo_end,   left_echo_start) ) );
    
    state.RX_buff[0] = ktime_to_us( ktime_sub(right_echo_end,  right_echo_start) );
    state.RX_buff[1] = ktime_to_us( ktime_sub(center_echo_end, center_echo_start) );
    state.RX_buff[2] = ktime_to_us( ktime_sub(left_echo_end,   left_echo_start) );

    //pr_info("Sensores r c l %lld %lld %lld\n", *(state.RX_buff + 8*0), *(state.RX_buff + 8*1), *(state.RX_buff + 8*2) );

    /* Cargo el dato en el buffer del usuario */
    //pr_info("Cargo el buffer del usuario con la informacion\n");
    if(__copy_to_user(ubuff, state.RX_buff, size) != 0)
    {
        pr_info("__copy_to_user: Fallo __copy_to_user\n");
        return -1;
    }

    //pr_info("Salgo de driver_read\n"); 
    return 0;
}

/*************************************************************************************************/
/**
  @brief Funcion que se ejecutara con el uso de la syscall write()

  @returns 0: sin error, -1: error
**/
/*************************************************************************************************/


static ssize_t driver_write(struct file *file, const char __user *ubuff, size_t size, loff_t *offset) 
{
    //pr_info("Entre a driver_write\n"); 

    //pr_info("Verifico si es valido el tamanio del buffer\n");  
    if(size != BYTE2READ)
    {
        pr_info("El tamanio del buffer no es valido\n");
        return -1;
    }
    
    /* Cargo el dato en el buffer del kernel */
    //pr_info("Cargo el buffer del usuario con la informacion\n");
    if(copy_from_user(state.TX_buff, ubuff, size) != 0)
    {
        pr_info("Fallo __copy_from_user\n");
        return -1;
    }

    //pr_info("Voy a escribir = %08llX \n", *(state.TX_buff)); 

    //pr_info("Set GPIO Pin Data \n");
    //set_registers(state.xgpiops_addr, OFFSET_GPIO_DATA_0, (uint32_t)0xFFFFFFFF, (*(state.TX_buff) & ((0x1<<0) | (0x1<<13))) );
    //msleep(10);
    set_registers(state.xgpiops_addr, OFFSET_GPIO_DATA_0, (uint32_t)0xFFFFEFFF, *(state.TX_buff) );

    //pr_info("Salgo de driver_write\n"); 
    return 0;
}


/*************************************************************************************************/
/******************************** Estructura file_operations *************************************/
/**
    @brief Implementacion de las funciones del driver open, read, write, close, ioctl, cada driver
    tiene su propia file_operations
**/

static const struct file_operations myled_control_operations = {
    //.owner = THIS_MODULE,
    .open = driver_open,
    .read = driver_read,
    .write = driver_write,
    .release = driver_release,
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
  int status=0; // request_irq

  pr_info(" Hola! Entre a driver probed! \n");

  // Consigo informacion del devicetree DeviceTree
  state.res_xgpiops = platform_get_resource(pdev, IORESOURCE_MEM, 0);
  if(!state.res_xgpiops)
  {
      pr_err("platform_get_resources: No se pudo conseguir la memoria\n");
      return -ENODEV;
  } 
  pr_info("La memoria que voy a mapear en el kernel va desde: %08X a %08X ", state.res_xgpiops->start, state.res_xgpiops->end);

  // Esta funcion solo preserva el area para que no sea usada, no hace ningun tipo de mapeo 
  state.remap_xgpiops_size = state.res_xgpiops->end - state.res_xgpiops->start + 1;
  if (!request_mem_region(state.res_xgpiops->start, state.remap_xgpiops_size, pdev->name)) 
  {
      pr_err("request_mem_region: No se pudo conseguir I/O\n");
      return -ENODEV;
  }

  pr_info("La memoria que voy a mapear en el kernel va desde: %08X a %ld ", state.res_xgpiops->start, state.remap_xgpiops_size);
  state.xgpiops_addr = ioremap(state.res_xgpiops->start, state.remap_xgpiops_size);
  if (state.xgpiops_addr == NULL) {
      pr_err("No se pudo conseguir ioremap memory\n");
      return -ENODEV;
  }
  //////////////////////////////////////////////////////////////////////////////////////
  // Consigo informacion del devicetree DeviceTree
  //////////////////////////////////////////////////////////////////////////////////////
  state.res_mio_pin = platform_get_resource(pdev, IORESOURCE_MEM, 1);
  if(!state.res_mio_pin)
  {
      pr_err("platform_get_resources: No se pudo conseguir la memoria\n");
      return -ENODEV;
  } 

  // Esta funcion solo preserva el area para que no sea usada, no hace ningun tipo de mapeo 
  state.remap_mio_pin_size = state.res_mio_pin->end - state.res_mio_pin->start + 1;
  if (!request_mem_region(state.res_mio_pin->start, state.remap_mio_pin_size, pdev->name)) 
  {
      pr_err("request_mem_region: No se pudo conseguir I/O\n");
      return -ENODEV;
  }

  pr_info("La segunda memoria que voy a mapear en el kernel va desde: %08X a %08X ", state.res_mio_pin->start, state.res_mio_pin->end);

  state.mio_pin_addr = ioremap(state.res_mio_pin->start, state.remap_mio_pin_size);
  if (state.mio_pin_addr == NULL) {
      pr_err("No se pudo conseguir ioremap memory\n");
      return -ENODEV;
  }


  /* Voy a pedir la interrupcion */
  pr_info("%s: Pido interrupcion al kernel \n", pdev->name);
  if ((state.irq = platform_get_irq(pdev, 0)) < 0)
  {
      pr_err(DEVICE_NAME": platform_get_irq: No se pudo registrar el ISR\n");
      return -EPERM;    // -1
  }

  //state.irq = gpio_to_irq(12);

  /* Implantamos el ISR */
  pr_info(DEVICE_NAME": Implantamos el ISR \n");
  pr_info(DEVICE_NAME": Numero del IRQ del device: %d\n", state.irq);
  if ((status = request_irq(state.irq, driver_isr, IRQF_TRIGGER_HIGH | IRQF_DISABLED , pdev->name, NULL)) != 0) // Consultar IRQF_NO_SUSPEND
  {
      iounmap(state.mio_pin_addr);
      iounmap(state.xgpiops_addr);
      release_mem_region(state.res_mio_pin->start, state.remap_mio_pin_size);
      release_mem_region(state.res_xgpiops->start, state.remap_xgpiops_size);
      pr_err(DEVICE_NAME": request_irq: No se pudo registrar el ISR , estado: %d\n", status);
      return -EPERM;    // -1
  }
  pr_info("%s: ISR implantado \n", pdev->name);


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

    /* Free irq */
    free_irq(state.irq, driver_isr);
    
    /* Release mapped virtual address */
    iounmap(state.mio_pin_addr);
    iounmap(state.xgpiops_addr);

    /* Release the region */
    release_mem_region(state.res_mio_pin->start, state.remap_mio_pin_size);
    release_mem_region(state.res_xgpiops->start, state.remap_xgpiops_size);

    pr_info("driver_remove: Removi el dispositivo!\n");

    return 0;
 }

/*************************************************************************************************/
/*********************** Register myled control platform driver **********************************/

static int __init my_pdrv_init (void) 
{
  pr_info("my_pdrv_init: Hola mundo!\n");

  //No es necesario allocar cdev porque lo defini como struct cdev no como struct *cdev !!!
  //pr_info("%s: Obtengo memoria para allocar cdev struct\n", pdev->name);
  //(state.chardev) = cdev_alloc();    // Obtiene memoria para allocar la estructura 

  pr_info("my_pdrv_init: Intento allocar cdev\n");
  if (alloc_chrdev_region(&state.devtype, BASE_MINOR, MINOR_COUNT, DEVICE_NAME) != 0) 
  {
    pr_err("alloc_chrdev_region: Error no es posible asignar numero mayor\n");
    return -EBUSY;  // Device or resource busy 
  }
  pr_info("my_pdrv_init: Cdev struct allocada\n");


  /* Procedemos a registrar el dispositivo en el sistema */
  pr_info("my_pdrv_init: Procedo a registrar el dispositivo en el sistema\n");

  /* Para inicializarla se puede inicializar a mano o bien una vez definida file_operations...  */
  pr_info("%my_pdrv_init: Cargo cdev struct\n");
  cdev_init(&state.chardev, &myled_control_operations);

  /* Para agregarla al sistema */
  pr_info("my_pdrv_init: Procedo a agregar la estructura cdev al sistema\n");
  if (cdev_add(&state.chardev, state.devtype, MINOR_COUNT) != 0) 
  {
    pr_err("cdev_add: No se pude agregar el cdev\n");
    unregister_chrdev_region(state.devtype, MINOR_COUNT);
    return -EPERM;    // -1
  }
  pr_info("my_pdrv_init: Estructura cdev agregada al sistema\n");

  /* Voy a crear la clase */
  pr_info("my_pdrv_init: Voy a crear la clase \n");
  state.devclass = class_create(THIS_MODULE, DEVICE_CLASS_NAME);
  if (IS_ERR(state.devclass)) 
  {
    pr_err("class_create: No se pudo crear la clase\n");
    unregister_chrdev_region(state.devtype, MINOR_COUNT);
    cdev_del(&state.chardev);
    return PTR_ERR(state.devclass);   // Handling null pointer cap2 Linux Drivers Development
  }
  pr_info("my_pdrv_init: Clase creada \n");

  /* Voy a crear el dispositivo */
  pr_info("my_pdrv_init: Voy a crear el dispositivo \n");
  state.dev = device_create(state.devclass, DEVICE_PARENT, state.devtype, NULL, DEVICE_NAME);
  if (IS_ERR(state.dev)) 
  {
    pr_err("device_create: No se pudo crear el dispositivo\n");
    unregister_chrdev_region(state.devtype, MINOR_COUNT);
    cdev_del(&state.chardev);
    class_destroy(state.devclass);  // Destruyo la clase creada en el paso previo
    return PTR_ERR(state.dev);
  }
  pr_info("my_pdrv_init: Dispositivo creado \n");

  pr_info("my_pdrv_init: Finalmente platform_driver_register\n");
  if(platform_driver_register(&myled_control_pdriver) < 0)
  {
    pr_err("device_create: No se pudo crear el dispositivo\n");
    unregister_chrdev_region(state.devtype, MINOR_COUNT);
    cdev_del(&state.chardev);
    class_destroy(state.devclass);                  // Destruyo la clase creada en el paso previo
    device_destroy(state.devclass, state.devtype);  // Destruyo el device creado en el paso previo
    return PTR_ERR(state.dev);
  }

  pr_info("my_pdrv_init: Finalmente termine\n");
  return 0;
}
module_init(my_pdrv_init);


static void __exit my_pdrv_remove (void)    // se ejecuta cuando hago rmmod
{
  pr_info("my_pdrv_remove: Remuevo el dispositivo!\n");

  pr_info("my_pdrv_remove: DesRegistro el driver!\n"); 
  platform_driver_unregister(&myled_control_pdriver);
  pr_info("my_pdrv_remove: Destruyo el dispositivo!\n");  
  device_destroy(state.devclass, state.devtype);  
  pr_info("my_pdrv_remove: Destruyo la clase!\n");
  class_destroy(state.devclass); 
  pr_info("my_pdrv_remove: Quito cdev del sistema!\n");
  cdev_del(&state.chardev);       
  pr_info("my_pdrv_remove: Desaloco cdev!\n");
  unregister_chrdev_region(state.devtype, MINOR_COUNT);
}
module_exit(my_pdrv_remove);


/*************************************************************************************************/
/************************************ Module Information *****************************************/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Martin Fuschetto");
MODULE_DESCRIPTION("My platform leds control");
