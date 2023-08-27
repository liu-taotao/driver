
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/uaccess.h>
#include <linux/io.h>
#include <linux/cdev.h>
#include <linux/device.h>

#define NEWCHRLED_NAME "newchrdev"
#define NEWCHRLED_COUNT 1

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

/*device object*/
struct newchrled_dev{
    struct cdev cdev; /*zifushebei*/
    dev_t devid; /*device number*/
    struct class *class;
    struct device *device;
    int major;
    int minor;
};
struct newchrled_dev newchrled; /*led device*/
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

static int newchrled_open(struct inode *inode,struct file *filp)
{
    filp->private_data = &newchrled;
    return 0;
}

static int newchrled_release(struct inode *inode,struct file *filp)
{
    struct newchrled_dev *dev = (struct newchrled_dev*)filp->private_data;
    return 0;
}

static ssize_t newchrled_write(struct file *filp,const char __user *buf,size_t count,loff_t *ppos)
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



static const struct file_operations newchrled_fops = {
    .owner = THIS_MODULE,
    .write = newchrled_write,
    .open  = newchrled_open,
    .release = newchrled_release,

};


/*input*/
static int __init newchrled_init(void)
{
    int ret = 0;
    unsigned int val = 0;
    printk("newchrled_init\r\n");
    /*1.init led*/

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

    /*2.register device*/
    if(newchrled.major) {/*down is major and minor number*/
        newchrled.devid = MKDEV(newchrled.major,0);
        ret = register_chrdev_region(newchrled.devid,NEWCHRLED_COUNT,NEWCHRLED_NAME);
    } else {        /*no give device number*/
        ret = alloc_chrdev_region(&newchrled.devid,0,NEWCHRLED_COUNT,NEWCHRLED_NAME);
        newchrled.major = MAJOR(newchrled.devid);
        newchrled.minor = MINOR(newchrled.devid);
    }
    if (ret < 0) {
        printk("newchrled chrdev_region err\r\n");
        return -1;
    }
    printk("newchrled major = %d minor = %d\r\n",newchrled.major,newchrled.minor);

    /*3.register device*/
    newchrled.cdev.owner = THIS_MODULE;
    cdev_init(&newchrled.cdev,&newchrled_fops);
    ret = cdev_add(&newchrled.cdev,newchrled.devid,NEWCHRLED_COUNT);

    /*4.auto create dev */
    newchrled.class = class_create(THIS_MODULE,NEWCHRLED_NAME);
    if (IS_ERR(newchrled.class)) {
        return PTR_ERR(newchrled.class);
    }
    newchrled.device = device_create(newchrled.class,NULL,newchrled.devid,NULL,NEWCHRLED_NAME);

    if (IS_ERR(newchrled.device)) {
        return PTR_ERR(newchrled.device);
    }

    return 0;
}
/*output*/
static void __exit newchrled_exit(void)
{
    unsigned int val = 0;
    val = readl(GPIO1_DR);
    val |= (1 << 3); /*led is open while GPIO1_DR is 0*/
    writel(val,GPIO1_DR);

    /**/
    printk("newchrled_exit\r\n");
    /*iounmap*/
    iounmap(IMX6U_CCM_CCGR1);
    iounmap(SW_MUX_GPIO1_IO03);
    iounmap(SW_PAD_GPIO1_IO03);
    iounmap(GPIO1_DR);
    iounmap(GPIO1_GDIR);

    cdev_del(&newchrled.cdev);
    /*1.delete device nunber*/
    unregister_chrdev_region(newchrled.devid,NEWCHRLED_COUNT);
    
    /*3*/
    device_destroy(newchrled.class,newchrled.devid);
    /*4*/
    class_destroy(newchrled.class);
}


/*register derver*/
module_init(newchrled_init);
module_exit(newchrled_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("liutao");