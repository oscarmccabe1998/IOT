
/*
 ============================================================================
 Name        : GPIO_Driver.h - the header file with four IO controls
 Author      : Oscar McCabe
 Version     : 0.1
 Copyright   : See Abertay copyright notice
 Description : RPi - GPIO Driver - Adapted from second independant learning task
 ============================================================================
 */
#ifndef GPIO_Driver_H
#define GPIO_Driver_H


typedef struct lkm_data {
	unsigned char data[256];
	unsigned long len;
	char type;
} lkm_data;

typedef struct gpio_pin {
	char desc[16];
	unsigned int pin;
	int value;
	char opt;
} gpio_pin;

#define IOCTL_READ 0x65
#define IOCTL_WRITE 0x66
#define GPIO_READ 0x67
#define GPIO_WRITE 0x68


#define  DEVICE_NAME "GPIO_Driver_dev"
#define  CLASS_NAME  "GPIO_Driver_cls"

#endif

