/*
 * myutil.c
 *
 * Created: 2016/01/28 4:26:47
 *  Author: HarukiNakai
 */ 

#include "myutil.h"

// 0 - 199 のみ対応
char* itoa_03d(char* str,int num){
	int tmp;
	if(num >= 100){
		num -= 100;
		str[0] = '1';
	} else {
		str[0] = '0';	
	};
	tmp = '0';
	while(num >= 10){
		num -= 10;
		tmp++;		
	}
	str[1] = tmp;
	str[2] = '0' + num;
	str[3] = '\0';
	return str;
}

// 0-15 -> '0'-'9','A'-'F'
char itoa_01x(unsigned int num){
	return (num >= 10) ? ('A' + num - 10) : ('0' + num);
}