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

#define TIMER_CNT     1
#define TIMER_NAME    "timer"

/*timer设备结构体*/
struct timer_dev {
        dev_t devid;            /*设备号*/
        int major;
        int minor;

        struct cdev cdev;

        struct class *class;
        struct device *device;

        struct device_node *nd;
        int led_gpio;   /*灯的io编号*/

        struct timer_list timers;        /*定时器定义*/


};

struct timer_dev timer; /*tiemr*/


static int timer_open(struct inode *inode,struct file *filp)
{
        filp->private_data = &timer;
        return 0;
}

static int timer_release(struct inode *inode,struct file *filp)
{
        return 0;
}

static ssize_t timer_write(struct file *filp,const char __user *buf,size_t count,loff_t *ppos)
{

        return 0;
}

static ssize_t timer_read(struct file *filp,char __user *buf,size_t count,loff_t *ppos)
{

        int ret = 0;


        return ret;
}
/*字符设备操作集*/
static const struct file_operations led_fops = {
        .owner          = THIS_MODULE,
        .open           = timer_open,
        .write          = timer_write,
        .read           = timer_read,
        .release        = timer_release,
};


/*定时器处理函数 里面的arg对应就是struct timer_dev timer; */
static void timer_func(unsigned long arg)
{
        struct timer_dev *dev = (struct timer_dev*)arg;
        static int sta = 1;     /*表示状态 每次翻转一次*/

        sta = !sta;
        gpio_set_value(dev->led_gpio,sta);

        /*重新启动定时器*/
        mod_timer(&dev->timers,jiffies + msecs_to_jiffies(500));
}

/* 初始化LED灯*/
int led_init(struct timer_dev *dev)
{
        int ret = 0;
        /*1、获取节点*/
        dev->nd = of_find_node_by_path("/gpioled");
        if (dev->nd == NULL) {
                ret = -EINVAL;
                goto fail_nd;
        }

        /*2、获取对应的io*/
        dev->led_gpio = of_get_named_gpio(dev->nd,"led-gpios",0);
        if (dev->led_gpio < 0) {
                printk("cat't find led gpio\r\n");
                ret = -EINVAL;
                goto fail_gpio;
        }
        printk("led gpio num is %d\r\n",dev->led_gpio);

        /*3、申请IO*/
        ret = gpio_request(dev->led_gpio,"led");
        if (ret) {
                ret = -EBUSY;
                printk("IO %d cat't request\r\n",dev->led_gpio);
                goto fail_request;
        }

        /*4、设置为输出*/
        ret = gpio_direction_output(dev->led_gpio,1); /*默认设置为1 是高电平 关灯*/
        if (ret < 0) {
                ret = -EINVAL;
                goto fail_gpioset;
        }

        return 0;
fail_gpioset:
        gpio_free(dev->led_gpio);
fail_request:
fail_gpio:
fail_nd:
        return ret;

}


/*驱动入口函数*/
static int __init timer_init(void)
{
        /*1、注册字符设备驱动*/
        int ret = 0;

        timer.major = 0;      /*不给定设备号，由系统自动分配*/
        printk("hello liutao timer_init\r\n");
        if (timer.major) {            /*给定主设备号*/
                timer.devid = MKDEV(timer.major,0); /*主设备号和次设备号*/
                ret = register_chrdev_region(timer.devid,TIMER_CNT,TIMER_NAME);
        } else {        /*没给定设备号*/
                ret = alloc_chrdev_region(&timer.devid,0,TIMER_CNT,TIMER_NAME);/*第一个参数是申请到的*/
                /*保存申请到的主次设备号*/
                timer.major = MAJOR(timer.devid);
                timer.minor = MINOR(timer.devid);
        }
        if (ret < 0) {
                goto fail_devid;
        }
        printk("timer major = %d, minor = %d\r\n",timer.major,timer.minor);

        /*2、初始化cdev*/
        timer.cdev.owner = THIS_MODULE;
        cdev_init(&timer.cdev,&led_fops);     /*第二个参数是字符设备操作集*/
        
        /*3、添加cdev 其返回值在实际中要做处理*/
        ret = cdev_add(&timer.cdev,timer.devid,TIMER_CNT);
        if (ret) {
                goto fail_cdevadd;
        }

        /*4、创建类*/
        timer.class = class_create(THIS_MODULE,TIMER_NAME);
        if (IS_ERR(timer.class)) {    /*由于是指针类型需要判断是否创建成功*/
                ret = PTR_ERR(timer.class);
                goto fail_class;
        }

        /*5、创建设备 感觉也就是相当于在开发板 ls /dev/ 下出现这个设备*/
        timer.device = device_create(timer.class,NULL,timer.devid,NULL,TIMER_NAME);
        if (IS_ERR(timer.device)) {    /*由于是指针类型需要判断是否创建成功*/
                ret = PTR_ERR(timer.device);
                goto fail_device;
        }


      
        /*在定时器初始化之前初始化灯
          因为定时器开始后要使用led*/
        led_init(&timer);
        if (ret < 0) {
                goto fail_ledinit;
        }

        /*1、初始化定时器*/
        init_timer(&timer.timers);

        /*2、注册定时器*/
        timer.timers.expires =  jiffies + msecs_to_jiffies(500);   /*周期*/
        /*上面500ms到了之后就会运行下面的函数 相当于中断函数*/
        /*也就是当timer_func执行的时候它的参数对应的就是timer那个结构体 相当于arg*/
        timer.timers.function = timer_func;
        /*data 会传递给定时器的timer_func函数*/

        timer.timers.data = (unsigned long)&timer;

        add_timer(&timer.timers);



        return 0;

fail_ledinit:
fail_device:
        class_destroy(timer.class);
fail_class:
        cdev_del(&timer.cdev);
fail_cdevadd:
        unregister_chrdev_region(timer.devid,TIMER_CNT);  /*释放设备号*/
fail_devid:
        return ret;
}

/*驱动出口函数*/
static void __exit timer_exit(void)
{
        printk("liutao timer_exit\r\n");

        /*关灯*/
        gpio_set_value(timer.led_gpio,1);
        /*删除定时器*/
        del_timer(&timer.timers);

        /*注销字符设备驱动*/
        cdev_del(&timer.cdev);
        unregister_chrdev_region(timer.devid,TIMER_CNT);

        /*先创建的类，后创建设备。所以要先销毁设备，再销毁类*/
        device_destroy(timer.class,timer.devid);
        class_destroy(timer.class);

        /*申请后request一定要记得释放，不然会报错*/
        gpio_free(timer.led_gpio);
}


module_init(timer_init);
module_exit(timer_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("liutao");