#include <stdint.h>
#include "reg.h"
#include "asm.h"

/* USART TXE Flag
 * This flag is cleared when data is written to USARTx_DR and
 * set when that data is transferred to the TDR
 */
#define USART_FLAG_TXE	((uint16_t) 0x0080)

void usart_init(void)
{
	*(RCC_APB2ENR) |= (uint32_t) (0x00000001 | 0x00000004);
	*(RCC_APB1ENR) |= (uint32_t) (0x00020000);

	/* USART2 Configuration, Rx->PA3, Tx->PA2 */
	*(GPIOA_CRL) = 0x00004B00;
	*(GPIOA_CRH) = 0x44444444;
	*(GPIOA_ODR) = 0x00000000;
	*(GPIOA_BSRR) = 0x00000000;
	*(GPIOA_BRR) = 0x00000000;

	*(USART2_CR1) = 0x0000000C;
	*(USART2_CR2) = 0x00000000;
	*(USART2_CR3) = 0x00000000;
	*(USART2_CR1) |= 0x2000;
}

void print_str(const char *str)
{
	while (*str) {
		while (!(*(USART2_SR) & USART_FLAG_TXE));
		*(USART2_DR) = (*str & 0xFF);
		str++;
	}
}

void usertask(void)
{
	print_str("usertask: 1st call of usertask!\n");
	print_str("usertask: Now, return to kernel mode\n");
	syscall(); //系統呼叫  在使用者行程中 再進行呼叫 EX 輸出入切換
	print_str("usertask: 2nd call of usertask!\n");
	print_str("usertask: Now, return to kernel mode\n");
	syscall();
	while (1)
		/* wait */ ;
}

int main(void)
{
	/* Initialization of process stack
	 * r4, r5, r6, r7, r8, r9, r10, r11, lr */
	unsigned int usertask_stack[256];
	unsigned int *usertask_stack_start = usertask_stack + 256 - 16;
	usertask_stack_start[8] = (unsigned int) &usertask;

	usart_init();

	print_str("OS: Starting...\n");
	print_str("OS: Calling the usertask (1st time)\n");
	usertask_stack_start = activate(usertask_stack_start);
	print_str("OS: Return to the OS mode !\n");
	print_str("OS: Calling the usertask (2nd time)\n");
	usertask_stack_start = activate(usertask_stack_start);
	print_str("OS: Return to the OS mode !\n");
	print_str("OS: Going to infinite loop...\n");
	while (1)
		/* We can't exit, there is nowhere to go */ ;
	return 0;
}
