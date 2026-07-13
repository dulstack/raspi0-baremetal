.org 0x00
.globl main
.globl _Reset
.globl SWI_Handler
.section .vectors
_VECTOR_TABLE:
	b _Reset
	b . //Undefined
	b SWI_Handler
	b halt
	b . //Data abort
	b . //IRQ
	b . //FIQ
.section .text
_Reset:
	ldr sp, =_stack_start
	ldr r3, =_bss_start
	ldr r4, =_bss_end
	mov r5, #0
zero_bss:
	cmp r3, r4
	bge _start
	str r5, [r3]
	add r3, #4
	b zero_bss
_start:
	bl main
halt:
	nop
	b halt	
