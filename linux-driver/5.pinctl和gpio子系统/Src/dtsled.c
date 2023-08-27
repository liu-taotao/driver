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
#include <linux/of_irq.h>

// #include <linux/of.h>
#include <linux/of_address.h>
// #include <linux/of_gpio.h>
// #include <asm/mach/map.h>
// #include <asm/uaccess.h>
// #include <asm/io.h>

#define DTSLED_CNT      1    /*设备号个数*/
#define DTSLED_NAME    "dtsled"    /*name*/

#define LEDOFF      0
#define LEDON       1
/*地址映射后的虚拟地址指针*/
static void __iomem *IMX6U_CCM_CCGR1;
static void __iomem *SW_MUX_GPIO1_IO03;
static void __iomem *SW_PAD_GPIO1_IO03;
static void __iomem *GPIO1_DR;
static void __iomem *GPIO1_GDIR;

/*led结构体*/
struct desled_dev{
    dev_t devid;            /*设备号*/
    struct cdev cdev;       /*字符设备*/
    struct class *class;    /*类*/
    struct device *device;  /*设备*/
    int major;              /*major number*/
    int minor;              /*次设备号*/

    struct device_node *nd; /*设备节点*/
};

struct desled_dev dtsled;   /*led设备*/

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

static int dtsled_open(struct inode *inode,struct file *filp)
{
    /*设置私有*/
    filp->private_data = &dtsled;
    return 0;
}

static int dtsled_release(struct inode *inode,struct file *filp)
{
    struct desled_dev *dev = (struct desled_dev*)filp->private_data;

    return 0;
}

static ssize_t dtsled_write(struct file *filp,const char __user *buf,size_t count,loff_t *ppos)
{
    struct desled_dev *dev = (struct desled_dev *)filp->private_data;
    int retvalue;
    unsigned char databuf[1];

    retvalue = copy_from_user(databuf,buf,count);
    if (retvalue < 0) {
        return -EFAULT;
    }
    /*led is open or close*/
    led_switch(databuf[0]);
    return 0;
}
/*字符设备操作集*/
static const struct file_operations dtsled_fops = {
    .owner      = THIS_MODULE,
    .write      = dtsled_write,
    .open       = dtsled_open,
    .release    = dtsled_release,
    
};

/*入口函数*/
static int __init dtsled_init(void)
{
    int ret = 0;
    const char *str;
    u32 regdata[10];
    u8 i = 0;
    unsigned int val = 0;
    printk("dtsled_init\r\n");

    /*注册字符设备*/
    /*1、申请设备号*/
    dtsled.major = 0;/*设备哈由内核分配*/
    if (dtsled.major) {/*给定设备号*/
        dtsled.devid = MKDEV(dtsled.major,0);
        ret = register_chrdev_region(dtsled.devid,DTSLED_CNT,DTSLED_NAME);

    } else {/*没有给定设备号*/
        ret = alloc_chrdev_region(&dtsled.devid,0,DTSLED_CNT,DTSLED_NAME);
        dtsled.major = MAJOR(dtsled.major);
        dtsled.minor = MINOR(dtsled.minor);
    }
    if(ret < 0) {
        goto fail_devid;
    }

    /*2、添加字符设备*/
    dtsled.cdev.owner = THIS_MODULE;
    cdev_init(&dtsled.cdev,&dtsled_fops);
    ret = cdev_add(&dtsled.cdev,dtsled.devid,DTSLED_CNT);
    if(ret < 0) {
        goto fail_cdev;
    }

    /*3、自动创建设备节点*/
    dtsled.class = class_create(THIS_MODULE,DTSLED_NAME);
    /*判断类是否创建成功*/
    if (IS_ERR(dtsled.class)) {
        ret = PTR_ERR(dtsled.class);
        goto fail_class;
    }

    /*设备*/
    dtsled.device = device_create(dtsled.class,NULL,dtsled.devid,NULL,DTSLED_NAME);
    /*判断设备是否创建成功*/
    if (IS_ERR(dtsled.device)) {
        ret = PTR_ERR(dtsled.device);
        goto fail_device;
    }


    /*获取设备树属性内容*/
    dtsled.nd = of_find_node_by_path("/alphaled");
    if (dtsled.nd == NULL) {
        ret = -EINVAL;
        goto fail_findnd;
    }    

    /*打印属性的值*/
    ret = of_property_read_string(dtsled.nd,"status",&str);
    if (ret < 0) {
        goto fail_rs;
    } else {
        printk("status = %s\r\n",str);
    }

    ret = of_property_read_string(dtsled.nd,"compatible",&str);
    if (ret < 0) {
        goto fail_rs;
    } else {
        printk("compatible = %s\r\n",str);
    }


    /*获取reg里面的值（相当于一个数组）*/
    ret = of_property_read_u32_array(dtsled.nd,"reg",regdata,10); /*自己定义的知道长度是10,如果不知道参考4工程*/
    if (ret < 0) {
        goto fail_rs;
    } else {
        printk("reg data:\r\n");
        for(i = 0; i < 10; i++)
        {
            printk("%#x ",regdata[i]);
        }
        printk("\r\n");
    }

#if 0
    /*led灯初始化*/

    /*1、初始化led灯，地址映射*/
    /*IMX6U_CCM_CCGR1 = ioremap(CCM_CCGR1_BASE,4);
    SW_MUX_GPIO1_IO03 = ioremap(SW_MUX_GPIO1_IO03_BASE,4);
    SW_PAD_GPIO1_IO03 = ioremap(SW_PAD_GPIO1_IO03_BASE,4);
    GPIO1_DR = ioremap(GPIO1_DR_BASE,4);
    GPIO1_GDIR = ioremap(GPIO1_GDIR_BASE,4);*/
    /*对应下面的地址*/
    /*reg = 	<0x020c406c 0x04  //CCM_CCGR1_BASE
			     0x020e0068 0x04  //SW_MUX_GPIO1_IO03_BASE
			     0x020e02f4 0x04  //SW_PAD_GPIO1_IO03_BASE
			     0x0209c000 0x04  //GPIO1_DR_BASE
			     0x0209c004 0x04>;//GPIO1_GDIR_BASE */

    IMX6U_CCM_CCGR1     = ioremap(regdata[0],regdata[1]);
    SW_MUX_GPIO1_IO03   = ioremap(regdata[2],regdata[3]);
    SW_PAD_GPIO1_IO03   = ioremap(regdata[4],regdata[5]);
    GPIO1_DR            = ioremap(regdata[6],regdata[7]);
    GPIO1_GDIR          = ioremap(regdata[8],regdata[9]);
#endif
    /*从获取到映射一步完成*/
    IMX6U_CCM_CCGR1     = of_iomap(dtsled.nd, 0);
    SW_MUX_GPIO1_IO03   = of_iomap(dtsled.nd, 1);
    SW_PAD_GPIO1_IO03   = of_iomap(dtsled.nd, 2);
    GPIO1_DR            = of_iomap(dtsled.nd, 3);
    GPIO1_GDIR          = of_iomap(dtsled.nd, 4);

    /*2.gpio init 初始化IO*/
    val = readl(IMX6U_CCM_CCGR1);
    val &= ~(3 << 26);/*clear old data bit26 27*/
    val |= 3 << 26; /*set bit26 27 == 1*/
    writel(val,IMX6U_CCM_CCGR1);

    writel(0x5,SW_MUX_GPIO1_IO03);/*设置复用*/
    writel(0x10b0,SW_PAD_GPIO1_IO03);/*设置电器属性*/

    val = readl(GPIO1_GDIR);
    val |= 1 << 3; /*bit3置1，设置为输出*/
    writel(val,GPIO1_GDIR);

    val = readl(GPIO1_DR);
   // val &= ~(1 << 3); /*led is open while GPIO1_DR is 0 but I want to it is close if begin*/
    val |= (1 << 3); /*bit3置1，关闭led*/
    writel(val,GPIO1_DR);
    return 0;

fail_rs:
fail_findnd:
    device_destroy(dtsled.class,dtsled.devid);/*到这一步证明前面创建设备成功了，那么就需要摧毁创建的设备*/
fail_device:
    class_destroy(dtsled.class); /*设备创建失败，但是此前类已经创建成功了*/
fail_class:
    cdev_del(&dtsled.cdev);
fail_cdev:
    unregister_chrdev_region(dtsled.devid,DTSLED_CNT);
fail_devid:
    return ret;

}
static void __exit dtsled_exit(void)
{
    printk("dtsled_exit\r\n");

    /*卸载设备时先关灯*/
    unsigned int val = 0;
    val = readl(GPIO1_DR);
    val |= (1 << 3);
    writel(val,GPIO1_DR);
    /*1、取消地址映射*/
    iounmap(IMX6U_CCM_CCGR1);
    iounmap(SW_MUX_GPIO1_IO03);
    iounmap(SW_PAD_GPIO1_IO03);
    iounmap(GPIO1_DR);
    iounmap(GPIO1_GDIR);

    /*释放设备号*/
    cdev_del(&dtsled.cdev);
    /*释放设备号*/
    unregister_chrdev_region(dtsled.devid,DTSLED_CNT);
    /*顺序时先创建类，在创建设备。所以要先摧毁设备,在摧毁类才可以*/
    device_destroy(dtsled.class,dtsled.devid);
    /*摧毁类*/
    class_destroy(dtsled.class);

}

/*注册驱动和卸载驱动*/
module_init(dtsled_init);
module_exit(dtsled_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("liutao");

