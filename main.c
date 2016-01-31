/*
 * kokenIoT.c
 *
 * Created: 2016/01/23 4:38:27
 * Author : HarukiNakai
 */ 

#include "main.h"

int pinc;
int existence; // �ݎ�?(�u�����_or��)
int door; //�h�A�J?
int pyro1, pyro2; //�h�A�O�œd�Z���T����?

int main(void)
{
	int a,i;
	char str[4];
	_delay_ms(40); // Wait for VDD stable
	Init();
    while (1) 
    {
		
		ADCSRA |= _BV(ADSC);       //�ϊ��J�n
		loop_until_bit_is_set(ADCSRA,ADIF);  //�ϊ��I����ADIF���Z�b�g�����
		a = ( ADC >> 4 );       //AD�ϊ����� 4bit���= 6bit:0-64
		if(a<32){
			existence = TRUE;
		} else {
			existence = FALSE;
		}
		
		pinc = PINC;
		pyro1 = bit_is_set(pinc, PINC0);
		pyro2 = bit_is_set(pinc, PINC1);
		door = bit_is_set(pinc, PINC3);
		SPLC792_puts(itoa_03d(str,pyro1));
		
		for(i=0;i<5;i++){
			_delay_ms(100);
		}
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
	
	DDRD = 0b11111111;
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
	ADCSRA = 0b10000100; // AD����:1 AD�J�n:0 AD�����N��:0 AD����:0 AD��������:0 ck/16
	ADMUX = 0b01000010; //AREF=VCC (AREF�s���ɂ̓R���f���T�����Ȃ���΂Ȃ�Ȃ�), ����:ADC2(PC2)	
}

static inline void Timer_Init(void){
	
}

static inline void PWM_Init(void){
	
}
