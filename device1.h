#ifndef _DEVICE_H  /* Include guard */
#define _DEVICE_H

#include <linux/module.h>
#include <linux/version.h>
#include <linux/kernel.h>
#include <linux/types.h>
#include <linux/kdev_t.h>
#include <linux/fs.h>
#include <linux/device.h>
#include <linux/cdev.h>


extern int funcion_inicio(void);
extern void funcion_salida(void);

#endif