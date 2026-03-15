#include"uart.h"
void main(){
	const char* msg="Hello, world!";
	uart_init(115200);
	while(*msg){
		uart_putc(*(msg++));
	}
	return;
}
