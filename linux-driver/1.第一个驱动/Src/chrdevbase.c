
#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/init.h>
#include <linux/fs.h>
#include <linux/kernel.h>
#include <linux/slab.h>
#include <linux/delay.h>
#include <linux/uaccess.h>
#include <linux/io.h>

#define CHARDEVBASE_MAJOR   200
#define CHRDEVBASE_NAME     "chrdevbase"

static char readbuf[100]; /*readbuf*/
static char writebuf[100];/*writebuf*/
static char kerneldata[] = {"kernel data"};


static int chrdevbase_open(struct inode *inode,struct file *file)
{
    printk("chrdevbase open\r\n");
    return 0;
}
static int chrdevbase_release(struct inode *inode,struct file *filp)
{
    printk("chrdevbase release\r\n");
    return 0;
}
static ssize_t chrdevbase_reade(struct file *filp,__user char *buf,size_t count,loff_t *ppos)
{
    int ret = 0;
    printk("chrdevbase read\r\n");
    memcpy(readbuf,kerneldata,sizeof(kerneldata));
    ret = copy_to_user(buf,readbuf,count);
    if (ret < 0) {
        printk("copy_to_user is error\r\n");
    }
    else {
        printk("copy_to_user is ok\r\n");
    }


    return 0;
}
static ssize_t chrdevbase_write(struct file *filp,const char __user *buf,size_t count,loff_t *ppos)
{

    int ret = 0;
    printk("chrdevbase write\r\n");

    ret = copy_from_user(writebuf,buf,count);
    if (ret < 0) {
        printk("write is error\r\n");
    }
    else {
        printk("kernel recevdata:%s\r\n",writebuf);
    }
    return 0;
}


static struct file_operations chrdevbase_fops={
    .owner = THIS_MODULE,
    .open = chrdevbase_open,
    .release = chrdevbase_release,
    .read = chrdevbase_reade,
    .write = chrdevbase_write,
};






static int __init chrdevbase_init(void)
{
    //device
    int ret = 0;
    ret = register_chrdev(CHARDEVBASE_MAJOR,CHRDEVBASE_NAME,&chrdevbase_fops);
    if(ret < 0)
    {
        printk("my name is liutao init failed\r\n");
    }
    printk("my name is liutao is ok\r\n");
    return 0;
}

static void __exit chrdevbase_exit(void)
{
    printk("exit liutao\r\n");
    unregister_chrdev(CHARDEVBASE_MAJOR,CHRDEVBASE_NAME);
    return;
}

module_init(chrdevbase_init);
module_exit(chrdevbase_exit);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("liutao");