/**
  ******************************************************************************
  * @file    Project/STM32F10x_StdPeriph_Template/stm32f10x_it.c 
  * @author  MCD Application Team
  * @version V3.5.0
  * @date    08-April-2011
  * @brief   Main Interrupt Service Routines.
  *          This file provides template for all exceptions handler and 
  *          peripherals interrupt service routine.
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
#include "stm32f10x_it.h"
#include "epson_m150ii.h"
#include "stm32f10x_gpio.h"
#include "string.h"

/** @addtogroup STM32F10x_StdPeriph_Template
  * @{
  */

/* Private typedef -----------------------------------------------------------*/
/* Private define ------------------------------------------------------------*/
/* Private macro -------------------------------------------------------------*/
/* Private variables ---------------------------------------------------------*/
/* Private function prototypes -----------------------------------------------*/
/* Private functions ---------------------------------------------------------*/

/******************************************************************************/
/*            Cortex-M3 Processor Exceptions Handlers                         */
/******************************************************************************/

/**
  * @brief  This function handles NMI exception.
  * @param  None
  * @retval None
  */
void NMI_Handler(void)
{
}

/**
  * @brief  This function handles Hard Fault exception.
  * @param  None
  * @retval None
  */
void HardFault_Handler(void)
{
  /* Go to infinite loop when Hard Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Memory Manage exception.
  * @param  None
  * @retval None
  */
void MemManage_Handler(void)
{
  /* Go to infinite loop when Memory Manage exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Bus Fault exception.
  * @param  None
  * @retval None
  */
void BusFault_Handler(void)
{
  /* Go to infinite loop when Bus Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles Usage Fault exception.
  * @param  None
  * @retval None
  */
void UsageFault_Handler(void)
{
  /* Go to infinite loop when Usage Fault exception occurs */
  while (1)
  {
  }
}

/**
  * @brief  This function handles SVCall exception.
  * @param  None
  * @retval None
  */
void SVC_Handler(void)
{
}

/**
  * @brief  This function handles Debug Monitor exception.
  * @param  None
  * @retval None
  */
void DebugMon_Handler(void)
{
}

/**
  * @brief  This function handles PendSVC exception.
  * @param  None
  * @retval None
  */
void PendSV_Handler(void)
{
}

/**
  * @brief  This function handles SysTick Handler.
  * @param  None
  * @retval None
  */
void SysTick_Handler(void)
{
}

/******************************************************************************/
/*                 STM32F10x Peripherals Interrupt Handlers                   */
/*  Add here the Interrupt Handler for the used peripheral(s) (PPP), for the  */
/*  available peripheral interrupt handler's name please refer to the startup */
/*  file (startup_stm32f10x_xx.s).                                            */
/******************************************************************************/

/**
  * @brief  This function handles PPP interrupt request.
  * @param  None
  * @retval None
  */
/*void PPP_IRQHandler(void)
{
}*/

// -------- flag variable --------- //
extern uint8_t byPrinter_head_ITFlag ;
extern uint8_t g_bTimingIntr;
extern uint8_t g_bResetIntr;

/**
  * @} EXTI9_5_IRQHandler()
  */
void EXTI9_5_IRQHandler(void)		
{	
	/******  PB8 -->>  Reset    ||    PB9 -->> Timing **********/ 

	if(EXTI_GetITStatus(EXTI_Line9) != RESET)	// PB8 -->> Timing
	{
		// 中断逻辑 --->>> 进行打印机的处理
		byPrinter_head_ITFlag = 0x01; 	// 打印机针头处理标志位
		g_bTimingIntr = 0x01;
		

//		Printer_Font_Extract("1.88 km");
//		Printer_line();
//		memset(ascii_printer, 0x00, sizeof(ascii_printer));
//		memset(print_real, 0x00, sizeof(print_real));
		
		EXTI_ClearITPendingBit(EXTI_Line9);		// Clean IT Flag
	}   

	if(EXTI_GetITStatus(EXTI_Line8) != RESET)	// PB9 -->> Reset
	{
		// 中断逻辑     
		g_bResetIntr = 0x01;
		byPrinter_head_ITFlag = 0x00;		// 打印机针头标志位清零

		EXTI_ClearITPendingBit(EXTI_Line8);		// Clean IT Flag
	}
	
	
//		EXTI_ClearITPendingBit(EXTI_Line9);		// Clean IT Flag
//		EXTI_ClearITPendingBit(EXTI_Line8);		// Clean IT Flag
	
	
}

/**
  * @} EXTI15_10_IRQHandler()
  */

//void EXTI15_10_IRQHandler(void)		// Reset Signal
//{
//}

/******************* (C) COPYRIGHT 2011 STMicroelectronics *****END OF FILE****/
