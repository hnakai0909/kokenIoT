/*
 * config.h
 *
 * Created: 2016/01/24 17:54:30
 *  Author: HarukiNakai
 */ 

#ifndef CONFIG_H_
#define CONFIG_H_

/* FUSE書き換え忘れずに */
#define F_CPU 8000000
#define UART_BAUD 9600
#define MYUBRR (F_CPU / UART_BAUD / 16 - 1)

#define BME280_I2C_ADDR 0x76


#endif /* CONFIG_H_ */