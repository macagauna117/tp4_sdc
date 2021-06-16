#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>


//Variables usadas la configuracion de Char Dev Driver
dev_t first = 0;
static struct cdev c_dev; 	        // Global variable for the character device structure
static struct class *class_dev; 	// Global variable for the device class


static int my_open(struct inode *i, struct file *f)
{
    printk(KERN_INFO "alarma: open()\n");
    return 0;
}
static int my_close(struct inode *i, struct file *f)
{
    printk(KERN_INFO "alarma: close()\n");
    return 0;
}
static ssize_t my_read(struct file *f, char __user *buf, size_t len, loff_t *off)
{
    printk(KERN_INFO "alarma: read()\n");
    return 0;
}
static ssize_t my_write(struct file *f, const char __user *buf, size_t len, loff_t *off)
{
    printk(KERN_INFO "alarma: write()\n");
    return len;
}

static struct file_operations fops =
{
    // Dentro de file_operations defino las funciones que voy a implementar..!!
    .owner = THIS_MODULE,
    .open = my_open,
    .release = my_close,
    .read = my_read,
    .write = my_write
};

int funcion_inicio(void){

        /*Alocando el numero mayor*/
    if ((alloc_chrdev_region(&first, 0, 1, "alarma")) < 0)
    {
        pr_err("Cannot allocate major number\n");
        return -1;
    }
    pr_info("Major = %d Minor = %d \n", MAJOR(first), MINOR(first));

    /*Creando estructura cdev*/
    cdev_init(&c_dev, &fops);

    /*Agregando el CDD al sistema*/
    if ((cdev_add(&c_dev, first, 1)) < 0)
    {
        pr_err("Cannot add the device to the system\n");
        goto r_class;
    }

    /*Creando estrucutra de clase*/
    if ((class_dev = class_create(THIS_MODULE, "class_alarma")) == NULL)
    {
        pr_err("Cannot create the struct class\n");
        goto r_class;
    }

    /*Creando dispositivo*/
    if ((device_create(class_dev, NULL, first, NULL, "alarma")) == NULL)
    {
        pr_err("Cannot create the Device 1\n");
        goto r_device;
    }

    r_device:
        class_destroy(class_dev);
    r_class:
        unregister_chrdev_region(first, 1);
    
    return 0;
}

void funcion_salida(void){
     //Se elimina la configuracion de /dev
    device_destroy(class_dev, first);
    class_destroy(class_dev);
    cdev_del(&c_dev);
    unregister_chrdev_region(first, 1);
    printk("Eliminando device driver de alarma.\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("Maca y Fede");
MODULE_DESCRIPTION("Modulo de Kernel para parpadear un LED y otras cositas");
