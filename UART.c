/*
 * UART.c
 *
 * Created: 2016/02/04 2:37:36
 *  Author: HarukiNakai
 */ 

#include "UART.h"

ISR(USART_RX_vect){
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
		case 'p':
			UART_putchar(itoa_01x((pres_raw>>16)&0x0F));
			UART_putchar(itoa_01x((pres_raw>>12)&0x0F));
			UART_putchar(itoa_01x((pres_raw>> 8)&0x0F));
			UART_putchar(itoa_01x((pres_raw>> 4)&0x0F));
			UART_putchar(itoa_01x((pres_raw    )&0x0F));
			break;
		case 't':
			UART_putchar(itoa_01x((temp_raw>>16)&0x0F));
			UART_putchar(itoa_01x((temp_raw>>12)&0x0F));
			UART_putchar(itoa_01x((temp_raw>> 8)&0x0F));
			UART_putchar(itoa_01x((temp_raw>> 4)&0x0F));
			UART_putchar(itoa_01x((temp_raw    )&0x0F));
			break;
		case 'h':
			UART_putchar(itoa_01x((hum_raw>>12)&0x0F));
			UART_putchar(itoa_01x((hum_raw>> 8)&0x0F));
			UART_putchar(itoa_01x((hum_raw>> 4)&0x0F));
			UART_putchar(itoa_01x((hum_raw    )&0x0F));
			break;
		//DIG
		case 'P':
			UART_putchar(itoa_01x((dig_P1>>12)&0x0F));
			UART_putchar(itoa_01x((dig_P1>> 8)&0x0F));
			UART_putchar(itoa_01x((dig_P1>> 4)&0x0F));
			UART_putchar(itoa_01x((dig_P1    )&0x0F));
			UART_putchar(itoa_01x((dig_P2>>12)&0x0F));
			UART_putchar(itoa_01x((dig_P2>> 8)&0x0F));
			UART_putchar(itoa_01x((dig_P2>> 4)&0x0F));
			UART_putchar(itoa_01x((dig_P2    )&0x0F));
			UART_putchar(itoa_01x((dig_P3>>12)&0x0F));
			UART_putchar(itoa_01x((dig_P3>> 8)&0x0F));
			UART_putchar(itoa_01x((dig_P3>> 4)&0x0F));
			UART_putchar(itoa_01x((dig_P3    )&0x0F));
			UART_putchar(itoa_01x((dig_P4>>12)&0x0F));
			UART_putchar(itoa_01x((dig_P4>> 8)&0x0F));
			UART_putchar(itoa_01x((dig_P4>> 4)&0x0F));
			UART_putchar(itoa_01x((dig_P4    )&0x0F));
			UART_putchar(itoa_01x((dig_P5>>12)&0x0F));
			UART_putchar(itoa_01x((dig_P5>> 8)&0x0F));
			UART_putchar(itoa_01x((dig_P5>> 4)&0x0F));
			UART_putchar(itoa_01x((dig_P5    )&0x0F));
			UART_putchar(itoa_01x((dig_P6>>12)&0x0F));
			UART_putchar(itoa_01x((dig_P6>> 8)&0x0F));
			UART_putchar(itoa_01x((dig_P6>> 4)&0x0F));
			UART_putchar(itoa_01x((dig_P6    )&0x0F));
			UART_putchar(itoa_01x((dig_P7>>12)&0x0F));
			UART_putchar(itoa_01x((dig_P7>> 8)&0x0F));
			UART_putchar(itoa_01x((dig_P7>> 4)&0x0F));
			UART_putchar(itoa_01x((dig_P7    )&0x0F));
			UART_putchar(itoa_01x((dig_P8>>12)&0x0F));
			UART_putchar(itoa_01x((dig_P8>> 8)&0x0F));
			UART_putchar(itoa_01x((dig_P8>> 4)&0x0F));
			UART_putchar(itoa_01x((dig_P8    )&0x0F));
			UART_putchar(itoa_01x((dig_P9>>12)&0x0F));
			UART_putchar(itoa_01x((dig_P9>> 8)&0x0F));
			UART_putchar(itoa_01x((dig_P9>> 4)&0x0F));
			UART_putchar(itoa_01x((dig_P9    )&0x0F));
			break;
		case 'T':
			UART_putchar(itoa_01x((dig_T1>>12)&0x0F));
			UART_putchar(itoa_01x((dig_T1>> 8)&0x0F));
			UART_putchar(itoa_01x((dig_T1>> 4)&0x0F));
			UART_putchar(itoa_01x((dig_T1    )&0x0F));
			UART_putchar(itoa_01x((dig_T2>>12)&0x0F));
			UART_putchar(itoa_01x((dig_T2>> 8)&0x0F));
			UART_putchar(itoa_01x((dig_T2>> 4)&0x0F));
			UART_putchar(itoa_01x((dig_T2    )&0x0F));
			UART_putchar(itoa_01x((dig_T3>>12)&0x0F));
			UART_putchar(itoa_01x((dig_T3>> 8)&0x0F));
			UART_putchar(itoa_01x((dig_T3>> 4)&0x0F));
			UART_putchar(itoa_01x((dig_T3    )&0x0F));
			break;
		case 'H':
			UART_putchar(itoa_01x((dig_H1>> 4)&0x0F));
			UART_putchar(itoa_01x((dig_H1    )&0x0F));
			UART_putchar(itoa_01x((dig_H2>>12)&0x0F));
			UART_putchar(itoa_01x((dig_H2>> 8)&0x0F));
			UART_putchar(itoa_01x((dig_H2>> 4)&0x0F));
			UART_putchar(itoa_01x((dig_H2    )&0x0F));
			UART_putchar(itoa_01x((dig_H3>> 4)&0x0F));
			UART_putchar(itoa_01x((dig_H3    )&0x0F));
			UART_putchar(itoa_01x((dig_H4>>12)&0x0F));
			UART_putchar(itoa_01x((dig_H4>> 8)&0x0F));
			UART_putchar(itoa_01x((dig_H4>> 4)&0x0F));
			UART_putchar(itoa_01x((dig_H4    )&0x0F));
			UART_putchar(itoa_01x((dig_H5>>12)&0x0F));
			UART_putchar(itoa_01x((dig_H5>> 8)&0x0F));
			UART_putchar(itoa_01x((dig_H5>> 4)&0x0F));
			UART_putchar(itoa_01x((dig_H5    )&0x0F));
			UART_putchar(itoa_01x((dig_H6>> 4)&0x0F));
			UART_putchar(itoa_01x((dig_H6    )&0x0F));
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