#include"uart.h"
#include"gpio.h"
bool uart_init(uint32_t baudrate){
	uint32_t CR;
	//Set uart0 alternate funcitons for pins 30-33 to ALT3
	for(int pin = 30; pin < 34; pin++){
		//here the gpio_pull_* calls will slow down the CPU a bit. TODO: optimize this part of code
		gpio_pull_down(pin);
		gpio_set_function(pin, GPIO_FUNC_ALT3);

	}
	*(UART_BASE + UART_CR) &= ~(0xffff);
	//wait until the end of transmission
	while( *(UART_BASE + UART_FR) & (1 << 3));
	*(UART_BASE + UART_LCRH) &= ~(1 << 4); //flush the TX FIFO
	CR = *(UART_BASE);
	CR |= 0x300;
	*(UART_BASE) = CR;
	//set word length to 8 bits and enable FIFOs 
	*(UART_BASE + UART_LCRH) |= 0x70; 
	*(UART_BASE + UART_IBRD) = (FUARTCLK / (16 * baudrate) ) & 0xffff;
	int frac = (FUARTCLK % (16 * baudrate));
	*(UART_BASE + UART_FBRD) = frac & 0x3d;
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
size_t uart_write(const char* buf, size_t count){
	while(count-- > 0){
		uart_putc(*(buf++));
	}
}
