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
#include <linux/of_irq.h>
#include <linux/interrupt.h>

#define DEVICE_NAME "vdma_control_chardev"                /* Define Driver Name */
#define DEVICE_CLASS_NAME "vdma_control_chardev_class"
//#define BYTE2READ 1*4                                     /* Cantidad de word de 32 bits que tengo que leer * 4 = Bytes 2 read */
#define BASE_MINOR 0                                      /* Base del numero menor */
#define MINOR_COUNT 1                                     /* Cantidad de numeros menores que voy a usar */
#define DEVICE_PARENT NULL

static int driver_probe (struct platform_device *pdev);
static int driver_remove (struct platform_device *pdev);


/*************************************************************************************************/
/***************************************** Registros *********************************************/
/*************************************************************************************************/
#define OFFSET_PARK_PTR_REG                     (uint32_t) 0x28    // Park mode ?? que es?
#define OFFSET_VERSION                          (uint32_t) 0x2c    // Registro version del VDMA

#define OFFSET_VDMA_S2MM_CONTROL_REGISTER       (uint32_t) 0x30    // Registro de control
#define OFFSET_VDMA_S2MM_STATUS_REGISTER        (uint32_t) 0x34    // Registro de estado
#define OFFSET_VDMA_S2MM_IRQ_MASK               (uint32_t) 0x3c    // Registro Error interrupt mask 
#define OFFSET_VDMA_S2MM_REG_INDEX              (uint32_t) 0x44    // Registro de indice
#define OFFSET_VDMA_S2MM_VSIZE                  (uint32_t) 0xa0    // Registro de tamanio vertical
#define OFFSET_VDMA_S2MM_HSIZE                  (uint32_t) 0xa4    // Registro de tamanio Horizontal 
#define OFFSET_VDMA_S2MM_FRMDLY_STRIDE          (uint32_t) 0xa8    // Registro de paso y frame delay
#define OFFSET_VDMA_S2MM_FRAMEBUFFER1           (uint32_t) 0xac    // Revisar???

/*************************************************************************************************/
/******************************************* FLAGS ***********************************************/
/*************************************************************************************************/
/* S2MM control register */
#define VDMA_CONTROL_REGISTER_START                     (uint32_t) 0x00000001      // Inicia el VDMA, vuelve a cero una vez comenzado
#define VDMA_CONTROL_REGISTER_CIRCULAR_PARK             (uint32_t) 0x00000002      // Modo circular, gira continuamente atraves del framebuffer
#define VDMA_CONTROL_REGISTER_RESET                     (uint32_t) 0x00000004      // Reset in progress
#define VDMA_CONTROL_REGISTER_GENLOCK_ENABLE            (uint32_t) 0x00000008      // Permite la sincronizacion de master/slave para cada canal de AXI (no lo uso)
#define VDMA_CONTROL_REGISTER_FrameCntEn                (uint32_t) 0x00000010      // Este registro limita la cantidad de frames a transmitir por IRQFrameCount CONTROL[16:23]
#define VDMA_CONTROL_REGISTER_INTERNAL_GENLOCK          (uint32_t) 0x00000080      // Genlock interno (no lo uso)
#define VDMA_CONTROL_REGISTER_WrPntr                    (uint32_t) 0x00000f00      // Setea Entidad controladora  ??? 
#define VDMA_CONTROL_REGISTER_FrmCtn_IrqEn              (uint32_t) 0x00001000      // Habilita interrupcion por Frame Count = 0 en el bit 12 del STATUS REGISTER
#define VDMA_CONTROL_REGISTER_DlyCnt_IrqEn              (uint32_t) 0x00002000      // Habilita la interrupcion por retraso en el conteo 
#define VDMA_CONTROL_REGISTER_ERR_IrqEn                 (uint32_t) 0x00004000      // Habilita la interrupcion por error
#define VDMA_CONTROL_REGISTER_Repeat_En                 (uint32_t) 0x00008000      // Repite el frame anterior en caso de error
#define VDMA_CONTROL_REGISTER_InterruptFrameCount       (uint32_t) 0x00ff0000      // Cantidad de frames a procesar (8 bits max 256) antes de alcanzar la interrupcion
#define VDMA_CONTROL_REGISTER_IRQDelayCount             (uint32_t) 0xff000000      // Este valor setea un contador de delay, se genera una interrupcion cuando llega a cero
                                                                        // y decrementa cuando s_axis_s2mm_tvalid

/* S2MM status register */
#define VDMA_STATUS_REGISTER_HALTED                     (uint32_t) 0x00000001      // Read-only                0: Running, 1: halted
#define VDMA_STATUS_REGISTER_VDMAInternalError          (uint32_t) 0x00000010      // Read or write-clear      1: Internal error detectado
#define VDMA_STATUS_REGISTER_VDMASlaveError             (uint32_t) 0x00000020      // Read-only                1: Slave error detectado
#define VDMA_STATUS_REGISTER_VDMADecodeError            (uint32_t) 0x00000040      // Read-only                1: Address Requerida invalidad
#define VDMA_STATUS_REGISTER_StartOfFrameEarlyError     (uint32_t) 0x00000080      // Read-only                1: Si el frame entrante es mas chico al programado
#define VDMA_STATUS_REGISTER_EndOfLineEarlyError        (uint32_t) 0x00000100      // Read-only                1: Si la linea no es del tamanio programado
#define VDMA_STATUS_REGISTER_StartOfFrameLateError      (uint32_t) 0x00000800      // Read-only                1: Si el frame entrante es mas grande al programado
#define VDMA_STATUS_REGISTER_FrameCountInterrupt        (uint32_t) 0x00001000      // Read-only                1: Cantidad de frame contados
#define VDMA_STATUS_REGISTER_DelayCountInterrupt        (uint32_t) 0x00002000      // Read-only                1: Delay count detectado
#define VDMA_STATUS_REGISTER_ErrorInterrupt             (uint32_t) 0x00004000      // Read-only                1: Interrupcion por error
#define VDMA_STATUS_REGISTER_EndOfLineLateError         (uint32_t) 0x00008000      // Read-only                1: Line size mas grande del programado
#define VDMA_STATUS_REGISTER_FrameCount                 (uint32_t) 0x00ff0000      // Read-only                1: Indica cuenta actual de la cantidad de frames
#define VDMA_STATUS_REGISTER_DelayCount                 (uint32_t) 0xff000000      // Read-only                1: Indica cuenta actual del delay 

/*************************************************************************************************/
/***************************************** mem map   *********************************************/
/*************************************************************************************************/
#define BASE_FRAME_BUFFER                               (uint32_t) 0x01000000
//#define WIDTH         640
//#define HEIGHT        480
#define WIDTH           320
#define HEIGHT          240
#define PIXEL_LENGHT    4                        


/*************************************************************************************************/
/************************************* Estructuras  vdma_handle ****************************************/
/*************************************************************************************************/
static struct vdma_handle{

  /* VDMA driver */
  void __iomem *base_addr_ctrl;     /* Vitual Base Address */
  struct resource *res_ctrl;        /* Device Resource Structure */
  unsigned long remap_size_ctrl;    /* Device Memory Size */
  /* Frame Buffer */ 
  void __iomem *base_addr_fb;       /* Vitual Base Address */
  struct resource *res_fb;          /* Device Resource Structure */
  unsigned long remap_size_fb;      /* Device Memory Size */
  int width;                        /* Ancho de la foto */
  int height;                       /* Largo de la foto */
  int pixelLength;                  /* Ancho del pixel */
  unsigned int *fbaddr;             /* Direccion del FrameBuffer */

  //void __iomem *_reg_cm_per;
  uint32_t *TX_buff;
  uint32_t *RX_buff;

  /* Creacion del char device */
  dev_t devtype;          // numero mayor y menor
  struct class *devclass; // class_create()
  struct device *dev;     // device_create()
  struct cdev chardev;    // cdev_add()

  int irq;

} vdma_handle;

/*************************************************************************************************/
/********************************* Estructuras  of_device_id *************************************/

static const struct of_device_id driver_of_match[] = {
{ .compatible = "vdma_control_driver" },
{ }
};

/*************************************************************************************************/
/********************************* Estructuras  platform_driver **********************************/

static struct platform_driver myvdma_control_pdriver = {
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
// volatile uint32_t get_register (void __iomem * reg, uint32_t offset)
// {
//   uint32_t out=0;

//   out=ioread32(reg + offset);
//   pr_info(DEVICE_NAME": get_register: Lei el registro: %8p y contiene %d \n", (reg+offset), out);

//   return out;
// }
/*************************************************************************************************/
/*************************************************************************************************/


int vdma_start(void){

  int interrupt_frame_count = 1;

  pr_info("El estado es... %08X\n", ioread32(vdma_handle.base_addr_ctrl+OFFSET_VDMA_S2MM_STATUS_REGISTER));

  // Reset VDMA
  set_registers(vdma_handle.base_addr_ctrl, OFFSET_VDMA_S2MM_CONTROL_REGISTER, VDMA_CONTROL_REGISTER_RESET, VDMA_CONTROL_REGISTER_RESET);

  // Espero que el reset termine 
  while ( ( (ioread32(vdma_handle.base_addr_ctrl+OFFSET_VDMA_S2MM_CONTROL_REGISTER) >> 2 ) & 0x01) != 0 )  // Espero SoftReset
  {
    pr_info(DEVICE_NAME": Esperando el reset...\n");
    mdelay(1);
  }
  pr_info(DEVICE_NAME": Reset completado \n");

  //pr_info("El estado es... %08X\n", ioread32(vdma_handle.base_addr_ctrl+OFFSET_VDMA_S2MM_STATUS_REGISTER));
  // Limpio todos los bits de error en el registro de estados
  set_registers(vdma_handle.base_addr_ctrl, OFFSET_VDMA_S2MM_STATUS_REGISTER, (uint32_t)0xFFFFFFFF, 0);
  //pr_info("El estado es limpio... %08X\n", ioread32(vdma_handle.base_addr_ctrl+OFFSET_VDMA_S2MM_STATUS_REGISTER));

  // Desenmascaro todas las interrupciones
  set_registers(vdma_handle.base_addr_ctrl, OFFSET_VDMA_S2MM_IRQ_MASK, (uint32_t)0x0f, (uint32_t)0x0);

  // Start S2MM in single buffering mode
  set_registers(vdma_handle.base_addr_ctrl, OFFSET_VDMA_S2MM_CONTROL_REGISTER, (uint32_t)0xFF0000,                     (interrupt_frame_count << 16) );
  set_registers(vdma_handle.base_addr_ctrl, OFFSET_VDMA_S2MM_CONTROL_REGISTER, VDMA_CONTROL_REGISTER_GENLOCK_ENABLE  , VDMA_CONTROL_REGISTER_GENLOCK_ENABLE );
  set_registers(vdma_handle.base_addr_ctrl, OFFSET_VDMA_S2MM_CONTROL_REGISTER, VDMA_CONTROL_REGISTER_INTERNAL_GENLOCK, VDMA_CONTROL_REGISTER_INTERNAL_GENLOCK);
  set_registers(vdma_handle.base_addr_ctrl, OFFSET_VDMA_S2MM_CONTROL_REGISTER, VDMA_CONTROL_REGISTER_CIRCULAR_PARK,    VDMA_CONTROL_REGISTER_CIRCULAR_PARK);
  set_registers(vdma_handle.base_addr_ctrl, OFFSET_VDMA_S2MM_CONTROL_REGISTER, VDMA_CONTROL_REGISTER_START,            VDMA_CONTROL_REGISTER_START);

  pr_info("El control es.. %08X\n", ioread32(vdma_handle.base_addr_ctrl+OFFSET_VDMA_S2MM_CONTROL_REGISTER));
  pr_info("El estado es... %08X\n", ioread32(vdma_handle.base_addr_ctrl+OFFSET_VDMA_S2MM_STATUS_REGISTER));
  // Espero que comience el VDMA
  while ( ((ioread32(vdma_handle.base_addr_ctrl + OFFSET_VDMA_S2MM_CONTROL_REGISTER) & 0x01 ) == 0) || ((ioread32(vdma_handle.base_addr_ctrl + OFFSET_VDMA_S2MM_STATUS_REGISTER) & 0x01 ) == 1 ) )   // Espero SoftReset
  {
    pr_info(DEVICE_NAME": Esperando al VDMA...\n");
    mdelay(1);
  }
  pr_info(DEVICE_NAME": El VDMA comenzo a correr \n");

  // Usa los primeros 16 frame pointer registers
  set_registers(vdma_handle.base_addr_ctrl, OFFSET_VDMA_S2MM_REG_INDEX, (uint32_t)0x01, (uint32_t)0x00);

  // Direccion fisica el FB
  set_registers(vdma_handle.base_addr_ctrl, OFFSET_VDMA_S2MM_FRAMEBUFFER1, (uint32_t)0xFFFFFFFF, (uint32_t)BASE_FRAME_BUFFER);

  // Registro Park 
  set_registers(vdma_handle.base_addr_ctrl, OFFSET_PARK_PTR_REG, (uint32_t)0xFFFFFFFF, (uint32_t)0x00);

  // Delay and Stride
  set_registers(vdma_handle.base_addr_ctrl, OFFSET_VDMA_S2MM_FRMDLY_STRIDE, (uint32_t)0x0000FFFF, (uint32_t)(vdma_handle.width*vdma_handle.pixelLength));

  // Tamanio de Linea horizontal 
  set_registers(vdma_handle.base_addr_ctrl, OFFSET_VDMA_S2MM_HSIZE, (uint32_t)0x0000FFFF, (uint32_t)(vdma_handle.width*vdma_handle.pixelLength));

  // Tamanio de Linea vertical, inicia la transmision
  set_registers(vdma_handle.base_addr_ctrl, OFFSET_VDMA_S2MM_VSIZE, (uint32_t)0x00000FFF, (uint32_t)(vdma_handle.height));
  pr_info("El VSIZE es... %08X\n", ioread32(vdma_handle.base_addr_ctrl + OFFSET_VDMA_S2MM_VSIZE));
  pr_info("El estado es... %08X\n", ioread32(vdma_handle.base_addr_ctrl+OFFSET_VDMA_S2MM_STATUS_REGISTER));

  return 0;
}


void vdma_init(void){

  vdma_handle.width  = WIDTH;
  vdma_handle.height = HEIGHT;
  vdma_handle.pixelLength = PIXEL_LENGHT;
  //*vdma_handle.fbaddr = BASE_FRAME_BUFFER;

}


/*************************************************************************************************/
/**
  @brief Funcion que se ejecutara con el uso de la syscall open()

  @returns 0: sin error, -1: error
**/
/*************************************************************************************************/

static int driver_open(struct inode *inode, struct file *file) 
{
  int i;

  pr_info("Hola! Entre a open! \n");

  pr_info("Inicializo registros del vdma \n");
  vdma_init();

  pr_info("Comienza el vdma \n");
  vdma_start();

  //pr_info("El primer pixel es= %s \n", buff);

  for (i=0;i<320*240;i++){
     iowrite32((uint32_t)0xFFFFFFFF, (vdma_handle.base_addr_fb + i*4) );
  }

  pr_info("El estado es... %08X\n", ioread32(vdma_handle.base_addr_ctrl+OFFSET_VDMA_S2MM_STATUS_REGISTER));
  //iowrite32(0, vdma_handle.base_addr_fb);

  pr_info("Chau! Sali de open! \n");
  return 0;
} 





/*************************************************************************************************/
/******************************** Estructura file_operations *************************************/
/**
    @brief Implementacion de las funciones del driver open, read, write, close, ioctl, cada driver
    tiene su propia file_operations
**/

static const struct file_operations myvdma_control_operations = {
    //.owner = THIS_MODULE,
    .open = driver_open,
    //.read = driver_read,
    //.write = driver_write,
    //.release = driver_release,
    //.unlocked_ioctl = driver_ioctl,
};

/*************************************************************************************************/
/**
  @brief Handler de interrupciones

  @param irq
  @param devid

  @returns 
**/
/*************************************************************************************************/
irqreturn_t driver_isr(int irq, void *devid, struct pt_regs *ptregs) 
{
  uint32_t irqstate;

  irqstate=ioread32(vdma_handle.base_addr_ctrl + OFFSET_VDMA_S2MM_STATUS_REGISTER);

  if (( (irqstate & VDMA_STATUS_REGISTER_FrameCountInterrupt)>> 12) == 0x1 ) 
  {
    pr_info("ISR: Frame Count!!!!\n");
    return IRQ_HANDLED;
  }

  if (( (irqstate & VDMA_STATUS_REGISTER_DelayCountInterrupt)>> 13) == 0x1 ) 
  {
    pr_info("ISR: Delay Count!!!!\n");
    return IRQ_HANDLED;
  }

  if (( (irqstate & VDMA_STATUS_REGISTER_ErrorInterrupt)>> 14) == 0x1 ) 
  {
    pr_info("ISR: Registro de estado!!!!\n");
    return IRQ_HANDLED;
  }
  pr_info(DEVICE_NAME": ISR: Interrupcion desconocida!!!!\n");
  return IRQ_HANDLED;
}


/*************************************************************************************************/
/**
  @brief Todos los recursos que utiliza el driver registrados en probe()

  @param pdev Struct platform_device

  @returns Error Handling, predefined errors in the kernel tree
**/
/*************************************************************************************************/

static int driver_probe (struct platform_device *pdev)
{
    int status=0; 

    pr_info(" Hola! Entre a driver probed! \n");

    /* Voy a pedir la interrupcion */
    pr_info("%s: Pido interrupcion al kernel \n", pdev->name);
    if ((vdma_handle.irq = platform_get_irq(pdev, 0)) < 0)
    {
      pr_err(DEVICE_NAME": platform_get_irq: No se pudo registrar el ISR\n");
      unregister_chrdev_region(vdma_handle.devtype, MINOR_COUNT);
      cdev_del(&vdma_handle.chardev);
      class_destroy(vdma_handle.devclass);          // Destruyo la clase creada en el paso previo
      device_destroy(vdma_handle.devclass, vdma_handle.devtype);  // Destruyo el device creado en el paso previo
      platform_driver_unregister(&myvdma_control_pdriver);
      return -EPERM;    // -1
    }
    

    /* Implantamos el ISR */
    pr_info(DEVICE_NAME": Implantamos el ISR \n");
    pr_info(DEVICE_NAME": Numero del IRQ del device: %d\n", vdma_handle.irq);
    if ((status = request_irq(vdma_handle.irq, (irq_handler_t)driver_isr, IRQF_TRIGGER_RISING, pdev->name, NULL)) != 0) // Consultar IRQF_NO_SUSPEND
    {
      pr_err(DEVICE_NAME": request_irq: No se pudo registrar el ISR\n");
      unregister_chrdev_region(vdma_handle.devtype, MINOR_COUNT);
      cdev_del(&vdma_handle.chardev);
      class_destroy(vdma_handle.devclass);          // Destruyo la clase creada en el paso previo
      device_destroy(vdma_handle.devclass, vdma_handle.devtype);  // Destruyo el device creado en el paso previo
      platform_driver_unregister(&myvdma_control_pdriver);
      return -EPERM;    // -1
    }
    pr_info("%s: ISR implantado \n", pdev->name);

    // Consigo informacion del devicetree DeviceTree
    vdma_handle.res_ctrl = platform_get_resource(pdev, IORESOURCE_MEM, 0);
    if(!vdma_handle.res_ctrl)
    {
        pr_err("platform_get_resources: No se pudo conseguir la memoria\n");
        return -ENODEV;
    } 

    pr_info("La memoria que voy a mapear en el kernel va desde: %08X a %08X \n", vdma_handle.res_ctrl->start, vdma_handle.res_ctrl->end);

    // Esta funcion solo preserva el area para que no sea usada, no hace ningun tipo de mapeo 
    vdma_handle.remap_size_ctrl = vdma_handle.res_ctrl->end - vdma_handle.res_ctrl->start + 1;
    if (!request_mem_region(vdma_handle.res_ctrl->start, vdma_handle.remap_size_ctrl, pdev->name)) 
    {
        pr_err("request_mem_region: No se pudo conseguir I/O\n");
        return -ENODEV;
    }

    //pr_info("La memoria que voy a mapear en el kernel va desde: %08X a %08X ", vdma_handle.res_ctrl->start, vdma_handle.res_ctrl->end);

    vdma_handle.base_addr_ctrl = ioremap(vdma_handle.res_ctrl->start, vdma_handle.remap_size_ctrl);
    if (vdma_handle.base_addr_ctrl == NULL) {
        pr_err("No se pudo conseguir ioremap memory\n");
        return -ENODEV;
    }

    printk(" base_Addr_Ctrl %lu - %p \n", (unsigned long)vdma_handle.base_addr_ctrl, vdma_handle.base_addr_ctrl);

    vdma_handle.res_fb = platform_get_resource(pdev, IORESOURCE_MEM, 1);
    if(!vdma_handle.res_fb)
    {
        pr_err("platform_get_resources: No se pudo conseguir la memoria\n");
        return -ENODEV;
    } 

    // Esta funcion solo preserva el area para que no sea usada, no hace ningun tipo de mapeo 
    vdma_handle.remap_size_fb = vdma_handle.res_fb->end - vdma_handle.res_fb->start + 1;
    if (!request_mem_region(vdma_handle.res_fb->start, vdma_handle.remap_size_fb, pdev->name)) 
    {
        pr_err("request_mem_region: No se pudo conseguir I/O\n");
        return -ENODEV;
    }

    pr_info("La memoria que voy a mapear en el kernel va desde: %08X a %08X \n", vdma_handle.res_fb->start, vdma_handle.res_fb->end);

    vdma_handle.base_addr_fb = ioremap(vdma_handle.res_fb->start, vdma_handle.remap_size_fb);
    if (vdma_handle.base_addr_fb == NULL) {
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
    iounmap(vdma_handle.base_addr_ctrl);
    /* Release the region */
    release_mem_region(vdma_handle.res_ctrl->start, vdma_handle.remap_size_ctrl);

    /* Release mapped virtual address */
    iounmap(vdma_handle.base_addr_fb);
    /* Release the region */
    release_mem_region(vdma_handle.res_fb->start, vdma_handle.remap_size_fb);

    /* Release IRQ */
    free_irq(vdma_handle.irq, NULL);

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
  //(vdma_handle.chardev) = cdev_alloc();    // Obtiene memoria para allocar la estructura 

  pr_info("my_pdrv_init: Intento allocar cdev\n");
  if (alloc_chrdev_region(&vdma_handle.devtype, BASE_MINOR, MINOR_COUNT, DEVICE_NAME) != 0) 
  {
    pr_err("alloc_chrdev_region: Error no es posible asignar numero mayor\n");
    return -EBUSY;  // Device or resource busy 
  }
  pr_info("my_pdrv_init: Cdev struct allocada\n");


  /* Procedemos a registrar el dispositivo en el sistema */
  pr_info("my_pdrv_init: Procedo a registrar el dispositivo en el sistema\n");

  /* Para inicializarla se puede inicializar a mano o bien una vez definida file_operations...  */
  pr_info("%my_pdrv_init: Cargo cdev struct\n");
  cdev_init(&vdma_handle.chardev, &myvdma_control_operations);

  /* Para agregarla al sistema */
  pr_info("my_pdrv_init: Procedo a agregar la estructura cdev al sistema\n");
  if (cdev_add(&vdma_handle.chardev, vdma_handle.devtype, MINOR_COUNT) != 0) 
  {
    pr_err("cdev_add: No se pude agregar el cdev\n");
    unregister_chrdev_region(vdma_handle.devtype, MINOR_COUNT);
    return -EPERM;    // -1
  }
  pr_info("my_pdrv_init: Estructura cdev agregada al sistema\n");

  /* Voy a crear la clase */
  pr_info("my_pdrv_init: Voy a crear la clase \n");
  vdma_handle.devclass = class_create(THIS_MODULE, DEVICE_CLASS_NAME);
  if (IS_ERR(vdma_handle.devclass)) 
  {
    pr_err("class_create: No se pudo crear la clase\n");
    unregister_chrdev_region(vdma_handle.devtype, MINOR_COUNT);
    cdev_del(&vdma_handle.chardev);
    return PTR_ERR(vdma_handle.devclass);   // Handling null pointer cap2 Linux Drivers Development
  }
  pr_info("my_pdrv_init: Clase creada \n");

  /* Voy a crear el dispositivo */
  pr_info("my_pdrv_init: Voy a crear el dispositivo \n");
  vdma_handle.dev = device_create(vdma_handle.devclass, DEVICE_PARENT, vdma_handle.devtype, NULL, DEVICE_NAME);
  if (IS_ERR(vdma_handle.dev)) 
  {
    pr_err("device_create: No se pudo crear el dispositivo\n");
    unregister_chrdev_region(vdma_handle.devtype, MINOR_COUNT);
    cdev_del(&vdma_handle.chardev);
    class_destroy(vdma_handle.devclass);  // Destruyo la clase creada en el paso previo
    return PTR_ERR(vdma_handle.dev);
  }
  pr_info("my_pdrv_init: Dispositivo creado \n");

  pr_info("my_pdrv_init: Finalmente platform_driver_register\n");
  if(platform_driver_register(&myvdma_control_pdriver) < 0)
  {
    pr_err("device_create: No se pudo crear el dispositivo\n");
    unregister_chrdev_region(vdma_handle.devtype, MINOR_COUNT);
    cdev_del(&vdma_handle.chardev);
    class_destroy(vdma_handle.devclass);                  // Destruyo la clase creada en el paso previo
    device_destroy(vdma_handle.devclass, vdma_handle.devtype);  // Destruyo el device creado en el paso previo
    return PTR_ERR(vdma_handle.dev);
  }

  pr_info("my_pdrv_init: Finalmente termine\n");
  return 0;
}
module_init(my_pdrv_init);


static void __exit my_pdrv_remove (void)    // se ejecuta cuando hago rmmod
{
  pr_info("my_pdrv_remove: Remuevo el dispositivo!\n");

  pr_info("my_pdrv_remove: DesRegistro el driver!\n"); 
  platform_driver_unregister(&myvdma_control_pdriver);
  pr_info("my_pdrv_remove: Destruyo el dispositivo!\n");  
  device_destroy(vdma_handle.devclass, vdma_handle.devtype);  
  pr_info("my_pdrv_remove: Destruyo la clase!\n");
  class_destroy(vdma_handle.devclass); 
  pr_info("my_pdrv_remove: Quito cdev del sistema!\n");
  cdev_del(&vdma_handle.chardev);       
  pr_info("my_pdrv_remove: Desaloco cdev!\n");
  unregister_chrdev_region(vdma_handle.devtype, MINOR_COUNT);
}
module_exit(my_pdrv_remove);

/*************************************************************************************************/
/************************************ Module Information *****************************************/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Martin Fuschetto");
MODULE_DESCRIPTION("My platform leds control");