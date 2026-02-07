ENTRY(_Reset);
MEMORY {
	RAM (rwx) : ORIGIN = 0x00000000, LENGTH = 512M
}
_stack_start = ORIGIN(RAM) + LENGTH(RAM);
SECTIONS {
	.vectors : {
		*(.vectors)
	} > RAM
	.text : {
		. = ALIGN(4);
		*(.text)
		. = ALIGN(4);
		*(.text.*)
		. = ALIGN(4);
	} > RAM
	.rodata : {
		. = ALIGN(4);
		*(.rodata)
		. = ALIGN(4);
		*(.rodata.*)
	} > RAM
	.data : {
		*(.data)
		. = ALIGN(4);
		*(.data.*)
		. = ALIGN(4);
	} > RAM
	.bss : {
		_bss_start = .;
		*(.bss)
		. = ALIGN(4);
		*(.bss.*)
		_bss_end = .;
	} > RAM
}
