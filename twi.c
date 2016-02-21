/*
 * twi.c
 *
 * Created: 2016/01/24 17:38:36
 *  Author: HarukiNakai
 */ 

#include "twi.h"

void I2C_Init(void){
	// 400kHz @ 8MHz
	TWSR = 0; //no prescale
	TWBR = 2;
	TWCR = _BV(TWEN);
}

void I2C_Start(void){
	TWCR = _BV(TWINT);
	_delay_us(27);
	TWCR = _BV(TWINT) | _BV(TWSTA) | _BV(TWEN);
	loop_until_bit_is_set(TWCR, TWINT);
}

void I2C_Stop(void){
	TWCR = _BV(TWINT) | _BV(TWSTO) | _BV(TWEN);
}

void I2C_Send(uint8_t data){
	TWDR = data;
	TWCR = _BV(TWINT) | _BV(TWEN);
	loop_until_bit_is_set(TWCR, TWINT);
	//_delay_us(27);
}

uint8_t I2C_Recv(int ack){
	if(ack==I2C_ACK){
		//ACK
		TWCR = _BV(TWINT) | _BV(TWEN) | _BV(TWEA);
	}else{
		//NOACK(NACK)
		TWCR = _BV(TWINT) | _BV(TWEN);
	}
	loop_until_bit_is_set(TWCR, TWINT);
	return TWDR;
}

void I2C_Recv_Num(uint8_t i2caddr, uint8_t* data, uint8_t num, uint8_t offset){
	uint8_t i;
	I2C_Start();
	I2C_Send((i2caddr << 1) | 1); //Read
	for(i = 0 ; i < num ; i++){
		data[offset + i] = I2C_Recv(I2C_ACK);
		_delay_us(27);
	}
	I2C_Recv(I2C_NOACK);
	I2C_Stop();
	TWCR = _BV(TWINT);
}