#include <linux/i2c.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <media/v4l2-subdev.h>

/* Defines */
#define I2C_BUS                     0
#define HMC5883L_I2C_ADDRESS     0x0D       // Fake board: 0x0D, original board: 0x1E

/* Registers */
#define QMC5883L_X_LSB           (uint32_t) 0x00
#define QMC5883L_X_MSB           (uint32_t) 0x01
#define QMC5883L_Y_LSB           (uint32_t) 0x02
#define QMC5883L_Y_MSB           (uint32_t) 0x03
#define QMC5883L_Z_LSB           (uint32_t) 0x04
#define QMC5883L_Z_MSB           (uint32_t) 0x05
#define QMC5883L_STATUS          (uint32_t) 0x06
#define QMC5883L_TEMP_LSB        (uint32_t) 0x07
#define QMC5883L_TEMP_MSB        (uint32_t) 0x08
#define QMC5883L_CONFIG          (uint32_t) 0x09
#define QMC5883L_CONFIG2         (uint32_t) 0x0A
#define QMC5883L_RESET           (uint32_t) 0x0B
#define QMC5883L_RESERVED        (uint32_t) 0x0C
#define QMC5883L_CHIP_ID         (uint32_t) 0x0D

/* Bit values for the STATUS register */
#define QMC5883L_STATUS_DRDY     0x01
#define QMC5883L_STATUS_OVL      0x02
#define QMC5883L_STATUS_DOR      0x04

/* Oversampling values for the CONFIG register */
#define QMC5883L_CONFIG_OS512    0b00000000
#define QMC5883L_CONFIG_OS256    0b01000000
#define QMC5883L_CONFIG_OS128    0b10000000
#define QMC5883L_CONFIG_OS64     0b11000000

/* Range values for the CONFIG register */
#define QMC5883L_CONFIG_2GAUSS   0b00000000
#define QMC5883L_CONFIG_8GAUSS   0b00010000

/* Rate values for the CONFIG register */
#define QMC5883L_CONFIG_10HZ     0b00000000
#define QMC5883L_CONFIG_50HZ     0b00000100
#define QMC5883L_CONFIG_100HZ    0b00001000
#define QMC5883L_CONFIG_200HZ    0b00001100

/* Mode values for the CONFIG register */
#define QMC5883L_CONFIG_STANDBY  0b00000000
#define QMC5883L_CONFIG_CONT     0b00000001

static struct state {
    struct i2c_client *client;
} state;


static struct i2c_board_info HMC5883L_i2c_board_info = {
    I2C_BOARD_INFO("HMC5883L", HMC5883L_I2C_ADDRESS)
};

static struct i2c_client *HMC5883L_client;


static int HMC5883L_probe(struct i2c_client *client, const struct i2c_device_id *id)
{
    struct state *dev; 
    uint32_t rec=0;

    pr_info("HMC5883L_probe: Hola, entre a probe!\n");

    if (client->addr != id->driver_data) {
        pr_info("HMC5883L_probe: Direccion equivada (es: %d)!\n", client->addr);
        //return -ENODEV;
    }

    memset(&state, 0, sizeof(state));
    dev = &state; 
    i2c_set_clientdata(client, dev);

    dev->client = client;

    pr_info("HMC5883L_probe: Inicializo el QMC5883L (falso HMC5883L) \n");
    
    rec = i2c_smbus_read_byte_data (client , QMC5883L_CHIP_ID);
    pr_info("i2c_smbus_read_byte_data: CHIP ID: %d \n", rec);

    pr_info("HMC5883L_probe: config2 reg \n");
    i2c_smbus_write_byte_data(client , QMC5883L_CONFIG2, (uint32_t)0x81 ); // No softreset, No rollover function, No interrupt

    pr_info("HMC5883L_probe: config reg \n");
    i2c_smbus_write_byte_data(client , QMC5883L_CONFIG, (uint32_t) 0x11);

    pr_info("HMC5883L_probe: reset reg \n");
    i2c_smbus_write_byte_data(client , QMC5883L_RESET, (uint32_t)0x01 );

    pr_info("HMC5883L: config: %08X, config2: %08X\n", i2c_smbus_read_byte_data (client , QMC5883L_CONFIG), i2c_smbus_read_byte_data (client , QMC5883L_CONFIG2));
    //pr_info("HMC5883L_probe: Read raw data \n");

    //pr_info("i2c_smbus_read_byte_data: %d \n", i2c_smbus_read_byte_data (client , QMC5883L_X_LSB));
    //pr_info("i2c_smbus_read_byte_data: %d \n", i2c_smbus_read_byte_data (client , QMC5883L_X_MSB));
    //pr_info("i2c_smbus_read_byte_data: %d \n", i2c_smbus_read_byte_data (client , QMC5883L_Y_LSB));
    //pr_info("i2c_smbus_read_byte_data: %d \n", i2c_smbus_read_byte_data (client , QMC5883L_Y_MSB));
    //pr_info("i2c_smbus_read_byte_data: %d \n", i2c_smbus_read_byte_data (client , QMC5883L_Z_LSB));
    //pr_info("i2c_smbus_read_byte_data: %d \n", i2c_smbus_read_byte_data (client , QMC5883L_Z_MSB));
    

    // if ( (rec = i2c_smbus_read_byte_data (client , 0x06)) != 'H') {
    //     pr_info("i2c_smbus_read_byte_data: %d \n", rec);
    //     //pr_info("HMC5883L_probe: No lei el idA: H \n");
    //     //return -1;
    // }

    pr_info("HMC5883L_probe: Termine!\n");

    return 0;
}

static int HMC5883L_remove(struct i2c_client *client)
{
    struct usense_device_descr *dev = i2c_get_clientdata(client);
    pr_info("Hola! Entre a HMC5883L_remove! \n");

    if(dev)
        i2c_set_clientdata(client, NULL);

    return 0;
}

// Generalmente se implementa una unica estructura del contolador 
// y se instancian todos los clientes en ella. ej. "HMC5883L". 

static struct i2c_device_id HMC5883L_idtable[] = {
	{ "HMC5883L", HMC5883L_I2C_ADDRESS },
	{ }
};


MODULE_DEVICE_TABLE(i2c, HMC5883L_idtable);

static struct i2c_driver HMC5883L_driver = {
	.driver = {
		.name	= "HMC5883L",
        .owner = THIS_MODULE,
	},

	.id_table	= HMC5883L_idtable,
	.probe		= HMC5883L_probe,
	.remove		= HMC5883L_remove,
};

//module_i2c_driver(HMC5883L_driver);


static int __init my_i2cdriver_init (void) 
{
    struct i2c_adapter *adapter = i2c_get_adapter(I2C_BUS);
    int ret;

    pr_info("my_i2cdriver_init: Hola mundo!\n");

    if(!adapter) {
        pr_info("my_i2cdriver_init: Error consiguiendo el adaptador! (fue el: %d)\n", I2C_BUS);
        return -ENODEV;
    }

    pr_info("my_i2cdriver_init: Creo nuevo device!\n");
    HMC5883L_client = i2c_new_device(adapter, &HMC5883L_i2c_board_info);
    if (!HMC5883L_client) {
        pr_info("i2c_new_device: Creando nuevo dispositivo!\n");
        i2c_put_adapter(adapter);
        return -1;
    }

    ret = i2c_add_driver(&HMC5883L_driver);
    if (ret < 0) {
        pr_info("i2c_add_driver: Agregando nuevo dispositivo!\n");
        i2c_unregister_device(HMC5883L_client);
        return ret;
    }

    return 0;
}
module_init(my_i2cdriver_init);

static void __exit my_i2cdriver_remove (void)    // se ejecuta cuando hago rmmod
{
    i2c_del_driver(&HMC5883L_driver);
    i2c_unregister_device(HMC5883L_client);
}
module_exit(my_i2cdriver_remove);

/*************************************************************************************************/
/************************************ Module Information *****************************************/
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Martin Fuschetto");
MODULE_DESCRIPTION("My i2c device HMC5883L driver");

