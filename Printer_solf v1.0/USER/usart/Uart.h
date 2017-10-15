#ifndef _UART_H_
#define _UART_H_
#include "stm32f10x.h"

/******************************************************************************
							全局函数声明
*******************************************************************************/ 
void Uart1_Init(uint32_t baud);
void PrintHexU8(uint8_t data);
void PrintHexS16(int16_t num);
void PrintS8( int8_t num);
void PrintU8(uint8_t num);
void PrintS16( int16_t num);
void PrintU16(uint16_t num);
void PrintString(uint8_t *s);

#endif
