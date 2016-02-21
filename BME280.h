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
#include <math.h>
#include "twi.h"
#include "myutil.h"

extern uint32_t pres_raw,temp_raw,hum_raw;

int BME280_Init(void);

void BME280_WriteRegister(uint8_t regaddr, uint8_t data);
void BME280_ReadRegister(uint8_t regaddr, uint8_t* data, uint8_t num, uint8_t offset);

void BME280_ReadData(void);

#endif /* BME280_H_ */