#ifndef __BCM2835_H
#define __BCM2835_H
#define MMIO_BASE 0x20000000
#define __NOP(count)\
	while(count-- > 0) __asm__("nop");
#include <stdint.h>
#include <stdbool.h>
#endif
