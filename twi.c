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

void I2C_Recv_Num(uint8_t i2caddr, uint8_t* data, uint8_t num){
	unsigned char i;
	uint8_t tmp;
	I2C_Start();
	I2C_Send((i2caddr << 1) | 1); //Read
	if(num>1){
		for(i = 0 ; i < num-1 ; i++){
			data[i] = I2C_Recv(I2C_ACK);
		}
		tmp = I2C_Recv(I2C_NOACK);
	}else{
		data[0] = I2C_Recv(I2C_NOACK);
	}
	I2C_Stop();
	TWCR = _BV(TWINT);
}