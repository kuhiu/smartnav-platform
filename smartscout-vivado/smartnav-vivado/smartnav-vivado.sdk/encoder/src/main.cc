/*
 * Empty C++ Application
 */

#include "xgpio.h"
#include "xparameters.h"

#include "mailbox.h"
#include "encoders.h"
#include "interrupt_controller.h"
#include "memory"

#define LED_CHANNEL 1

#define MICROBLAZE_THREAD_CMD_ASK_ENCODER 1
#define MICROBLAZE_THREAD_CMD_LED_CONTROL 3

int main() {
	int status;
	// Interrupt controller
	InterruptController interrupt_controller;
	// Encoders object
	encoders encoders(interrupt_controller);
	// mailbox object
	Mailbox mailbox(interrupt_controller);
	// Start interrupt controller
	interrupt_controller.start();
	// Data received from mailbox
	u32 data[mailbox.message_length];

	/* Loop forever blinking the LED */
	while (1) {
		status = mailbox.newMsgRcvd(data);
		if (status != XST_FAILURE) {
			switch (data[1]) {		// msg CMD
				case MICROBLAZE_THREAD_CMD_LED_CONTROL:
					if (data[2]) 	// msg ARG
						XGpio_WriteReg(XPAR_AXI_GPIO_1_BASEADDR, ((LED_CHANNEL - 1) * XGPIO_CHAN_OFFSET) + XGPIO_DATA_OFFSET, 0x01);
					else
						XGpio_WriteReg(XPAR_AXI_GPIO_1_BASEADDR, ((LED_CHANNEL - 1) * XGPIO_CHAN_OFFSET) + XGPIO_DATA_OFFSET, 0x00);
					break;
				case MICROBLAZE_THREAD_CMD_ASK_ENCODER:
					data[2] = encoders.getCount();
					mailbox.sendMsg(data);
					break;
				default:
					break;
			}
		}
	}

	return 0;
}
