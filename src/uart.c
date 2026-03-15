#include"uart.h"
bool uart_init(uint16_t baudrate){
	uint32_t CR;
	for(int pin = 14; pin <= 39; pin++){
		//don't forget to jump over the pins 18-29, 34, 35
		if((pin > 17 && pin < 30) ||
		   (pin > 33 && pin < 36) 
		) continue;
		//here the gpio_pull_* calls will slow down the CPU a bit. TODO: optimize this part of code
		(void) pin==36 ? gpio_pull_up(pin) : gpio_pull_down(pin);
		if(pin < 16)gpio_set_function(pin, GPIO_FUNC_ALT0);
		else gpio_set_function(pin, pin < 36 ? GPIO_FUNC_ALT3 : GPIO_FUNC_ALT2);

	}
	*(UART_BASE + UART_CR) &= ~(0xffff);
	//wait until the end of transmission
	while( *(UART_BASE + UART_FR) & (1 << 3));
	*(UART_BASE + UART_LCRH) &= ~(1<<4); //flush the TX FIFO
	CR = *(UART_BASE);
	CR |= 0b11 0000 0000;
	*(UART_BASE) = CR;
	//set word length to 8 bits and enable FIFOs 
	*(UART_BASE + UART_LCRH) |= 0x70; 
	*(UART_BASE + UART_IBRD) = (FUARTCLK / (16 * baudrate) ) & 0xffff;
	float frac = ((float)FUARTCLK / (16 * baudrate)); 
	frac -= (uint32_t) frac;
	while(frac != (uint32_t) frac)frac *= 10;
	*(UART_BASE + UART_FBRD) = ((uint32_t)frac) & 0x3f;
	*(UART_BASE + UART_CR) |= 1;
}
void uart_putc(char c){
	//wait for TX FIFO to free
	while( *(UART_BASE + UART_FR) & 1<<5 );
	*(UART_BASE + UART_DR) = (c & 0xff);
}
char uart_getc(){
	//wait for RX FIFO to free
	while( *(UART_BASE + UART_FR) & 1<<5 );
	return *(UART_BASE + UART_DR);
}
