/*
 * BME280.c
 *
 * Created: 2016/01/25 0:27:02
 *  Author: HarukiNakai
 */ 

#include "BME280.h"

// t_fine carries fine temperature as global value
int32_t t_fine;

uint16_t dig_T1;
int16_t dig_T2;
int16_t dig_T3;
uint16_t dig_P1;
int16_t dig_P2;
int16_t dig_P3;
int16_t dig_P4;
int16_t dig_P5;
int16_t dig_P6;
int16_t dig_P7;
int16_t dig_P8;
int16_t dig_P9;
int8_t  dig_H1;
int16_t dig_H2;
int8_t  dig_H3;
int16_t dig_H4;
int16_t dig_H5;
int8_t  dig_H6;

int BME280_Init(void){
	
	uint8_t osrs_t = 1;             //Temperature oversampling x 1
	uint8_t osrs_p = 1;             //Pressure oversampling x 1
	uint8_t osrs_h = 1;             //Humidity oversampling x 1
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

int BME280_WriteRegister(uint8_t addr,uint8_t data){
	I2C_Start();
	I2C_Send(BME280_I2C_ADDR);
	I2C_Send(addr);
	I2C_Send(data);
	I2C_Stop();
	return 0;
}

void BME280_ReadData(void){
	int i = 0;
	uint32_t data[8];
	I2C_Start();
	I2C_Send(BME280_I2C_ADDR<<1); //Write
	I2C_Send(0xF7);
	I2C_Stop();
	I2C_Start();
	I2C_Send(BME280_I2C_ADDR<<1 | 1); //Read
	
	I2C_Send(0xF7);
	for(i=0;i<8;i++){
		data[i] = I2C_Recv();
	}
	pres_raw = (data[0] << 12) | (data[1] << 4) | (data[2] >> 4);
	temp_raw = (data[3] << 12) | (data[4] << 4) | (data[5] >> 4);
	hum_raw  = (data[6] << 8) | data[7];
	
	I2C_Send(0x88); // read dig_T regs
	for(i=0;i<6;i++){
		data[i] = I2C_Recv();
	}
	dig_T1 = (data[1] << 8) | data[0];
	dig_T2 = (data[3] << 8) | data[2];
	dig_T3 = (data[5] << 8) | data[4];
	
	I2C_Send(0x8E); // read dig_P regs
	for(i=0;i<8;i++){
		data[i] = I2C_Recv();
	}
	dig_P1 = (data[ 1] << 8) | data[ 0];
	dig_P2 = (data[ 3] << 8) | data[ 2];
	dig_P3 = (data[ 5] << 8) | data[ 4];
	dig_P4 = (data[ 7] << 8) | data[ 6];
	for(i=0;i<8;i++){
		data[i] = I2C_Recv();
	}
	dig_P5 = (data[ 1] << 8) | data[ 0];
	dig_P6 = (data[ 3] << 8) | data[ 2];
	dig_P7 = (data[ 5] << 8) | data[ 4];
	dig_P8 = (data[ 7] << 8) | data[ 6];
	for(i=0;i<2;i++){
		data[i] = I2C_Recv();
	}
	dig_P9 = (data[1] << 8) | data[0];
	 
	
	I2C_Send(0xA1); // read dig_H regs
	data[0] = I2C_Recv();
	I2C_Send(0xE1); // read dig_H regs
	for(i=1;i<8;i++){
		data[i] = I2C_Recv();
	}
	dig_H1 = data[0];
	dig_H2 = (data[2] << 8) | data[1];
	dig_H3 = data[3];
	dig_H4 = (data[4] << 4) | (data[5] & 0x0f);
	dig_H5 = (data[6] << 4) | ((data[5]>>4) & 0x0f);
	dig_H6 = data[7];
	
}

int32_t calibration_T(int32_t adc_T)
{
	
	int32_t var1, var2, T;
	var1 = ((((adc_T >> 3) - ((int32_t)dig_T1<<1))) * ((int32_t)dig_T2)) >> 11;
	var2 = (((((adc_T >> 4) - ((int32_t)dig_T1)) * ((adc_T>>4) - ((int32_t)dig_T1))) >> 12) * ((int32_t)dig_T3)) >> 14;
	
	t_fine = var1 + var2;
	T = (t_fine * 5 + 128) >> 8;
	return T;
}

uint32_t calibration_P(int32_t adc_P)
{
	int32_t var1, var2;
	uint32_t P;
	var1 = (((int32_t)t_fine)>>1) - (int32_t)64000;
	var2 = (((var1>>2) * (var1>>2)) >> 11) * ((int32_t)dig_P6);
	var2 = var2 + ((var1*((int32_t)dig_P5))<<1);
	var2 = (var2>>2)+(((int32_t)dig_P4)<<16);
	var1 = (((dig_P3 * (((var1>>2)*(var1>>2)) >> 13)) >>3) + ((((int32_t)dig_P2) * var1)>>1))>>18;
	var1 = ((((32768+var1))*((int32_t)dig_P1))>>15);
	if (var1 == 0)
	{
		return 0;
	}
	P = (((uint32_t)(((int32_t)1048576)-adc_P)-(var2>>12)))*3125;
	if(P<0x80000000)
	{
		P = (P << 1) / ((uint32_t) var1);
	}
	else
	{
		P = (P / (uint32_t)var1) * 2;
	}
	var1 = (((int32_t)dig_P9) * ((int32_t)(((P>>3) * (P>>3))>>13)))>>12;
	var2 = (((int32_t)(P>>2)) * ((int32_t)dig_P8))>>13;
	P = (uint32_t)((int32_t)P + ((var1 + var2 + dig_P7) >> 4));
	return P;
}

uint32_t calibration_H(int32_t adc_H)
{
	int32_t v_x1;
	
	v_x1 = (t_fine - ((int32_t)76800));
	v_x1 = (((((adc_H << 14) -(((int32_t)dig_H4) << 20) - (((int32_t)dig_H5) * v_x1)) +
	((int32_t)16384)) >> 15) * (((((((v_x1 * ((int32_t)dig_H6)) >> 10) *
	(((v_x1 * ((int32_t)dig_H3)) >> 11) + ((int32_t) 32768))) >> 10) + (( int32_t)2097152)) *
	((int32_t) dig_H2) + 8192) >> 14));
	v_x1 = (v_x1 - (((((v_x1 >> 15) * (v_x1 >> 15)) >> 7) * ((int32_t)dig_H1)) >> 4));
	v_x1 = (v_x1 < 0 ? 0 : v_x1);
	v_x1 = (v_x1 > 419430400 ? 419430400 : v_x1);
	return (uint32_t)(v_x1 >> 12);
}