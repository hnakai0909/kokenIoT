/*
 * UART.h
 *
 * Created: 2016/02/04 2:37:47
 *  Author: HarukiNakai
 */ 

#ifndef UART_H_
#define UART_H_

#include "config.h"

#define I2C_ACK 1
#define I2C_NOACK 0

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>

void UART_puts(char* str);

#endif /* UART_H_ */