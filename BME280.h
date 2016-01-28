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

int BME280_Init(void);
int BME280_WriteRegister(uint8_t addr,uint8_t data);



#endif /* BME280_H_ */