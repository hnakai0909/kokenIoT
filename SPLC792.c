/*
 * SPLC792.c
 *
 * Created: 2016/01/29 3:36:27
 *  Author: HarukiNakai
 */ 

#include "SPLC792.h"


void SPLC792_Init(void){
	//reset low
	_delay_ms(1);
	//reset high
	_delay_ms(50);
	SPLC792_Cmd(0x38); // function set
	SPLC792_Cmd(0x39); // extension function set
	SPLC792_Cmd(0x14); // internal oscillator
	SPLC792_Cmd(0x70 | (SPLC792_CONTRAST & 15)); // contrast low
	SPLC792_Cmd(0x5c | (SPLC792_CONTRAST >> 4 & 3)); // contrast high / icon / power
	SPLC792_Cmd(0x6c); // follower control
	_delay_ms(200); // Wait for LCD's VCC stable
	SPLC792_Cmd(0x38); // function set
	SPLC792_Cmd(0x0c); // display on
	SPLC792_Cmd(0x01); // clear display (take 2ms)
	_delay_ms(2);
	
}

void SPLC792_Cmd(uint8_t cmd){
	I2C_Start();
	I2C_Send(BME280_I2C_ADDR);
	I2C_Send(0x00);
	I2C_Send(cmd);
	I2C_Stop();
	//_delay_us(27); // > 25us(400KHz*10?) + 1.3us
}

void SPLC792_Data(uint8_t data){
	I2C_Start();
	I2C_Send(BME280_I2C_ADDR);
	I2C_Send(0x40);
	I2C_Send(data);
	I2C_Stop();
	//_delay_us(27); // > 25us(400KHz*10?) + 1.3us
}

void SPLC792_Move(uint8_t pos){
	SPLC792_Cmd(0x80 | pos);
}

void SPLC792_puts(const char *s){
	while(*s){
		SPLC792_Data(*s++);
	}
}

void SPLC792_puts_8(char c0,char c1,char c2,char c3,char c4,char c5,char c6,char c7){
	SPLC792_Data(c0);
	SPLC792_Data(c1);
	SPLC792_Data(c2);
	SPLC792_Data(c3);
	SPLC792_Data(c4);
	SPLC792_Data(c5);
	SPLC792_Data(c6);
	SPLC792_Data(c7);
}