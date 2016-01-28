/*
 * BME280.c
 *
 * Created: 2016/01/25 0:27:02
 *  Author: HarukiNakai
 */ 

#include "BME280.h"

int BME280_Init(void){
	
	BME280_WriteRegister(BME280_CTRL_MEAS_ADDR, 0);
	BME280_WriteRegister(BME280_CONFIG_ADDR, 0);
	BME280_WriteRegister(BME280_CTRL_HUM_ADDR, 0);
	
	return 0;
}

int BME280_WriteRegister(uint8_t addr,uint8_t data){
	I2C_Start();
	I2C_Send(BME280_I2C_ADDR);
	if (TW_STATUS != TW_MT_SLA_ACK) { return 1;	}
	I2C_Send(addr);
	if (TW_STATUS != TW_MT_SLA_ACK) { return 1;	}
	I2C_Send(data);
	if (TW_STATUS != TW_MT_SLA_ACK) { return 1;	}
	I2C_Stop();
	return 0;
}