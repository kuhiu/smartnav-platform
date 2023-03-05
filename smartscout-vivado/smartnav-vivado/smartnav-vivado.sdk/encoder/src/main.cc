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

#define MICROBLAZE_THREAD_CMD_ASK_ENCODER_1 1
#define MICROBLAZE_THREAD_CMD_ASK_ENCODER_2 2
#define MICROBLAZE_THREAD_CMD_LED_CONTROL 3

int main() {
	int status;
	// Interrupt controller
	InterruptController interrupt_controller;
	// Encoders object
	encoders::gpio_info __gpio_0;
	__gpio_0.ID = XPAR_GPIO_0_DEVICE_ID;
	__gpio_0.BASE =  XPAR_AXI_GPIO_0_BASEADDR;
	__gpio_0.INTR_ID = XPAR_INTC_0_GPIO_0_VEC_ID;
	__gpio_0.MASK = encoders::channels::GPIO_CHANNEL1;
	encoders encoder_0(interrupt_controller, __gpio_0);
	// Encoders object
	encoders::gpio_info __gpio_1;
	__gpio_1.ID = XPAR_GPIO_2_DEVICE_ID;
	__gpio_1.BASE =  XPAR_AXI_GPIO_2_BASEADDR;
	__gpio_1.INTR_ID = XPAR_INTC_0_GPIO_2_VEC_ID;
	__gpio_1.MASK = encoders::channels::GPIO_CHANNEL1 ;
	encoders encoder_1(interrupt_controller, __gpio_1);
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
				case MICROBLAZE_THREAD_CMD_ASK_ENCODER_1:
					data[2] = encoder_0.getCount();
					mailbox.sendMsg(data);
					break;
				case MICROBLAZE_THREAD_CMD_ASK_ENCODER_2:
					data[2] = encoder_1.getCount();
					mailbox.sendMsg(data);
					break;
				default:
					break;
			}
		}
	}

	return 0;
}
