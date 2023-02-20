#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>
#include <errno.h>
#include <sys/ioctl.h>

#define AXI_MAILBOX_IOC_NMAGICO 'd'
#define AXI_MAILBOX_IOC_NUM_MAX 1
#define AXI_MAILBOX_IOC_PUSH_BLOCKING _IO(AXI_MAILBOX_IOC_NMAGICO, 0)
#define AXI_MAILBOX_IOC_POP_BLOCKING _IO(AXI_MAILBOX_IOC_NMAGICO, 1)

#define MICROBLAZE_THREAD_CMD_ASK_ENCODER 1
#define MICROBLAZE_THREAD_CMD_LED_CONTROL 3

#define MSG_LENGTH 4

typedef struct msg_mailbox {
  /** msg to send or receive */
  char msg[MSG_LENGTH];
} msgMailbox;

int main(int argc, char **argv) {
    int fd;
    int ret;
    msgMailbox msg;
    int led_cmd;


    printf("Hello mailbox!\n");
    fd = open("/dev/axi_mailbox_0", O_RDWR);
    if (fd < 0) {
        printf("Open failed: %s", strerror(errno));
        return -1;
    }

    msg.msg[0] = 0xAA;
    msg.msg[1] = MICROBLAZE_THREAD_CMD_LED_CONTROL;
    printf("Do you wanna turn on the led?\n");
    scanf("%d", &led_cmd);
    if (led_cmd) 
        msg.msg[2] = 1;
    else 
        msg.msg[2] = 0;
    msg.msg[3] = 0x55;

    ret = ioctl(fd, AXI_MAILBOX_IOC_PUSH_BLOCKING, &msg);
    if (ret < 0) {
        printf("Ioctl failed: %s", strerror(errno));
        return -1;
    }

    printf("Ask encoder.\n");
    msg.msg[0] = 0xAA;
    msg.msg[1] = MICROBLAZE_THREAD_CMD_ASK_ENCODER;
    msg.msg[2] = 0;
    msg.msg[3] = 0x55;
    ret = ioctl(fd, AXI_MAILBOX_IOC_PUSH_BLOCKING, &msg);
    if (ret < 0) {
        printf("Ioctl failed: %s", strerror(errno));
        return -1;
    }
    printf("Waitting answer...\n");
    ret = ioctl(fd, AXI_MAILBOX_IOC_POP_BLOCKING, &msg);
    if (ret < 0) {
        printf("Ioctl failed: %s", strerror(errno));
        return -1;
    }
    printf("Answer, encoder count: %d\n", msg.msg[2]);
    return 0;
}
