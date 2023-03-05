/*
 * main.c
 *
 *  Created on: Feb 12, 2023
 *      Author: petalinux
 */

#include "xparameters.h"
#include "xgpio_l.h"
/************************** Constant Definitions *****************************/
#define LED 0x01 /* Assumes bit 0 of GPIO is connected to an LED */
/*
* The following constant maps to the Base address of the hardware
* instances that was created in the EDK XPS system.
*/
#define GPIO_REG_BASEADDR XPAR_AXI_GPIO_0_BASEADDR
/*
* The following constant is used to wait after an LED is turned on to make
* sure that it is visible to the human eye. This constant might need to be
* tuned for faster or slower processor speeds.
*/
#define LED_DELAY 100000000
/*
* The following constant is used to determine which channel of the GPIO is
* used for the LED if there are 2 channels supported.
*/
#define LED_CHANNEL 1
/*****************************************************************************
* The purpose of this function is to illustrate how to use the GPIO low level
* driver to turn on and off an LED.
*
* @param None
*
* @return Always 0
*
* @note
* The main function is returning an integer to prevent compiler warnings.
*
******************************************************************************/
int main()
{
	u32 Data;
	volatile int Delay;
	/*
	* Set the direction for all signals to be inputs except the LED output
	*/
	XGpio_WriteReg((GPIO_REG_BASEADDR), (((LED_CHANNEL - 1) * XGPIO_CHAN_OFFSET) + XGPIO_TRI_OFFSET), (~LED));
	/* Loop forever blinking the LED */
	while (1) {
	/*
	* Read the state of the data so that only the LED state can be
	* modified
	*/
	Data = XGpio_ReadReg(GPIO_REG_BASEADDR, ((LED_CHANNEL - 1) * XGPIO_CHAN_OFFSET) + XGPIO_DATA_OFFSET);
	/* Set the LED to the opposite state such that it blinks */
	if (Data & LED) {
	   XGpio_WriteReg((GPIO_REG_BASEADDR),((LED_CHANNEL - 1) * XGPIO_CHAN_OFFSET) + XGPIO_DATA_OFFSET, Data & ~LED);
	} else {
		XGpio_WriteReg((GPIO_REG_BASEADDR),((LED_CHANNEL - 1) * XGPIO_CHAN_OFFSET) + XGPIO_DATA_OFFSET,Data | LED);
	}
	/* Wait a small amount of time so that the LED is visible */
	for (Delay = 0; Delay < LED_DELAY; Delay++);
	}
	return 0;
}
