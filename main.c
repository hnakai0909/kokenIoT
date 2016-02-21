/*
 * kokenIoT.c
 *
 * Created: 2016/01/23 4:38:27
 * Author : HarukiNakai
 */ 

#include "main.h"

unsigned char pinc,pind;
unsigned char pyro1, pyro2; // ドア前焦電センサ反応?
unsigned char door; // ドア開?
unsigned char existence; // 在室?(蛍光灯 点or滅)
unsigned char button; // 0無押下,1選択,2決定,3取消 (同時押しは知らない)
uint8_t adc_val;

uint8_t bflag = 0;
uint8_t bmode = 0;
//F+D>A<DEA2>A<EF+E>A<D2: familymart
uint8_t bdata[16] = {85,106,142,106,95,71,71,142,95,85,95,142,106,106,106,0};

char UART_TXbuf[UART_TXBUF_SIZE];
uint8_t UART_TXbuf_head = 0;
uint8_t UART_TXbuf_tail = 0;

// door,pyro
ISR(PCINT1_vect){
	pinc = PINC;
	pyro1 = (bit_is_set(pinc, PINC0)) ? 1 : 0;
	pyro2 = (bit_is_set(pinc, PINC1)) ? 1 : 0;
	door  = (bit_is_set(pinc, PINC3)) ? 1 : 0;
}

// button
ISR(PCINT2_vect){
	// Enable interrupt
	TIMSK1 = _BV(OCIE1A);
	TCNT1 = 0;
	OCR1A = 1000; // 7812で1秒のはず
	PCICR = _BV(PCIE1); // チャタリング対策
	PCMSK2 = 0;
	if(bflag==1){
		return;
	}
	bflag = 1;
	pind = PIND;
	if(bit_is_clear(pind, PIND2)){
		button = 1;
	} else if (bit_is_clear(pind, PIND3)){
		button = 2;
	} else if (bit_is_clear(pind, PIND4)){
		button = 3;
	} else {
		button = 0;
	}
	if(button!=0){
		Beep_Play(142);// 440.1 hz
		SPLC792_Data('*');
	}
}

ISR(TIMER1_COMPA_vect){
	TIMSK1 = 0x00; // Stop Interrupt
	TCNT1 = 0;
	OCR1A = 0;
	TCCR0A = 0x00;
	OCR0A = 0;
	PCICR = _BV(PCIE2) | _BV(PCIE1);
	PCMSK2 = _BV(PCINT20) | _BV(PCINT19) | _BV(PCINT18);
	bflag=0;
}

ISR(ADC_vect){
	adc_val = ( ADC >> 3 );       // AD変換結果10bit 3bitｼﾌﾄ= 7bit:0-127 (ここで割り込みが起きてはいけない)
	if(adc_val < 12){
		existence = TRUE;
	} else {
		existence = FALSE;
	}	
}

int main(void)
{
	uint8_t i=0;
	char str[64];
	_delay_ms(40); // Wait for VDD stable
	Init();
	SplashScreen();
    while (1) 
    {
		// pyro1,pyro2,door,button,existence,adc_val
		SPLC792_Cmd(0x03);
		SPLC792_Data('0'+pyro1);SPLC792_Data(',');
		SPLC792_Data('0'+pyro2);SPLC792_Data(',');
		SPLC792_Data('0'+door);SPLC792_Data(',');
		SPLC792_Data('0'+existence);SPLC792_Data(',');
		
		SPLC792_puts(itoa_03d(str,adc_val));SPLC792_Data(',');
		SPLC792_Data('0'+i); // 生死確認用
		BME280_ReadData();
		if(bmode == 0 && door == 1){
			bmode=1;
		}
		if(bmode > 0){
			Beep_Play(bdata[bmode-1]);
			bmode++;
		}
		if(bmode >= 16 && bmode!=127){
			Beep_Stop();
			bmode = 127;
		}
		if(bmode == 127 && door == 0){
			bmode = 0;
		}
		
		i++;
		if(i>=10){i=0;}
		
		_delay_ms(300);
		
    }
}

static inline void Init(void){
	GPIO_Init();
	UART_Init();
	I2C_Init();
	ADC_Init();
	Timer_Init();
	PWM_Init();
	PCINT_Init();
	
	BME280_Init();
	SPLC792_Init();
	
	sei();
}

static inline void GPIO_Init(void){
	//0:input 1:out\put
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
	UCSR0A = 0b00000000;
	UCSR0B = _BV(RXCIE0) | _BV(RXEN0) | _BV(TXEN0);
	UCSR0C = _BV(UCSZ01) | _BV(UCSZ00);
}

static inline void ADC_Init(void){
	ADCSRA = 0b11101110; // AD許可:1 AD開始:1 AD自動起動:1 AD割込:0 AD完了割込:1 ck/64
	ADMUX = 0b11000010; //AREF=1.1V, 入力:ADC2(PC2)	
}

static inline void Timer_Init(void){
	TCCR1A = 0b00000000; // no PWM
	TCCR1B = 0b00001101; //Prescaler: 1/1024, TOP=OCR1A
	OCR1A = 0;
}

static inline void PWM_Init(void){
	TCCR0B = 0b00001011; // Prescaler: 1/64,
	OCR0A = 127;
}

static inline void PCINT_Init(void){
	PCICR = _BV(PCIE2) | _BV(PCIE1);
	PCMSK2 = _BV(PCINT20) | _BV(PCINT19) | _BV(PCINT18);
	PCMSK1 = _BV(PCINT11) | _BV(PCINT9) | _BV(PCINT8);
}

void Beep_Play(uint8_t freq){
	TCCR0A = 0b01000010; // Fast PWM, OC:Toggle, TOP=OCR2A
	OCR0A = freq;//28で1000Hzくらいのはず..?
}

void Beep_Stop(void){
	TCCR0A = 0x00;
	OCR0A = 0;
}

void SplashScreen(void){
	SPLC792_Cmd(0x03);
	SPLC792_puts("koken IoT System");
	SPLC792_Cmd(0xC0);
	SPLC792_puts("  ver 0.02 alpha");
	Beep_Play(46);
	_delay_ms(100);
	Beep_Play(92);
	_delay_ms(100);
	Beep_Stop();
	_delay_ms(800);
	SPLC792_Cmd(0x01); // clear display (take 2ms)
	_delay_ms(2);
}