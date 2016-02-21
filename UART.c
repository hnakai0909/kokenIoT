/*
 * UART.c
 *
 * Created: 2016/02/04 2:37:36
 *  Author: HarukiNakai
 */ 

#include "UART.h"

ISR(USART_RX_vect){
	uint8_t i = 0;
	char udr,str[5];
	udr = UDR0;
	switch(udr){
		case '?':
			//pyro1,pyro2,door,button,existence(,a)
			UART_putchar('0'+pyro1);UART_putchar(',');
			UART_putchar('0'+pyro2);UART_putchar(',');
			UART_putchar('0'+door);UART_putchar(',');
			UART_putchar('0'+existence);UART_putchar(',');
			UART_puts(itoa_03d(str,adc_val));UART_putchar(13);UART_putchar(10);
			break;
		//raw
		case 'r':
			for(i=0;i<8;i++){
				UART_putchar(itoa_01x((data_raw[i]>> 4)&0x0F));
				UART_putchar(itoa_01x((data_raw[i]    )&0x0F));
			}
			break;
		//dig
		case 'd':
			for(i=0;i<32;i++){
				UART_putchar(itoa_01x((data_dig[i]>> 4)&0x0F));
				UART_putchar(itoa_01x((data_dig[i]    )&0x0F));
			}
			break;
		// FORCE RESET
		case 'Q':
			cli();
			wdt_enable(WDTO_15MS);
			while(1){
				_delay_ms(20);
			}
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