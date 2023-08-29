#include <linux/types.h>
#include <linux/kernel.h>
#include <linux/delay.h>
#include <linux/ide.h>
#include <linux/init.h>
#include <linux/module.h>
#include <linux/errno.h>
#include <linux/gpio.h>
#include <linux/cdev.h>
#include <linux/device.h>
#include <linux/of_gpio.h>
#include <linux/semaphore.h>
#include <linux/timer.h>
#include <linux/irq.h>
#include <linux/wait.h>
#include <linux/poll.h>
#include <linux/fs.h>
#include <linux/fcntl.h>
#include <linux/platform_device.h>
#include <asm/mach/map.h>
#include <asm/uaccess.h>
#include <asm/io.h>



/*寄存器物理地址*/
#define CCM_CCGR1_BASE                  (0x020c406c)
#define SW_MUX_GPIO1_IO03_BASE          (0X020E0068)
#define SW_PAD_GPIO1_IO03_BASE          (0x020E02F4)
#define GPIO1_DR_BASE                   (0x0209C000)
#define GPIO1_GDIR_BASE                 (0x0209C004)

#define REGISTER_LENGTH                 4

static void leddevice_release(struct device *dev)
{
        printk("leddevice release\r\n");
}

/*resource结构体*/
static struct resource led_resources[] = {
        [0] = {
                .start  = CCM_CCGR1_BASE,
                .end    = CCM_CCGR1_BASE + REGISTER_LENGTH - 1,
                .flags  = IORESOURCE_MEM,
        },

        [1] = {
                .start  = SW_MUX_GPIO1_IO03_BASE,
                .end    = SW_MUX_GPIO1_IO03_BASE + REGISTER_LENGTH - 1,
                .flags  = IORESOURCE_MEM,
        },
        
        [2] = {
                .start  = SW_PAD_GPIO1_IO03_BASE,
                .end    = SW_PAD_GPIO1_IO03_BASE + REGISTER_LENGTH - 1,
                .flags  = IORESOURCE_MEM,
        },
        
        [3] = {
                .start  = GPIO1_DR_BASE,
                .end    = GPIO1_DR_BASE + REGISTER_LENGTH - 1,
                .flags  = IORESOURCE_MEM,
        },
        
        [4] = {
                .start  = GPIO1_GDIR_BASE,
                .end    = GPIO1_GDIR_BASE + REGISTER_LENGTH - 1,
                .flags  = IORESOURCE_MEM,
        },
};

/*注册的结构体*/
static struct platform_device leddevice = {
        .name           = "imx6ull-led",/*设备写的什么名字，驱动也要些什么名字*/
        .id             = -1,/*为-1表示次设备无ID*/
        .dev            = {
                .release  = leddevice_release,/*有什么资源释放，可以在这里去释放*/
        },

        /*跟资源有关的*/
        .num_resources = ARRAY_SIZE(led_resources),
        .resource = led_resources,

};

/*设备加载*/
static int __init leddevice_init(void)
{
        int ret = 0;
        printk("leddevice_init\r\n");

        /*注册platform设备*/
        ret = platform_device_register(&leddevice);/*里面是指针，所有要取指*/

        return ret;
}

/*设备卸载*/
static void __exit leddevice_exit(void)
{
        printk("leddevice_exit\r\n");
        /*卸载platform设备*/
        platform_device_unregister(&leddevice);
}


module_init(leddevice_init);
module_exit(leddevice_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("liutao");