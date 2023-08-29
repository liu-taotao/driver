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
#include <linux/input.h>


#define KEYINPUT_CNT     1
#define KEYINPUT_NAME    "keyinput"

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

};


/*keyinput设备结构体*/
struct keyinput_dev {
        struct device_node *nd;

        struct irq_keydesc irqkey[KEY_NUM];

        struct timer_list timer;        /*定时器*/

        /*输入设备*/
        struct input_dev *inputdev;


};

struct keyinput_dev keyinput; /*irq 设备*/


/*中断处理函数*/
static irqreturn_t key0_handler(int irq,void *dev_id)
{

        struct keyinput_dev *dev = dev_id;

        /*dev_id就是keyinput*/
        dev->timer.data = (volatile unsigned long)dev_id; /*强制类型转换，因为data是括号里面的类型*/
        /*消抖*/
        mod_timer(&dev->timer,jiffies + msecs_to_jiffies(20));         /*10s定时*/

        return IRQ_HANDLED;
}

/*定时器处理函数 进行一个消抖*/
static void timer_func(unsigned long arg)
{
        int value = 0;
        struct keyinput_dev *dev = (struct keyinput_dev *)arg;
        value = gpio_get_value(dev->irqkey[0].gpio);

        if (value == 0) {       /*按下*/
                /*上报按键值*/
                input_event(dev->inputdev,EV_KEY,KEY_0,1);/*按下*/
                /*每上报一个数据都要同步一下*/
                input_sync(dev->inputdev);

        } else if (value == 1) {        /*释放*/
                /*上报按键值*/
                input_event(dev->inputdev,EV_KEY,KEY_0,0);/*释放*/
                input_sync(dev->inputdev);
        }

}

/*按键初始化*/
static int keyio_init(struct keyinput_dev *dev)
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
                dev->irqkey[i].gpio = of_get_named_gpio(keyinput.nd,"key-gpios",i);
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

        }


        dev->irqkey[0].handler = key0_handler;
        dev->irqkey[0].value = KEY_0;
        /*4、按键中断初始化*/
        for (i = 0; i < KEY_NUM; i++) {
                /*第三个参数是触发方式*/
                ret = request_irq(dev->irqkey[i].irqnum,key0_handler,
                                        IRQF_TRIGGER_RISING|IRQF_TRIGGER_FALLING,
                                        dev->irqkey[i].name,&keyinput);
                if (ret) {
                        printk("irq %d request failed\r\n",dev->irqkey[i].irqnum);
                        goto fail_irq;
                }
       }


        /*5、初始化定时器*/
        init_timer(&keyinput.timer);
        /*6、注册定时器*/

        /*也就是当timer_func执行的时候它的参数对应的就是timer那个结构体 相当于arg*/
        keyinput.timer.function = timer_func;
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
static int __init keyinput_init(void)
{

        int ret = 0;

        /*1、初始化io*/
        ret = keyio_init(&keyinput);
        if (ret < 0) {
                goto fail_keyinit;
        }

        /*2、注册input_dev*/
        keyinput.inputdev = input_allocate_device();
        if (keyinput.inputdev == NULL) {
                ret = -EINVAL;
                goto fail_keyinit;
        }
        /*3、初始化*/
        keyinput.inputdev->name = KEYINPUT_NAME;
        /*捕获事件有三种方法*/
        /*1*/
        __set_bit(EV_KEY,keyinput.inputdev->evbit);/*设置产生按键事件*/
        __set_bit(EV_REP,keyinput.inputdev->evbit);/*重复事件*/
        __set_bit(KEY_0,keyinput.inputdev->keybit);/*按键值*/

        /*注册*/
        ret = input_register_device(keyinput.inputdev);
        if (ret) {
                
                goto fail_input_register;
        }



        return 0;
fail_input_register:
                input_free_device(keyinput.inputdev);/*释放*/
fail_keyinit:

        return ret;
}

/*驱动出口函数*/
static void __exit keyinput_exit(void)
{
        int i = 0;
        printk("liutao keyinput_exit\r\n");

        /*1、释放中断*/
        for (i = 0; i < KEY_NUM; i++) {
                free_irq(keyinput.irqkey[i].irqnum,&keyinput);
        }

        /*2、释放io 申请后request一定要记得释放，不然会报错*/
        for (i = 0; i < KEY_NUM; i++) {
                gpio_free(keyinput.irqkey[i].gpio);
        }

        /*3、删除定时器*/
        del_timer(&keyinput.timer);
        
        /*4、注销input_dev*/
        input_unregister_device(keyinput.inputdev);
        input_free_device(keyinput.inputdev);


}


module_init(keyinput_init);
module_exit(keyinput_exit);
MODULE_LICENSE("GPL");
MODULE_AUTHOR("liutao");