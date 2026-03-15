#ifndef __UART_H
#define __UART_H
#include "BCM2835.h"
#define UART_BASE (uint32_t*)0x20201000
#define FUARTCLK 250000000
#define UART_DR 0x00
#define UART_FR 0x18
#define UART_IBRD 0x24
#define UART_FBRD 0x28
#define UART_LCRH 0x2c
#define UART_CR 0x30
#define UART_MIS 0x40
#define UART_ICR 0x44
bool uart_init(uint16_t baud);
void uart_putc(char);
char uart_getc();
#endif
