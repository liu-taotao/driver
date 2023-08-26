
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/uaccess.h>
#include <linux/io.h>


#define LED_MAJOR   200
#define LED_NAME    "led"



/*hardware address*/
#define CCM_CCGR1_BASE  (0x020c406c)
#define SW_MUX_GPIO1_IO03_BASE  (0X020E0068)
#define SW_PAD_GPIO1_IO03_BASE (0x020E02F4)
#define GPIO1_DR_BASE (0x0209C000)
#define GPIO1_GDIR_BASE (0x0209C004)

/*address virtual pointer*/
static void __iomem *IMX6U_CCM_CCGR1;
static void __iomem *SW_MUX_GPIO1_IO03;
static void __iomem *SW_PAD_GPIO1_IO03;
static void __iomem *GPIO1_DR;
static void __iomem *GPIO1_GDIR;

#define LEDOFF 0
#define LEDON 1

/*led is open/close*/
static void led_switch(u8 sta)
{
    u32 val = 0;

    if(sta == LEDON) {
        val = readl(GPIO1_DR);
        val &= ~(1 << 3); /*led is open while GPIO1_DR is 0*/
        writel(val,GPIO1_DR);
    } else if(sta == LEDOFF) {
        val = readl(GPIO1_DR);
        val |= (1 << 3); /*led is open while GPIO1_DR is 0*/
        writel(val,GPIO1_DR);
    }
}

static int led_open(struct inode *inode,struct file *filp)
{
    return 0;
}

static int led_release(struct inode *inode,struct file *filp)
{
    return 0;
}

static ssize_t led_write(struct file *filp,const char __user *buf,size_t count,loff_t *ppos)
{
    int retvalue;
    unsigned char databuf[1];

    retvalue = copy_from_user(databuf,buf,count);
    if(retvalue < 0) {
        printk("kernel write failed\r\n");
        return -EFAULT;
    }
    /*led is open or close*/
    led_switch(databuf[0]);
    
    return 0;
}


/*ops*/
static const struct file_operations led_fops = {
    .owner = THIS_MODULE,
    .write = led_write,
    .open  = led_open,
    .release = led_release,
};

/*input */
static int __init led_init(void)
{
    int ret = 0;
    unsigned int val = 0;
    /*1.io init ioremap*/
    /*32bit->4*/
    IMX6U_CCM_CCGR1 = ioremap(CCM_CCGR1_BASE,4);
    SW_MUX_GPIO1_IO03 = ioremap(SW_MUX_GPIO1_IO03_BASE,4);
    SW_PAD_GPIO1_IO03 = ioremap(SW_PAD_GPIO1_IO03_BASE,4);
    GPIO1_DR = ioremap(GPIO1_DR_BASE,4);
    GPIO1_GDIR = ioremap(GPIO1_GDIR_BASE,4);

    /*2.gpio init*/
    val = readl(IMX6U_CCM_CCGR1);
    val &= ~(3 << 26);/*clear old data bit26 27*/
    val |= 3 << 26; /*set bit26 27 == 1*/
    writel(val,IMX6U_CCM_CCGR1);

    writel(0x5,SW_MUX_GPIO1_IO03);/*setting fuyong*/
    writel(0x10b0,SW_PAD_GPIO1_IO03);/*setting dianqisuxing*/

    val = readl(GPIO1_GDIR);
    val |= 1 << 3; /*output == 1*/
    writel(val,GPIO1_GDIR);

    val = readl(GPIO1_DR);
   // val &= ~(1 << 3); /*led is open while GPIO1_DR is 0 but I want to it is close if begin*/
    val |= (1 << 3);
    writel(val,GPIO1_DR);
    /*1.register_chrdev*/

    ret = register_chrdev(LED_MAJOR,LED_NAME,&led_fops);
    if (ret < 0) {
        printk("register chardev failed\r\n");
        return -EIO;
    }

    printk("led_init new\r\n");
    return 0;
}
/*output*/
static void __exit led_exit(void)
{
    unsigned int val = 0;
    val = readl(GPIO1_DR);
    val |= (1 << 3); /*led is open while GPIO1_DR is 0*/
    writel(val,GPIO1_DR);
    /*iounmap*/
    iounmap(IMX6U_CCM_CCGR1);
    iounmap(SW_MUX_GPIO1_IO03);
    iounmap(SW_PAD_GPIO1_IO03);
    iounmap(GPIO1_DR);
    iounmap(GPIO1_GDIR);

    unregister_chrdev(LED_MAJOR,LED_NAME);

    printk("led_exit\r\n");
}
module_init(led_init);
module_exit(led_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("liutao");