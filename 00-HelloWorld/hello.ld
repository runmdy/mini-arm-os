ENTRY(reset_handler) //硬體對應 真正的位置區

MEMORY
{
	FLASH (rx) : ORIGIN = 0x00000000, LENGTH = 128K 
}

SECTIONS
{
	.text :
	{
		KEEP(*(.isr_vector))
		*(.text)   /*程式段位置*/
	} >FLASH   //這段要寫入上面的flash裡面
}
