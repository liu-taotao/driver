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

#include <linux/of.h>
#include <linux/of_address.h>
#include <linux/of_gpio.h>
#include <asm/mach/map.h>
#include <asm/uaccess.h>
#include <asm/io.h>

#define GPIOLED_CNT     1
#define GPIOLED_NAME    "gpioled"

#define LEDOFF          0
#define LEDON           1

/*gpioled设备结构体*/
struct gpioled_dev {
        dev_t devid;            /*设备号*/
        int major;
        int minor;

        struct cdev cdev;

        struct class *class;
        struct device *device;

        struct device_node *nd;
        int led_gpio;
};

struct gpioled_dev gpioled; /*LED*/


static int led_open(struct inode *inode,struct file *filp)
{
        filp->private_data = &gpioled;
        return 0;
}

static int led_release(struct inode *inode,struct file *filp)
{
        return 0;
}

static ssize_t led_write(struct file *filp,const char __user *buf,size_t count,loff_t *ppos)
{
        struct gpioled_dev *dev = filp->private_data;
        int ret;
        unsigned int databuf[1];

        ret = copy_from_user(databuf,buf,count);
        if (ret < 0) {
                return -EFAULT;
        }
        /*开灯*/
        if (databuf[0] == LEDON) { 
              gpio_set_value(dev->led_gpio,0); /*获取私有数据，所以采用*/ 
        } else if (databuf[0] == LEDOFF) {
                /*关灯*/
                gpio_set_value(dev->led_gpio,1);
        }

        return 0;
}


/*字符设备操作集*/
static const struct file_operations led_fops = {
        .owner          = THIS_MODULE,
        .open           = led_open,
        .write          = led_write,
        .release        = led_release,
};



/*驱动入口函数*/
static int __init led_init(void)
{
        /*1、注册字符设备驱动*/
        int ret = 0;
        gpioled.major = 0;      /*不给定设备号，由系统自动分配*/
        printk("hello liutao led_init\r\n");
        if (gpioled.major) {            /*给定主设备号*/
                gpioled.devid = MKDEV(gpioled.major,0); /*主设备号和次设备号*/
                register_chrdev_region(gpioled.devid,GPIOLED_CNT,GPIOLED_NAME);
        } else {        /*没给定设备号*/
                alloc_chrdev_region(&gpioled.devid,0,GPIOLED_CNT,GPIOLED_NAME);/*第一个参数是申请到的*/
                /*保存申请到的主次设备号*/
                gpioled.major = MAJOR(gpioled.devid);
                gpioled.minor = MINOR(gpioled.devid);
        }
        printk("gpioled major = %d, minor = %d\r\n",gpioled.major,gpioled.minor);

        /*2、初始化cdev*/
        gpioled.cdev.owner = THIS_MODULE;
        cdev_init(&gpioled.cdev,&led_fops);     /*第二个参数是字符设备操作集*/
        
        /*3、添加cdev 其返回值在实际中要做处理*/
        cdev_add(&gpioled.cdev,gpioled.devid,GPIOLED_CNT);

        /*4、创建类*/
        gpioled.class = class_create(THIS_MODULE,GPIOLED_NAME);
        if (IS_ERR(gpioled.class)) {    /*由于是指针类型需要判断是否创建成功*/
                return PTR_ERR(gpioled.class);
        }

        /*5、创建设备 感觉也就是相当于在开发板 ls /dev/ 下出现这个设备*/
        gpioled.device = device_create(gpioled.class,NULL,gpioled.devid,NULL,GPIOLED_NAME);
        if (IS_ERR(gpioled.device)) {    /*由于是指针类型需要判断是否创建成功*/
                return PTR_ERR(gpioled.device);
        }




        /*第2部分，1、获取设备节点(因为在设备树下，我是在根节点下添加到)*/
        gpioled.nd = of_find_node_by_path("/gpioled");
        if (gpioled.nd == NULL) {
                ret = -EINVAL;
                goto fail_findnode;
        }

        /*2、获取LED所对应的GPIO*/
        gpioled.led_gpio = of_get_named_gpio(gpioled.nd,"led-gpios",0);
        if (gpioled.led_gpio < 0) {
                printk("cat't find led gpio\r\n");
                ret = -EINVAL;
                goto fail_findnode;
        }
        printk("led gpio num = %d\r\n",gpioled.led_gpio);

        /*3、申请IO*/
        ret = gpio_request(gpioled.led_gpio,"led-gpio");
        if (ret) {
                printk("Failed to request the led gpio\r\n");
                ret = -EINVAL;
                goto fail_findnode;
        }

        /*4、使用IO,设置为输出*/
        ret = gpio_direction_output(gpioled.led_gpio,1); /*低电平点亮，默认高电平*/
        if (ret) {
                goto fail_setoutput;
        }

        /*5、输出低电平，点亮LED灯*/
        gpio_set_value(gpioled.led_gpio,0);
        return 0;

fail_setoutput:
        gpio_free(gpioled.led_gpio);
fail_findnode:
        return ret;
}

/*驱动出口函数*/
static void __exit led_exit(void)
{
        printk("liutao led_exit\r\n");
        /*关灯，要先关灯后，才会摧毁其他*/
        gpio_set_value(gpioled.led_gpio,1);
        /*注销字符设备驱动*/
        cdev_del(&gpioled.cdev);
        unregister_chrdev_region(gpioled.devid,GPIOLED_CNT);

        /*先创建的类，后创建设备。所以要先销毁设备，再销毁类*/
        device_destroy(gpioled.class,gpioled.devid);
        class_destroy(gpioled.class);


        /*释放IO*/
        gpio_free(gpioled.led_gpio);



}


module_init(led_init);
module_exit(led_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("liutao");