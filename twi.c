/*
 * twi.c
 *
 * Created: 2016/01/24 17:38:36
 *  Author: HarukiNakai
 */ 

#include "twi.h"

void I2C_Init(void){
	// 400kHz @ 8MHz
	TWSR = 0;
	TWBR = 2;
}

void I2C_Start(void){
	TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
	loop_until_bit_is_set(TWCR, TWINT);
}

void I2C_Stop(void){
	TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
	loop_until_bit_is_set(TWCR, TWSTO);
}

void I2C_Send(uint8_t data){
	/*
	if(TW_STATUS != TW_START)return 1;
	*/
	TWDR = data;
	TWCR = _BV(TWINT) | _BV(TWEN);
	loop_until_bit_is_set(TWCR, TWINT);
}

uint8_t I2C_Recv(int ack){
	/*
	if (TW_STATUS != TW_MT_DATA_ACK)ERROR();
	*/
	TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
	loop_until_bit_is_set(TWCR, TWSTO);
	return TWDR;
}