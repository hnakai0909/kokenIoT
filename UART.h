/*
 * UART.h
 *
 * Created: 2016/02/04 2:37:47
 *  Author: HarukiNakai
 */ 

#ifndef UART_H_
#define UART_H_

#define UART_TXBUF_SIZE 128

#include "config.h"

#define I2C_ACK 1
#define I2C_NOACK 0

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include <avr/wdt.h>
#include <util/delay.h>
#include "myutil.h"

extern unsigned char pyro1,pyro2,door,existence;
extern uint8_t adc_val;

extern uint8_t data_raw[8];
extern uint8_t data_dig[32];

extern char UART_TXbuf[UART_TXBUF_SIZE];
extern uint8_t UART_TXbuf_head;
extern uint8_t UART_TXbuf_tail;

void UART_putchar(uint8_t c);
void UART_puts(char* str);

#endif /* UART_H_ */