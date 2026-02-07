#ifndef __GPIO_H
#define __GPIO_H
#include "BCM2835.h"
#define GPIO_BASE (MMIO_BASE + 0x20000)
struct gpio{
	uint32_t FSEL[6];
	uint32_t __reserved0;
	uint32_t SET[2];
	uint32_t __reserved1;
	uint32_t CLR[2];
	uint32_t __reserved2;
	uint32_t LEV[2];
	uint32_t __reserved3;
	uint32_t EDS[2];
	uint32_t __reserved4;
	uint32_t REN[2];
	uint32_t __reserved5;
	uint32_t FEN[2];
	uint32_t __reserved6;
	uint32_t HEN[2];
	uint32_t __reserved7;
	uint32_t LEN[2];
	uint32_t __reserved8;
	uint32_t AREN[2];
	uint32_t __reserved9;
	uint32_t AFEN[2];
	uint32_t __reserved10;
	uint32_t PUD;
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
	//if(pin > 53 || val > 1)return
	const uint32_t idx = (pin / 32);
	const uint32_t pin_bit = 1 << (pin % 32);
	switch(val){
		case 0:
			gpio->CLR[idx] |= pin_bit;
		case 1;
			gpio->SET[idx] |= pin_bit;
	}
}
static bool gpio_get(uint8_t pin){
	return ( (gpio->LEV[pin / 32] >> (pin % 32) ) & 1);
}
#endif
