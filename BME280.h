/*
 * BME280.h
 *
 * Created: 2016/01/25 0:25:53
 *  Author: HarukiNakai
 */ 

#ifndef BME280_H_
#define BME280_H_

#define BME280_CTRL_HUM_ADDR 0xF2
#define BME280_CTRL_MEAS_ADDR 0xF4
#define BME280_CONFIG_ADDR 0xF5

#define BME280_CTRL_HUM_DATA (OSRS_T<<5)|(OSRS_P<<2)|MODE;

#include "config.h"

#include <avr/io.h>
#include <avr/sfr_defs.h>
#include <util/delay.h>
#include <util/twi.h>
#include "twi.h"

extern uint32_t pres_raw,temp_raw;
extern uint16_t hum_raw;

int BME280_Init(void);
int BME280_WriteRegister(uint8_t addr,uint8_t data);

void BME280_ReadData(void);


int32_t calibration_T(int32_t adc_T);
uint32_t calibration_P(int32_t adc_P);
uint32_t calibration_H(int32_t adc_H);

#endif /* BME280_H_ */