#ifndef D437A6A4_1D1B_47D6_8E3D_D1462EF1D7D9
#define D437A6A4_1D1B_47D6_8E3D_D1462EF1D7D9

#define MSG_LENGTH 4

#define AXI_MAILBOX_IOC_NMAGICO 'd'
#define AXI_MAILBOX_IOC_NUM_MAX 1
#define AXI_MAILBOX_IOC_PUSH_BLOCKING _IO(AXI_MAILBOX_IOC_NMAGICO, 0)
#define AXI_MAILBOX_IOC_POP_BLOCKING _IO(AXI_MAILBOX_IOC_NMAGICO, 1)

/**
 * @brief msg to send or receive from user space 
 * 
 */
typedef struct msg_mailbox {
  /** msg to send or receive */
  int msg[4];
} msgMailbox;

#endif /* D437A6A4_1D1B_47D6_8E3D_D1462EF1D7D9 */
