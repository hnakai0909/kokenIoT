/*
 * kokenIoT.c
 *
 * Created: 2016/01/23 4:38:27
 * Author : HarukiNakai
 */ 

#include "main.h"

int pinc,pind;
int existence; // 在室?(蛍光灯 点or滅)
int door; //ドア開?
int pyro1, pyro2; //ドア前焦電センサ反応?
int button; // 0無押下,1選択,2決定,3取消 (同時押しは知らない)

int main(void)
{
	int a;
	char str[4];
	_delay_ms(40); // Wait for VDD stable
	Init();
    while (1) 
    {
		
		ADCSRA |= _BV(ADSC);       //変換開始
		loop_until_bit_is_set(ADCSRA,ADIF);  //変換終了時ADIFがセットされる
		a = ( ADC >> 4 );       //AD変換結果 4bitｼﾌﾄ= 6bit:0-64
		if(a < 32){
			existence = TRUE;
		} else {
			existence = FALSE;
		}
		
		pinc = PINC;
		pind = PIND;
		pyro1 = bit_is_set(pinc, PINC0);
		pyro2 = bit_is_set(pinc, PINC1);
		door = bit_is_set(pinc, PINC3);
		if(bit_is_set(pind, PIND2)){
			button = 1;
		} else if (bit_is_set(pind, PIND3)){
			button = 2;
		} else if (bit_is_set(pind, PIND4)){
			button = 3;
		} else {
			button = 0;
		}
		SPLC792_puts(itoa_03d(str,pyro1));
		_delay_ms(100);
		
    }
}

static inline void Init(void){
	GPIO_Init();
	UART_Init();
	I2C_Init();
	ADC_Init();
	Timer_Init();
	PWM_Init();
	
	BME280_Init();
	SPLC792_Init();
}

static inline void GPIO_Init(void){
	//0:input 1:output
	DDRB = 0b11111111;
	PORTB = 0b00000000;
	
	DDRC = 0b11110000;
	PORTC = 0b00000000;
	
	DDRD = 0b11100010;
	PORTD = 0b00000000;
}

static inline void UART_Init(void){
	// baud rate
	UBRR0 = MYUBRR;
	
	// no interrupt
	// asynchronous, no parity, stop-bit = 1bit, data-bit = 8bit
	UCSR0A = 0x00000000;
	UCSR0B = _BV(RXEN0) | _BV(TXEN0) | (0 << UCSZ02);
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
}



static inline void ADC_Init(void){
	ADCSRA = 0b10000100; // AD許可:1 AD開始:0 AD自動起動:0 AD割込:0 AD完了割込:0 ck/16
	ADMUX = 0b01000010; //AREF=VCC (AREFピンにはコンデンサをつけなければならない), 入力:ADC2(PC2)	
}

static inline void Timer_Init(void){
	
}

static inline void PWM_Init(void){
	
}
