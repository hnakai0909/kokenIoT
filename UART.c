/*
 * UART.c
 *
 * Created: 2016/02/04 2:37:36
 *  Author: HarukiNakai
 */ 

#include "UART.h"

ISR(USART_RX_vect){
	char udr;
	udr = UDR0;
	switch(udr){
		case '?':
		
		break;
		case 'B':
		break;
		default:
		break;
	}
}

ISR(USART_UDRE_vect){
	if (UART_TXbuf_head == UART_TXbuf_tail) {
		// Buffer empty, so disable interrupts
		UCSR0B &= ~_BV(UDRIE0);
		} else {
		// There is more data in the output buffer. Send the next byte
		unsigned char c = UART_TXbuf[UART_TXbuf_tail];
		UART_TXbuf_tail = (UART_TXbuf_tail + 1) % UART_TXBUF_SIZE;
		UDR0 = c;
	}
}

void UART_putchar(uint8_t c){
	int i = (UART_TXbuf_head + 1) % UART_TXBUF_SIZE;
	
	// If the output buffer is full, there's nothing for it other than to
	// wait for the interrupt handler to empty it a bit
	// ???: return 0 here instead?
	while (i == UART_TXbuf_tail);
	
	UART_TXbuf[UART_TXbuf_head] = c;
	UART_TXbuf_head = i;
	
	UCSR0B |= _BV(UDRIE0);
	//sbi(*_ucsra, TXC0);
}

void UART_puts(char* str){
	while(*str){
		UART_putchar(*str++);
	}
}