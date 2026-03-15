#ifndef __GPIO_H
#define __GPIO_H
#include "BCM2835.h"
#define GPIO_BASE (MMIO_BASE + 0x20000)
struct gpio{
	uint32_t FSEL[6]; // 0x00
	uint32_t __reserved0;	// 0x18
	uint32_t SET[2];	//0x1c
	uint32_t __reserved1;	//0x24
	uint32_t CLR[2];	//0x28
	uint32_t __reserved2;	//0x30
	uint32_t LEV[2];	//0x34
	uint32_t __reserved3;	//0x3c
	uint32_t EDS[2];	//0x40
	uint32_t __reserved4;	//0x48
	uint32_t REN[2];	//0x4c
	uint32_t __reserved5;	//0x54
	uint32_t FEN[2];	//0x58
	uint32_t __reserved6;	//0x60
	uint32_t HEN[2];	//0x64
	uint32_t __reserved7;	//0x6c
	uint32_t LEN[2];	//0x70
	uint32_t __reserved8;	//0x78
	uint32_t AREN[2];	//0x7c
	uint32_t __reserved9;	//0x84
	uint32_t AFEN[2];	//0x88
	uint32_t __reserved10;	//0x90
	uint32_t PUD;		//pull-up/down
	uint32_t PUDCLK[2];
};
struct gpio* gpio = (struct gpio*) GPIO_BASE;
enum GPIO_FUNC{
	GPIO_FUNC_IN = 0,
	GPIO_FUNC_OUT,
	GPIO_FUNC_ALT5,
	GPIO_FUNC_ALT4,
	GPIO_FUNC_ALT0,
	GPIO_FUNC_ALT1,
	GPIO_FUNC_ALT2,	
	GPIO_FUNC_ALT3
};
static inline void gpio_set_function(uint8_t pin, uint8_t func){
	//if(pin > 53 || func > 7)return;
	const uint32_t fsel_index = (pin / 10);
	const uint32_t fsel_offset_bit = ( (pin % 10) * 3 );
	const uint32_t fsel_mask = 7 << fsel_offset_bit; 
	//clear the selected function
	gpio->FSEL[fsel_index] &= ~(fsel_mask);
	//set the function
	gpio->FSEL[fsel_index] |= func << fsel_offset_bit;
}
static inline void gpio_put(uint8_t pin, bool val){
	const uint32_t idx = (pin / 32);
	//if(pin > 53 || val > 1)return
	const uint32_t pin_bit = 1 << (pin % 32);
	switch(val){
		case 0:
			gpio->CLR[idx] |= pin_bit;
		case 1:
			gpio->SET[idx] |= pin_bit;
	}
}
static bool gpio_get(uint8_t pin){
	return ( (gpio->LEV[pin / 32] >> (pin % 32) ) & 1);
}
static void gpio_pull_up(uint8_t pin){
	//if(pin > 53 || val > 1)return
	uint32_t tmp = gpio->PUD;
	tmp = tmp & 0xffffff00;
	tmp |= 0x02;
	gpio->PUD = tmp;
	__NOP(150);
	gpio->PUDCLK[pin / 32] = (1 << (pin % 32));
	__NOP(150);
	tmp = tmp & (~1);	//disable the pull-up/down control
	gpio->PUD = tmp;
	gpio->PUDCLK[pin / 32] = (1 << (pin % 32));
}
static void gpio_pull_down(uint8_t pin){
	//if(pin > 53 || val > 1)return
	uint32_t tmp = gpio->PUD;
	tmp = tmp & 0xffffff00;
	tmp |= 0x01;
	gpio->PUD = tmp;
	__NOP(150);
	gpio->PUDCLK[pin / 32] = (1 << (pin % 32));
	__NOP(150);
	tmp = tmp & (~1);
	gpio->PUD = tmp;
	gpio->PUDCLK[pin / 32] = (1 << (pin % 32));
}
#endif
