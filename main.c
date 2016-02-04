/*
 * kokenIoT.c
 *
 * Created: 2016/01/23 4:38:27
 * Author : HarukiNakai
 */ 

#include "main.h"

unsigned char pinc,pind;
unsigned char existence; // 在室?(蛍光灯 点or滅)
unsigned char door; //ドア開?
unsigned char pyro1, pyro2; //ドア前焦電センサ反応?
unsigned char button; // 0無押下,1選択,2決定,3取消 (同時押しは知らない)
uint32_t pres_raw,temp_raw;
uint32_t hum_raw;

double temp_act = 0.0, press_act = 0.0,hum_act=0.0;
int32_t temp_cal;
uint32_t press_cal,hum_cal;

// door,pyro
ISR(PCINT1_vect){
		
}

//button
ISR(PCINT2_vect){
	
}

ISR(TIMER2_COMPA_vect){
	
}

int main(void)
{
	uint8_t a;
	char str[64];
	_delay_ms(40); // Wait for VDD stable
	Init();
	//_delay_ms(120);
    while (1) 
    {
		
		ADCSRA |= _BV(ADSC);       //変換開始
		loop_until_bit_is_set(ADCSRA, ADIF);  //変換終了時ADIFがセットされる
		a = ( ADC >> 4 );       //AD変換結果 4bitｼﾌﾄ= 6bit:0-64
		if(a < 32){
			existence = TRUE;
		} else {
			existence = FALSE;
		}
		
		pinc = PINC;
		pind = PIND;
		pyro1 = (bit_is_set(pinc, PINC0)) ? 1 : 0;
		pyro2 = (bit_is_set(pinc, PINC1)) ? 1 : 0;
		door  = (bit_is_set(pinc, PINC3)) ? 1 : 0;
		if(bit_is_clear(pind, PIND2)){
			button = 1;
		} else if (bit_is_clear(pind, PIND3)){
			button = 2;
		} else if (bit_is_clear(pind, PIND4)){
			button = 3;
		} else {
			button = 0;
		}
		UDR0 = '\r';_delay_ms(1);UDR0 = '\n';_delay_ms(1);
		UDR0 = '0' + button;_delay_ms(1);
		//SPLC792_puts_8('P', '0'+pyro1, '0'+pyro2, 'D', '0'+door, 'E', '0'+existence, ' ');
		//SPLC792_puts_8('A','B','C','D','A','B','C','D');
		sprintf(str,"Pyro:%d,%d Door:%d Btn:%d Exi:%d(raw:%d)\n",pyro1,pyro2,door,button,existence,a);
		UART_puts(str);
		_delay_ms(35);
		
		BME280_ReadData();
		sprintf(str,"Raw: t=%lu p=%lu h=%lu ",temp_raw,pres_raw,hum_raw);
		UART_puts(str);
		SPLC792_Cmd(0x03);SPLC792_puts(str);
		_delay_ms(35);
		temp_cal = calibration_T(temp_raw);
		press_cal = calibration_P(pres_raw);
		hum_cal = calibration_H(hum_raw);
		temp_act = (double)temp_cal / 100.0;
		press_act = (double)press_cal / 100.0;
		hum_act = (double)hum_cal / 1024.0;
		
		sprintf(str,"Act: t=%.2f p=%.2f h=%.2f ",temp_act,press_act,hum_act);
		UART_puts(str);
		
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
	//PCINT_Init();
	
	BME280_Init();
	SPLC792_Init();
	
	//sei();
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

static inline void PCINT_Init(void){
	PCICR = _BV(PCIE2) | _BV(PCIE1);
	PCMSK2 = _BV(PCINT20) | _BV(PCINT19) | _BV(PCINT18);
	PCMSK1 = _BV(PCINT11) | _BV(PCINT9) | _BV(PCINT8);
}