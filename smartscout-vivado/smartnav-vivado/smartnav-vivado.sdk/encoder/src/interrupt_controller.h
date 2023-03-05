/*
 * interrupt_controller.h
 *
 *  Created on: Feb 16, 2023
 *      Author: petalinux
 */

#ifndef SRC_INTERRUPT_CONTROLLER_H_
#define SRC_INTERRUPT_CONTROLLER_H_

#include "xintc.h"

#define INTC_DEVICE_ID XPAR_INTC_0_DEVICE_ID

class InterruptController {
public:
	/* InterruptController constructor **/
	InterruptController() {
		int status;

		// Enable microblaze interrupt
		microblaze_enable_interrupts();
		// Initialize the interrupt controller driver
		status = XIntc_Initialize(&__intc_driver, INTC_DEVICE_ID);
		if (status != XST_SUCCESS) {
			throw "XIntc_Initialize: status !=XST_SUCCESS";
		}
	};
	/** InterruptController destructor */
	~InterruptController() = default;
	/** Connect a new handler to the interrupt controller */
	int connect_handler(uint32_t device_intr_id, XInterruptHandler handler, void* handler_arg) {
		int status;

		status = XIntc_Connect(&__intc_driver,
				device_intr_id,
				handler,
				handler_arg);
		if (status != XST_SUCCESS) {
			return XST_FAILURE;
		}
		XIntc_Enable(&__intc_driver, device_intr_id);

		return XST_SUCCESS;
	};
	/** Start the interrupt controller */
	int start() {
		int status;

		// Start interrupt controller
		status = XIntc_Start(&__intc_driver, XIN_REAL_MODE);
		if (status != XST_SUCCESS) {
			return XST_FAILURE;
		}

		// Initialize the exception table
		Xil_ExceptionInit();
		// Register the interrupt controller hanlder with the exception table
		Xil_ExceptionRegisterHandler(XIL_EXCEPTION_ID_INT,
					(Xil_ExceptionHandler)XIntc_InterruptHandler,
					&__intc_driver);
		// Enable exceptions
		Xil_ExceptionEnable();
		return 0;
	};

private:
	/** Interrupt controller driver */
	XIntc __intc_driver;

};


#endif /* SRC_INTERRUPT_CONTROLLER_H_ */
