/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/main.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main program body
  ******************************************************************************
  * @attention
  *
  * THE PRESENT FIRMWARE WHICH IS FOR GUIDANCE ONLY AIMS AT PROVIDING CUSTOMERS
  * WITH CODING INFORMATION REGARDING THEIR PRODUCTS IN ORDER FOR THEM TO SAVE
  * TIME. AS A RESULT, STMICROELECTRONICS SHALL NOT BE HELD LIABLE FOR ANY
  * DIRECT, INDIRECT OR CONSEQUENTIAL DAMAGES WITH RESPECT TO ANY CLAIMS ARISING
  * FROM THE CONTENT OF SUCH FIRMWARE AND/OR THE USE MADE BY CUSTOMERS OF THE
  * CODING INFORMATION CONTAINED HEREIN IN CONNECTION WITH THEIR PRODUCTS.
  *
  * <h2><center>&copy; COPYRIGHT 2011 STMicroelectronics</center></h2>
  ******************************************************************************
  */  

/* Includes ------------------------------------------------------------------*/
#include "stm32f10x.h"
#include <stdio.h>
#include "stm32f10x_rcc.h"
#include "delay.h"
#include "Uart.h" 
#include "epson_m150ii.h"

ErrorStatus HSEStartUpStatus;

extern u8 print_real[7][12]; 
uint8_t byPrinter_head_ITFlag;	// 中断处理标志位

void RCC_Configuration(void)
{   
	/* RCC system reset(for debug purpose) */
	RCC_DeInit();

	/* Enable HSE */
	RCC_HSEConfig(RCC_HSE_ON);

	/* Wait till HSE is ready */
	HSEStartUpStatus = RCC_WaitForHSEStartUp();

	if(HSEStartUpStatus == SUCCESS)
	{
		/* HCLK = SYSCLK */
		RCC_HCLKConfig(RCC_SYSCLK_Div1); 
  
		/* PCLK2 = HCLK */
		RCC_PCLK2Config(RCC_HCLK_Div1); 

		/* PCLK1 = HCLK/2 */
		RCC_PCLK1Config(RCC_HCLK_Div2);

		/* Flash 2 wait state */
		FLASH_SetLatency(FLASH_Latency_2);
		/* Enable Prefetch Buffer */
		FLASH_PrefetchBufferCmd(FLASH_PrefetchBuffer_Enable);

		/* PLLCLK = 8MHz * 9 = 72 MHz */
		RCC_PLLConfig(RCC_PLLSource_HSE_Div1, RCC_PLLMul_9);

		/* Enable PLL */ 
		RCC_PLLCmd(ENABLE);

		/* Wait till PLL is ready */
		while(RCC_GetFlagStatus(RCC_FLAG_PLLRDY) == RESET)
		{
		}

		/* Select PLL as system clock source */
		RCC_SYSCLKConfig(RCC_SYSCLKSource_PLLCLK);

		/* Wait till PLL is used as system clock source */
		while(RCC_GetSYSCLKSource() != 0x08)
		{
		}
	}


	RCC_APB2PeriphClockCmd(RCC_APB2Periph_TIM1 | 
		RCC_APB2Periph_GPIOA |
		RCC_APB2Periph_GPIOB |
		RCC_APB2Periph_ADC1 |
		RCC_APB2Periph_USART1 |
		RCC_APB2Periph_AFIO,		
		ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART2 |
		RCC_APB1Periph_TIM4, 
		ENABLE);

	RCC_APB1PeriphClockCmd(RCC_APB1Periph_USART3, 
		ENABLE);

	/* Enable DMA clock */
	RCC_AHBPeriphClockCmd(RCC_AHBPeriph_DMA1, ENABLE);
	//	SEGGER_RTT_printf(0, "sysclock is %d", SystemCoreClock );
}

/******************************************************************************
函数原型:	void Nvic_Init(void)
功    能:	NVIC 初始化
*******************************************************************************/ 
void Nvic_Init(void)
{
	NVIC_InitTypeDef NVIC_InitStructure;
	
	// NVIC_PriorityGroup 
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);		// 位于同一组别, 

	// Reset	PB10 
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;	// Reset signal
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	// Timing  PB6
	NVIC_InitStructure.NVIC_IRQChannel = EXTI9_5_IRQn;		// Timing 
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
	
	// USART ( 串口)
	NVIC_InitStructure.NVIC_IRQChannel = USART1_IRQn;		// USART
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_Init(&NVIC_InitStructure);
}

void Printer_work(void)
{
	if(byPrinter_head_ITFlag == 0x01)
	{
		//Printer_Font_Extract("A1B2C3");	// 提取先关的数据
//		Printer_Font_Extract("A1B2C3D4");
		print_matrix_invert();		// 打印点阵的置换
		Printer_line();	// 打印一行
	}
}

int main(void)
{
	RCC_Configuration();	
	Uart1_Init(115200);	// 串口初始化： 波特率 115200, 8 数据位, 1 位停止位, 禁用奇偶校验
	delay_init();		// 延时初始化
	
	Printer_IO_Config();	// 打印机 IO 初始化
	Nvic_Init();			// 中断优先级初始化
	Printer_Timer_Init();  // 打印前初始化变量
	
	MOTER_ON();
	delay_ms(200);
	Printer_Font_Extract("A1B2C3D4");

//	memset(print_real, 0xFF, sizeof(print_real));

  	while (1)
  	{
  		Printer_work();
  	}
}

