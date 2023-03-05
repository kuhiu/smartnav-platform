/*
 * mailbox.h
 *
 *  Created on: Feb 16, 2023
 *      Author: petalinux
 */

#ifndef SRC_MAILBOX_H_
#define SRC_MAILBOX_H_

#include "xmbox.h"
#include "xstatus.h"
#include "xparameters.h"
#include "xintc.h"
#include "interrupt_controller.h"

#define MBOX_DEVICE_ID		XPAR_MBOX_0_DEVICE_ID
#define MBOX_INTR_ID		XPAR_INTC_0_MBOX_0_VEC_ID

#define MAILBOX_RIT	3	/* mailbox receive interrupt threshold */
#define MAILBOX_SIT	4	/* mailbox send interrupt threshold */

class Mailbox {
public:
	/** Msg length */
	static const int message_length = 4;
	/** Mailbox constructor */
	Mailbox(InterruptController &interrupt_controller) {
		int status;

		// Lookup configuration data in the device configuration table.
		__config_mb = XMbox_LookupConfig(MBOX_DEVICE_ID);
		if (__config_mb == (XMbox_Config *)NULL)
			throw "__config_mb: NULL";
		// Mailbox init
		status = XMbox_CfgInitialize(&__mbox, __config_mb, __config_mb->BaseAddress);
		if (status != XST_SUCCESS)
			throw "status XMbox_CfgInitialize: failed";
		XMbox_SetSendThreshold(&__mbox, MAILBOX_SIT);
		XMbox_SetReceiveThreshold(&__mbox, MAILBOX_RIT);
		// Connect handler
		status = interrupt_controller.connect_handler(MBOX_INTR_ID, (XInterruptHandler) __mailbox_handler, this);
		if (status != XST_SUCCESS)
			throw "status __mailbox_setup_intr: failed";
		// Enable interrupts
		XMbox_SetInterruptEnable(&__mbox,
							 XMB_IX_STA | XMB_IX_RTA | XMB_IX_ERR);

	};
	/** Mailbox destructor */
	~Mailbox() = default;
	/** Read a new msg if exists */
	int newMsgRcvd(u32 *msg, int msg_length = message_length) {
		u32 bytes_recvd;
		int status = XST_FAILURE;

		if (__newMsg) {
			status = XMbox_Read(&__mbox, msg, msg_length*4, &bytes_recvd);
			__newMsg = false;
			if ( (msg[0] != 0xAA) && (msg[3] != 0x55) )
				status = XST_FAILURE;
		}
		return status;
	}
	/** Send a msg to the mailbox */
	int sendMsg(u32 *msg, int msg_length = message_length) {
		u32 bytes_sended;
		int status = XST_FAILURE;

		if ( (msg[0] == 0xAA) && (msg[3] == 0x55) ) {
			status = XMbox_Write(&__mbox, msg, msg_length*4, &bytes_sended);
		}

		return status;
	};

private:
	/** Mailbox config */
	XMbox_Config* __config_mb;
	/** Mailbox */
	XMbox __mbox;
	/** Msg received */
	bool __newMsg;
	/** Mailbox handler */
	static void __mailbox_handler(Mailbox* mailbox_instance) {
		uint32_t mask;
		XMbox* mbox = &(mailbox_instance->__mbox);
		mask = XMbox_GetInterruptStatus(mbox);
		if (mask & XMB_IX_STA) {

		}
		if (mask & XMB_IX_RTA) {
			mailbox_instance->__newMsg = true;
		}
		if (mask & XMB_IX_ERR) {

		}
		XMbox_ClearInterrupt(mbox, mask);
	};

};


#endif /* SRC_MAILBOX_H_ */
