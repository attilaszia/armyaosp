/*
* Linker script for the ARM kernel
*
*/


SECTIONS {
	
	.init 0x8000 : {
		*(.init)
	}
	
	.text : {
		*(.text)
	}
	
	.data : {
		*(.data)
	}
        
        .rodata : {
                *(.rodata)
        }

    . = ALIGN(64);

    _bss = . ;
    .bss : {
               *(.bss)
    }

    . = ALIGN(64);
    _end = .;

	/*
	* Discard other stuff. This might be risky, we should permit
        * a few specific sections only, but it will do for now.
	*/
	/DISCARD/ : {
		*(*)
	}
}
