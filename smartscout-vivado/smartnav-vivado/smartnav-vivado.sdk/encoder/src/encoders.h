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
	/** AXI GPIO ID */
	const static uint8_t AXI_GPIO_INTR_ID = XPAR_MICROBLAZE_0_AXI_INTC_AXI_GPIO_0_IP2INTC_IRPT_INTR;
	/** Encoders constructor */
	encoders(InterruptController &interrupt_controller) {
		int status;

		__encoder_count = 0;
		__init_io();
		status = interrupt_controller.connect_handler(AXI_GPIO_INTR_ID, (XInterruptHandler) gpio_isr, this);
		if (status != XST_SUCCESS)
			throw ("connect_handler: status != XST_SUCCESS. ");
		XGpio_InterruptEnable(&__gpio_driver, XPAR_AXI_GPIO_0_IP2INTC_IRPT_MASK);
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
	/** GPIO isr */
	static void gpio_isr(encoders* encoder_instance) {
		// From xilinx support its necessary disable,
		// the interrupt of the axi-gpio
		XGpio_InterruptDisable(&encoder_instance->__gpio_driver, XPAR_AXI_GPIO_0_IP2INTC_IRPT_MASK);
		// A new slits is being counted
		if (XGpio_ReadReg(XPAR_AXI_GPIO_0_BASEADDR, XPAR_AXI_GPIO_0_IP2INTC_IRPT_MASK))
			encoder_instance->__encoder_count++;
		// Clear the interrupt
		XGpio_InterruptClear(&encoder_instance->__gpio_driver, XPAR_AXI_GPIO_0_IP2INTC_IRPT_MASK);
		// Enable the interrupt
		XGpio_InterruptEnable(&encoder_instance->__gpio_driver, XPAR_AXI_GPIO_0_IP2INTC_IRPT_MASK);
	};
	/** Initialize the axi gpio */
	void __init_io() {
		XGpio_Initialize(&__gpio_driver, XPAR_AXI_GPIO_0_DEVICE_ID);
		// Channel 1, all inputs
		XGpio_SetDataDirection(&__gpio_driver, 1, 0xf);
		XGpio_InterruptClear(&__gpio_driver, 0x0);
	};

};

#endif /* SRC_ENCODERS_H_ */
