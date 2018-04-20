#include <stdio.h>
#include <unistd.h>
#include <sys/reboot.h>
/*
* Commands accepted by the _reboot() system call.
*
* RESTART     Restart system using default command and mode.
* HALT        Stop OS and give system control to ROM monitor, if any.
* CAD_ON      Ctrl-Alt-Del sequence causes RESTART command.
* CAD_OFF     Ctrl-Alt-Del sequence sends SIGINT to init task.
* POWER_OFF   Stop OS and remove all power from system, if possible.
* RESTART2    Restart system using given command string.
* SW_SUSPEND  Suspend system using software suspend if compiled in.
* KEXEC       Restart system using a previously loaded Linux kernel
*/
#define LINUX_REBOOT_CMD_RESTART        0x01234567  /*无返回，直接重启*/
#define LINUX_REBOOT_CMD_HALT           0xCDEF0123  /*直接停止OS运行,并返回，用于故障*/
#define LINUX_REBOOT_CMD_CAD_ON         0x89ABCDEF  /*激活Ctrl-Alt-Del的reboot行为*/
#define LINUX_REBOOT_CMD_CAD_OFF        0x00000000  /*？？？无法关闭 */
#define LINUX_REBOOT_CMD_POWER_OFF      0x4321FEDC  /*停止OS运行,关闭电源，标准关机*/
#define LINUX_REBOOT_CMD_RESTART2       0xA1B2C3D4  /*和RESTART一样，区别是什么*/
#define LINUX_REBOOT_CMD_SW_SUSPEND     0xD000FCE2  /*软件休眠，可用于快速开机*/
#define LINUX_REBOOT_CMD_KEXEC          0x45584543  /*？？？*/
int main()
{
    if(reboot(LINUX_REBOOT_CMD_RESTART2) == -1) {
        perror("reboot");
    }
    
    return 0;
}
