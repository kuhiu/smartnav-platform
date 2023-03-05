/*
 * encoders.h
 *
 *  Created on: Feb 12, 2023
 *      Author: petalinux
 */

#ifndef SRC_ENCODERS_H_
#define SRC_ENCODERS_H_

#include "xparameters.h"
#include "xil_io.h"
#include "xgpio.h"
#include "xintc.h"
#include "xintc_l.h"
#include "xil_exception.h"
#include "microblaze_sleep.h"

#include "interrupt_controller.h"

class encoders {
public:
	enum channels {
		/** GPIO channel 1 */
		GPIO_CHANNEL1 = 1,
		/** GPIO channel 2 */
		GPIO_CHANNEL2 = 2,

	};
	/** GPIO info struct */
	struct gpio_info {
		/** GPIO ID */
		uint32_t ID;
		/** GPIO BASE */
		uint32_t BASE;
		/** AXI GPIO ID */
		uint32_t INTR_ID;
		/** GPIO MASK */
		uint32_t MASK;
	};
	/** Encoders constructor */
	encoders(InterruptController &interrupt_controller, gpio_info gpioinfo) {
		int status;

		__gpio_info = gpioinfo;
		__encoder_count = 0;
		__init_io();
		status = interrupt_controller.connect_handler(__gpio_info.ID, (XInterruptHandler) gpio_isr, this);
		if (status != XST_SUCCESS)
			throw ("connect_handler: status != XST_SUCCESS. ");
		XGpio_InterruptEnable(&__gpio_driver, __gpio_info.MASK);
		XGpio_InterruptGlobalEnable(&__gpio_driver);
	};
	/** Encoders destructor */
	~encoders() = default;
	/** Getter the number of slits counted */
	uint32_t getCount() { return __encoder_count; };

private:
	/** GPIO driver instance */
	XGpio __gpio_driver;
	/** The number of slits counted by the encoder */
	uint32_t __encoder_count;
	/** GPIO information */
	gpio_info __gpio_info;
	/** GPIO isr */
	static void gpio_isr(encoders* encoder_instance) {
		// From xilinx support its necessary disable,
		// the interrupt of the axi-gpio
		XGpio_InterruptDisable(&encoder_instance->__gpio_driver, (encoder_instance->__gpio_info).MASK);
		// A new slits is being counted
		if (XGpio_ReadReg((encoder_instance->__gpio_info).BASE, (encoder_instance->__gpio_info).MASK))
			encoder_instance->__encoder_count++;
		// Clear the interrupt
		XGpio_InterruptClear(&encoder_instance->__gpio_driver, (encoder_instance->__gpio_info).MASK);
		// Enable the interrupt
		XGpio_InterruptEnable(&encoder_instance->__gpio_driver, (encoder_instance->__gpio_info).MASK);
	};
	/** Initialize the axi gpio */
	void __init_io() {
		XGpio_Initialize(&__gpio_driver, __gpio_info.ID);
		// Channel 1, all inputs
		XGpio_SetDataDirection(&__gpio_driver, 1, 0xf);
		XGpio_InterruptClear(&__gpio_driver, 0x0);
	};

};

#endif /* SRC_ENCODERS_H_ */
