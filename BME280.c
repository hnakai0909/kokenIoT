/*
 * BME280.c
 *
 * Created: 2016/01/25 0:27:02
 *  Author: HarukiNakai
 */ 

#include "BME280.h"

uint8_t data_raw[8];
uint8_t data_dig[32];

int BME280_Init(void){
	
	uint8_t osrs_t = 2;             //Temperature oversampling x 1
	uint8_t osrs_p = 2;             //Pressure oversampling x 1
	uint8_t osrs_h = 2;             //Humidity oversampling x 1
	uint8_t mode = 3;               //Normal mode
	uint8_t t_sb = 5;               //Standby 1000ms
	uint8_t filter = 0;             //Filter off
	uint8_t spi3w_en = 0;           //3-wire SPI Disable
	
	uint8_t ctrl_hum_reg  = osrs_h;
	uint8_t ctrl_meas_reg = (osrs_t << 5) | (osrs_p << 2) | mode;
	uint8_t config_reg    = (t_sb << 5) | (filter << 2) | spi3w_en;
	
	BME280_WriteRegister(BME280_CTRL_HUM_ADDR, ctrl_hum_reg);
	BME280_WriteRegister(BME280_CTRL_MEAS_ADDR, ctrl_meas_reg);
	BME280_WriteRegister(BME280_CONFIG_ADDR, config_reg);
	
	
	return 0;
}

void BME280_WriteRegister(uint8_t regaddr, uint8_t data){
	I2C_Start();
	I2C_Send(BME280_I2C_ADDR<<1);
	I2C_Send(regaddr);
	I2C_Send(data);
	I2C_Stop();
}

void BME280_ReadRegister(uint8_t regaddr, uint8_t* data, uint8_t num, uint8_t offset){
	I2C_Start();
	//UDR0 = itoa_01x(TW_STATUS>>4); _delay_ms(1); UDR0 = itoa_01x(TW_STATUS&0x0f); _delay_ms(1);
	I2C_Send(BME280_I2C_ADDR<<1);
	I2C_Send(regaddr);
	I2C_Stop();
	I2C_Recv_Num(BME280_I2C_ADDR, data, num, offset);
}

void BME280_ReadData(void){
	uint8_t offset = 0;
	BME280_ReadRegister(0xF7, data_raw, 8, offset); // read raw pres,temp,hum
	offset += 8;
	
	offset = 0;
	BME280_ReadRegister(0x88, data_dig, 6, offset); // read dig_T regs
	offset += 6;
	
	BME280_ReadRegister(0x8E, data_dig, 8, offset); // read dig_P regs1	
	offset +=  8;

	BME280_ReadRegister(0x96, data_dig, 8, offset); // read dig_P regs2
	offset +=  8;
	
	BME280_ReadRegister(0x9E, data_dig, 2, offset); // read dig_P regs3
	offset +=  2;

	BME280_ReadRegister(0xA1, data_dig, 1, offset); // read dig_H1 regs
	offset +=  1;
	
	BME280_ReadRegister(0xE1, data_dig, 7, offset); // read dig_H2-6 regs
	offset +=  7;
}