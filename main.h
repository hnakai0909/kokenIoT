#ifndef MAIN_H_
#define MAIN_H_

#define TRUE 1
#define FALSE 0

#include "config.h"

#include <avr/io.h>
#include <avr/interrupt.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>
#include <stdio.h>

#include "twi.h"
#include "UART.h"
#include "BME280.h"
#include "SPLC792.h"
#include "myutil.h"

static inline void Init(void);

static inline void GPIO_Init(void);
static inline void UART_Init(void);
static inline void ADC_Init(void);
static inline void Timer_Init(void);
static inline void PWM_Init(void);

/*
(PCINT14/RESET)			PC6	01	28	PC5 (ADC5/SCL/PCINT13)
(PCINT16/RXD)			PD0	02	27	PC4 (ADC4/SDA/PCINT12)
(PCINT17/TXD)			PD1	03	26	PC3 (ADC3/PCINT11)
(PCINT18/INT0)			PD2	04	25	PC2 (ADC2/PCINT10)
(PCINT19/OC2B/INT1)		PD3	05	24	PC1 (ADC1/PCINT9)
(PCINT20/XCK/T0)		PD4	06	23	PC0 (ADC0/PCINT8)
VCC							07	22	GND
GND							08	21	AREF
(PCINT6/XTAL1/TOSC1)	PB6	09	20	AVCC
(PCINT7/XTAL2/TOSC2)	PB7	10	19	PB5 (SCK/PCINT5)
(PCINT21/OC0B/T1)		PD5	11	18	PB4 (MISO/PCINT4)
(PCINT22/OC0A/AIN0)		PD6	12	17	PB3 (MOSI/OC2A/PCINT3)
(PCINT23/AIN1)			PD7	13	16	PB2 (SS/OC1B/PCINT2)
(PCINT0/CLKO/ICP1)		PB0	14	15	PB1 (OC1A/PCINT1)
*/

#endif /* MAIN_H_ */