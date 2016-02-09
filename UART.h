/*
 * UART.h
 *
 * Created: 2016/02/04 2:37:47
 *  Author: HarukiNakai
 */ 

#ifndef UART_H_
#define UART_H_

#define UART_TXBUF_SIZE 64

#include "config.h"

#define I2C_ACK 1
#define I2C_NOACK 0

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>

extern unsigned char pyro1,pyro2,door,existence;

extern uint16_t dig_T1;
extern int16_t dig_T2;
extern int16_t dig_T3;
extern uint16_t dig_P1;
extern int16_t dig_P2;
extern int16_t dig_P3;
extern int16_t dig_P4;
extern int16_t dig_P5;
extern int16_t dig_P6;
extern int16_t dig_P7;
extern int16_t dig_P8;
extern int16_t dig_P9;
extern int8_t  dig_H1;
extern int16_t dig_H2;
extern int8_t  dig_H3;
extern int16_t dig_H4;
extern int16_t dig_H5;
extern int8_t  dig_H6;

extern char UART_TXbuf[UART_TXBUF_SIZE];
extern uint8_t UART_TXbuf_head;
extern uint8_t UART_TXbuf_tail;

void UART_putchar(uint8_t c);
void UART_puts(char* str);

#endif /* UART_H_ */