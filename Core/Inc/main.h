/**
  ******************************************************************************
  * @file           : main.h
  * @brief          : Header for main.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __MAIN_H
#define __MAIN_H

#ifdef __cplusplus
extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#include "stm32f0xx.h"

/* Private includes ----------------------------------------------------------*/
#include "common.h"
#include "tim.h"
#include "usart.h"
#include "ili9341.h"
#include "fonts.h"
#include "display.h"
#include "spi.h"
#include "w25qxx.h"
#include "stm32f0xx_it.h"

/* Exported types ------------------------------------------------------------*/

/* Exported constants --------------------------------------------------------*/

/* Exported variables --------------------------------------------------------*/
extern uint32_t sysQuantum;
extern uint32_t millis;
extern uint32_t seconds;
extern uint32_t minutes;
extern uint32_t _EREG_;
extern uint32_t check;
extern uint32_t SystemCoreClock;
extern uint8_t eepromReady;

/* Private defines -----------------------------------------------------------*/
#define SWO_USART

// _EREG_ Flags    
#define _BT6F_    0 // Basic Timer6 Flag
// #define _RTCALAF_ 1 // RTC Alarm A Flag
// #define _RTCALBF_ 2 // RTC Alarm B Flag
// #define _RTWUPF_  3 // RTC Wake Up Flag
#define _RDF_     4 // Run Display Flag
// #define _DDF_     5 // Display Delay Flag
// #define _DBLF_    6 // Data Buffer is Locked Flag
#define _U1RXF_   7 // USART1 RXNE Interrupt occurs Flag
// #define _BLINKF_  8 // Blink Flaf
#define _DELAYF_  9 // Delay Flag
// #define _EWUPF_   10 // EXTI WakeUp PA0 Flag
// #define _ETSF_    11 // EXTI Touch Screen PA15 Flag
#define _TBLF_    12 // Transfer Buffer is Locked Flag

/* Exported functions prototypes ---------------------------------------------*/
extern void Delay_Handler(uint32_t delay);
extern void Delay(uint32_t delay);
extern void Cron_Handler(void);


#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */

/************************ (C) COPYRIGHT STMicroelectronics *****END OF FILE****/
