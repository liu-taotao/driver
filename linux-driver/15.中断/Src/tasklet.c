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
#include <linux/timer.h>
#include <linux/jiffies.h>
#include <linux/string.h>
#include <linux/irq.h>
#include <linux/interrupt.h>


#define IMX6UIRQ_CNT     1
#define IMX6UIRQ_NAME    "imx6uirq"

#define KEY_NUM         1
#define KEY0VALUE       0X01    /*有效*/
#define INVAKEY         0XFF    /*无效*/
/*key结构体*/
struct irq_keydesc {
        int gpio;               /*io编号*/
        int irqnum;             /*中断号*/
        unsigned char value;    /*键值*/
        char name[10];          /*名字*/   


        irqreturn_t (*handler) (int,void *);       /*中断处理函数*/

        struct tasklet_struct tasklet;  /*下半部*/
};


/*imx6uirq设备结构体*/
struct imx6uirq_dev {
        dev_t devid;            /*设备号*/
        int major;
        int minor;

        struct cdev cdev;

        struct class *class;
        struct device *device;

        struct device_node *nd;

        struct irq_keydesc irqkey[KEY_NUM];

        struct timer_list timer;        /*定时器*/

        /*原子操作*/
        atomic_t keyvalue;
        atomic_t releasekey;



};

struct imx6uirq_dev imx6uirq; /*irq 设备*/


static int imx6uirq_open(struct inode *inode,struct file *filp)
{
        filp->private_data = &imx6uirq;
        return 0;
}

static int imx6uirq_release(struct inode *inode,struct file *filp)
{
        return 0;
}

static ssize_t imx6uirq_write(struct file *filp,const char __user *buf,size_t count,loff_t *ppos)
{

        return 0;
}

static ssize_t imx6uirq_read(struct file *filp,char __user *buf,size_t count,loff_t *ppos)
{
        int ret = 0;
        unsigned char keyvalue;
        unsigned char releasekey;
        struct imx6uirq_dev *dev = filp->private_data;

        keyvalue = atomic_read(&dev->keyvalue);
        releasekey = atomic_read(&dev->releasekey);

        if (releasekey) {       /*如果是有效按键*/
                if (keyvalue & 0x80) {
                        keyvalue &= ~0x80;
                        ret = copy_to_user(buf,&keyvalue,sizeof(keyvalue));
                } else {
                        goto data_error;
                }
                atomic_set(&dev->releasekey,0); /*按下标志清零*/
        } else {
                goto data_error;
        }

        return ret;

data_error:
        return -EINVAL;
}
/*字符设备操作集*/
static const struct file_operations led_fops = {
        .owner          = THIS_MODULE,
        .open           = imx6uirq_open,
        .write          = imx6uirq_write,
        .read           = imx6uirq_read,
        .release        = imx6uirq_release,
};


/*中断处理函数*/
static irqreturn_t key0_handler(int irq,void *dev_id)
{

        struct imx6uirq_dev *dev = dev_id;

#if 0
        value = gpio_get_value(dev->irqkey[0].gpio);
        if (value == 0) {       /*按下*/
                printk("key0 push!\r\n");

        } else if (value == 1) {        /*释放*/
                printk("key0 releale!\r\n");
        }
#endif

#if 0
        /*dev_id就是imx6uirq*/
        dev->timer.data = (volatile unsigned long)dev_id; /*强制类型转换，因为data是括号里面的类型*/
        /*消抖*/
        mod_timer(&dev->timer,jiffies + msecs_to_jiffies(20));         /*10s定时*/
#endif
        tasklet_schedule(&dev->irqkey[0].tasklet);

        return IRQ_HANDLED;
}

/*tasklet*/
static void key_tasklet(unsigned long data)
{

        struct imx6uirq_dev *dev = (struct imx6uirq_dev *)data;

        printk("liut key_tasklet\r\n");
        /*dev_id就是imx6uirq*/
        dev->timer.data = (volatile unsigned long)data; /*强制类型转换，因为data是括号里面的类型*/
        /*消抖*/
        mod_timer(&dev->timer,jiffies + msecs_to_jiffies(20));         /*10s定时*/

}

/*定时器处理函数 进行一个消抖*/
static void timer_func(unsigned long arg)
{
        int value = 0;
        struct imx6uirq_dev *dev = (struct imx6uirq_dev *)arg;
        value = gpio_get_value(dev->irqkey[0].gpio);

        if (value == 0) {       /*按下*/
        atomic_set(&dev->keyvalue,dev->irqkey[0].value); /*后者值写给前者*/
                printk("key0 push!\r\n");

        } else if (value == 1) {        /*释放*/
                atomic_set(&dev->keyvalue,0x80 | (dev->irqkey[0].value));
                atomic_set(&dev->releasekey,1); /*完整的按键过程*/
                printk("key0 releale!\r\n");
        }

}

/*按键初始化*/
static int keyio_init(struct imx6uirq_dev *dev)
{
        int ret = 0;
        int i = 0;

        /*1、按键初始化*/
        dev->nd = of_find_node_by_path("/key");
        if (dev->nd == NULL) {
                ret = -EINVAL;
                goto fail_nd;
        }

        /*2、获取IO的编号 有很多io就用循环获取*/
        for(i = 0; i < KEY_NUM; i++) {
                dev->irqkey[i].gpio = of_get_named_gpio(imx6uirq.nd,"key-gpios",i);
                if (dev->irqkey[i].gpio < 0) {
                        printk("cat't find io \r\n");
                        ret = -EINVAL;
                        goto fail_gpio;
                }
                printk("get gpio num is %d\r\n",dev->irqkey[i].gpio);
        }

        /*3、申请io 依据上面*/
        for(i = 0; i < KEY_NUM; i++) {
                memset(dev->irqkey[i].name,0,sizeof(dev->irqkey[i].name));
                sprintf(dev->irqkey[i].name,"key%d",i);
                ret = gpio_request(dev->irqkey[i].gpio,dev->irqkey[i].name);
                if (ret) {
                        ret = -EBUSY;
                        printk("IO %d cat't request\r\n",dev->irqkey[i].gpio);
                        goto fail_request;
                }

                /*同时设置io口为输入*/
                ret = gpio_direction_input(dev->irqkey[i].gpio);
                if (ret < 0) {
                        ret = -EINVAL;
                        goto fail_gpioset;
                }

                /*获取中断号*/
                dev->irqkey[i].irqnum = gpio_to_irq(dev->irqkey[i].gpio);

#if 0
/*获取中断号两个函数都可以*/
dev->irqkey[i].irqnum = gpio_to_irq(dev->irqkey[i].gpio);

/*下面这个是通用的*/
dev->irqkey[i].irqnum = irq_of_parse_and_map(dev->nd,i);

#endif
        }


        dev->irqkey[0].handler = key0_handler;
        dev->irqkey[0].value = KEY0VALUE;

        /*4、按键中断初始化*/
        for (i = 0; i < KEY_NUM; i++) {
                /*第三个参数是触发方式*/
                ret = request_irq(dev->irqkey[i].irqnum,key0_handler,
                                        IRQF_TRIGGER_RISING|IRQF_TRIGGER_FALLING,
                                        dev->irqkey[i].name,&imx6uirq);
                if (ret) {
                        printk("irq %d request failed\r\n",dev->irqkey[i].irqnum);
                        goto fail_irq;
                }
                /*这里写死了，不管用的那几个io都是这个key_tasklet函数*/
                tasklet_init(&dev->irqkey[0].tasklet,key_tasklet,(unsigned long)dev);
       }


        /*5、初始化定时器*/
        init_timer(&imx6uirq.timer);
        /*6、注册定时器*/

        /*也就是当timer_func执行的时候它的参数对应的就是timer那个结构体 相当于arg*/
        imx6uirq.timer.function = timer_func;
        /*data 会传递给定时器的timer_func函数*/

        return 0;
fail_irq:
        for (i = 0; i < KEY_NUM; i++) {
                gpio_free(dev->irqkey[i].gpio);
        }
fail_gpioset:
        gpio_free(dev->irqkey[i].gpio);
fail_request:
fail_gpio:
fail_nd:

        return ret;
}

/*驱动入口函数*/
static int __init imx6uirq_init(void)
{
        /*1、注册字符设备驱动*/
        int ret = 0;

        imx6uirq.major = 0;      /*不给定设备号，由系统自动分配*/
        printk("hello liutao imx6uirq_init\r\n");
        if (imx6uirq.major) {            /*给定主设备号*/
                imx6uirq.devid = MKDEV(imx6uirq.major,0); /*主设备号和次设备号*/
                ret = register_chrdev_region(imx6uirq.devid,IMX6UIRQ_CNT,IMX6UIRQ_NAME);
        } else {        /*没给定设备号*/
                ret = alloc_chrdev_region(&imx6uirq.devid,0,IMX6UIRQ_CNT,IMX6UIRQ_NAME);/*第一个参数是申请到的*/
                /*保存申请到的主次设备号*/
                imx6uirq.major = MAJOR(imx6uirq.devid);
                imx6uirq.minor = MINOR(imx6uirq.devid);
        }
        if (ret < 0) {
                goto fail_devid;
        }
        printk("imx6uirq major = %d, minor = %d\r\n",imx6uirq.major,imx6uirq.minor);

        /*2、初始化cdev*/
        imx6uirq.cdev.owner = THIS_MODULE;
        cdev_init(&imx6uirq.cdev,&led_fops);     /*第二个参数是字符设备操作集*/
        
        /*3、添加cdev 其返回值在实际中要做处理*/
        ret = cdev_add(&imx6uirq.cdev,imx6uirq.devid,IMX6UIRQ_CNT);
        if (ret) {
                goto fail_cdevadd;
        }

        /*4、创建类*/
        imx6uirq.class = class_create(THIS_MODULE,IMX6UIRQ_NAME);
        if (IS_ERR(imx6uirq.class)) {    /*由于是指针类型需要判断是否创建成功*/
                ret = PTR_ERR(imx6uirq.class);
                goto fail_class;
        }

        /*5、创建设备 感觉也就是相当于在开发板 ls /dev/ 下出现这个设备*/
        imx6uirq.device = device_create(imx6uirq.class,NULL,imx6uirq.devid,NULL,IMX6UIRQ_NAME);
        if (IS_ERR(imx6uirq.device)) {    /*由于是指针类型需要判断是否创建成功*/
                ret = PTR_ERR(imx6uirq.device);
                goto fail_device;
        }

        /*初始化io*/
        ret = keyio_init(&imx6uirq);
        if (ret < 0) {
                goto fail_keyinit;
        }

        /*初始化原子变量*/
        atomic_set(&imx6uirq.keyvalue,INVAKEY);
        atomic_set(&imx6uirq.releasekey,0);
        return 0;

fail_keyinit:
fail_device:
        class_destroy(imx6uirq.class);
fail_class:
        cdev_del(&imx6uirq.cdev);
fail_cdevadd:
        unregister_chrdev_region(imx6uirq.devid,IMX6UIRQ_CNT);  /*释放设备号*/
fail_devid:
        return ret;
}

/*驱动出口函数*/
static void __exit imx6uirq_exit(void)
{
        int i = 0;
        printk("liutao imx6uirq_exit\r\n");

        /*1、释放中断*/
        for (i = 0; i < KEY_NUM; i++) {
                free_irq(imx6uirq.irqkey[i].irqnum,&imx6uirq);
        }

        /*2、释放io 申请后request一定要记得释放，不然会报错*/
        for (i = 0; i < KEY_NUM; i++) {
                gpio_free(imx6uirq.irqkey[i].gpio);
        }

        /*3、删除定时器*/
        del_timer(&imx6uirq.timer);
        
        /*注销字符设备驱动*/
        cdev_del(&imx6uirq.cdev);
        unregister_chrdev_region(imx6uirq.devid,IMX6UIRQ_CNT);

        /*先创建的类，后创建设备。所以要先销毁设备，再销毁类*/
        device_destroy(imx6uirq.class,imx6uirq.devid);
        class_destroy(imx6uirq.class);


}


module_init(imx6uirq_init);
module_exit(imx6uirq_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("liutao");