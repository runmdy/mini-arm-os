#include <stdint.h>
#include "reg.h"

#define USART_FLAG_TXE	((uint16_t) 0x0080)

int puts(const char *str)
{  //操作輸出
	while (*str) {
		while (!(*(USART2_SR) & USART_FLAG_TXE));  //   後面條件檢查可否寫入
		*(USART2_DR) = *str++ & 0xFF;
	}
	return 0;
}

void main(void)
{   //初始化參數設定
	*(RCC_APB2ENR) |= (uint32_t) (0x00000001 | 0x00000004);
	*(RCC_APB1ENR) |= (uint32_t) (0x00020000);

	/* USART2 Configuration */
	*(GPIOA_CRL) = 0x00004B00;
	*(GPIOA_CRH) = 0x44444444;

	*(USART2_CR1) = 0x0000000C;
	*(USART2_CR1) |= 0x2000;

	puts("Hello World!\n"); //透過USART將hello送至宿主機

	while (1);  //防止運行其他程式
}
