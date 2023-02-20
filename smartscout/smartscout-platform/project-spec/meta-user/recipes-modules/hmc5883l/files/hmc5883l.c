#include <linux/i2c.h>
#include <linux/init.h>
#include <linux/of_device.h>
#include <linux/module.h>
#include <linux/delay.h>
#include <media/v4l2-subdev.h>

#define DEBUG_HMC5883L 1
#if defined DEBUG_HMC5883L
#define DEBUG_PRINT(fmt, args...) pr_info( "DEBUG: %s:%d:%s(): " fmt, \
																						__FILE__, __LINE__, __func__, ##args)
#else
	#define DEBUG_PRINT(fmt, args...) /* Don't do anything in release builds */
#endif

#define I2C_BUS                     0
#define HMC5883L_I2C_ADDRESS     0x0D       // Fake board: 0x0D, original board: 0x1E

/* Registers */
#define QMC5883L_X_LSB       		 0x00
#define QMC5883L_X_MSB       		 0x01
#define QMC5883L_Y_LSB       		 0x02
#define QMC5883L_Y_MSB       		 0x03
#define QMC5883L_Z_LSB       		 0x04
#define QMC5883L_Z_MSB       		 0x05
#define QMC5883L_STATUS      		 0x06
#define QMC5883L_TEMP_LSB    		 0x07
#define QMC5883L_TEMP_MSB    		 0x08
#define QMC5883L_CONFIG      		 0x09
#define QMC5883L_CONFIG2     		 0x0A
#define QMC5883L_RESET       		 0x0B
#define QMC5883L_RESERVED    		 0x0C
#define QMC5883L_CHIP_ID     		 0x0D

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

static int HMC5883L_probe(struct i2c_client *client, const struct i2c_device_id *id);
static int HMC5883L_remove(struct i2c_client *client);


static struct i2c_device_id HMC5883L_idtable[] = {
	{ "HMC5883L", HMC5883L_I2C_ADDRESS },
	{ }
};

MODULE_DEVICE_TABLE(i2c, HMC5883L_idtable);

static const struct of_device_id HMC5883L_dt_ids[] = {
	{ "HMC5883L", HMC5883L_I2C_ADDRESS },
	{ }
};

MODULE_DEVICE_TABLE(of, HMC5883L_dt_ids);

static struct i2c_driver HMC5883L_driver = {
	.driver = {
		.name	= "HMC5883L",
		.of_match_table = of_match_ptr(HMC5883L_dt_ids),
    .owner = THIS_MODULE,
	},
	.id_table	= HMC5883L_idtable,
	.probe		= HMC5883L_probe,
	.remove		= HMC5883L_remove,
};

static int HMC5883L_probe(struct i2c_client *client, const struct i2c_device_id *id) {
	int ret;

	DEBUG_PRINT("HMC5883L_probe!\n");
	if (client->dev.of_node) {
		DEBUG_PRINT("data = %x.\n", (unsigned int) of_device_get_match_data(&client->dev));
	}
	DEBUG_PRINT("HMC5883L: config: %08X, config2: %08X\n", i2c_smbus_read_byte_data (client, QMC5883L_CONFIG), i2c_smbus_read_byte_data (client , QMC5883L_CONFIG2));
	// Get device id
	//ret = i2c_smbus_read_byte_data (client , QMC5883L_CHIP_ID);
	//DEBUG_PRINT("i2c_smbus_read_byte_data: CHIP ID: %d \n", ret);
	// No softreset, No rollover function, No interrupt
	i2c_smbus_write_byte_data(client , QMC5883L_RESET, (uint32_t)0x01 );
	//i2c_smbus_write_byte_data(client , QMC5883L_CONFIG2, (uint32_t)0x81 ); 
	//i2c_smbus_write_byte_data(client , QMC5883L_CONFIG2, (uint32_t)0x01 ); 
	i2c_smbus_write_byte_data(client , QMC5883L_CONFIG, (uint32_t) 0x1D);
	DEBUG_PRINT("HMC5883L: config: %08X, config2: %08X\n", i2c_smbus_read_byte_data (client, QMC5883L_CONFIG), i2c_smbus_read_byte_data (client , QMC5883L_CONFIG2));

	return 0;
}

static int HMC5883L_remove(struct i2c_client *client) {
	DEBUG_PRINT("Hi! HMC5883L_remove! \n");
	return 0;
}

// static int __init my_i2cdriver_init (void)  {
// 	return i2c_add_driver(&HMC5883L_driver);
// }
// module_init(my_i2cdriver_init);

// static void __exit my_i2cdriver_remove (void) {  
// 	i2c_del_driver(&HMC5883L_driver);
// }
// module_exit(my_i2cdriver_remove);

module_i2c_driver(HMC5883L_driver);

/* Standard module information */
MODULE_LICENSE("GPL");
MODULE_AUTHOR("Fuschetto Martin");
MODULE_DESCRIPTION("hmc5883l");
