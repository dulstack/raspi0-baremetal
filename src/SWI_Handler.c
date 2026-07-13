#include<stdint.h>
#include"uart.h"
void __attribute__((interrupt ("SWI"))) SWI_Handler(){
	register uint32_t r0 asm ("r0"), r1 asm ("r1"), r2 asm ("r2"), r3 asm ("r3"), 
		 r4 asm ("r4"), r5 asm ("r5"), r6 asm ("r6"), r7 asm ("r7");
	__asm__("push {r0,r1,r3,r4,r5,r6,r7}");
	uint32_t svc_number;
	__asm__("ldr %0, [lr, $-4]" : "=r" (svc_number));
	svc_number &= 0xff;
	if(svc_number != 0){
		return;
	}
	__asm__("pop {r0,r1,r3,r4,r5,r6,r7}");
	switch(r7){
		case 4:
		 if(r0 == 1)
		  uart_write((const char*)r1, r2);

	}
}
