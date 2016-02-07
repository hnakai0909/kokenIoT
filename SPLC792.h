/*
 * SPLC792.h (I2C LCD module)
 *
 * Created: 2016/01/29 3:36:45
 *  Author: HarukiNakai
 */ 


#ifndef SPLC792_H_
#define SPLC792_H_

#include "config.h"

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>
#include <util/twi.h>
#include "twi.h"

void SPLC792_Init(void);

void SPLC792_Data(uint8_t data);
void SPLC792_Cmd(uint8_t cmd);
void SPLC792_Move(uint8_t pos);

void SPLC792_puts(const char *s);
void SPLC792_puts_8(char c0,char c1,char c2,char c3,char c4,char c5,char c6,char c7);


#endif /* SPLC792_H_ */