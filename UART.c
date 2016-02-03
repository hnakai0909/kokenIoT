/*
 * UART.c
 *
 * Created: 2016/02/04 2:37:36
 *  Author: HarukiNakai
 */ 

#include "UART.h"

void UART_puts(char* str){
	while(*str){
		UDR0 = *str++;
		_delay_ms(2);
	}
}