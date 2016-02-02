/*
 * twi.h
 *
 * Created: 2016/01/24 17:38:20
 *  Author: HarukiNakai
 */ 

#ifndef TWI_H_
#define TWI_H_

#include "config.h"

#define I2C_ACK 1
#define I2C_NOACK 0

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>
#include <util/twi.h>

void I2C_Init(void);
void I2C_Start(void);
void I2C_Stop(void);
void I2C_Send(uint8_t data);
uint8_t I2C_Recv(int ack);
void I2C_Recv_Num(uint8_t i2caddr, uint8_t* data, uint8_t num);

#endif /* TWI_H_ */