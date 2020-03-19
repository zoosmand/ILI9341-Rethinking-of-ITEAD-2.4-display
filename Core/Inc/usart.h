/**
  ******************************************************************************
  * File Name          : USART.h
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef __USART_H
#define __USART_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private defines -----------------------------------------------------------*/
#define TX_Pin          GPIO_PIN_9
#define TX_Pin_Pos      GPIO_PIN_9_Pos
#define RX_Pin          GPIO_PIN_10
#define RX_Pin_Pos      GPIO_PIN_10_Pos
#define USART_Port      GPIOA

/* Exported functions prototypes ---------------------------------------------*/
void USART1_Init(void);
void USART1_RX_Handler(uint8_t *buf, uint16_t len);
void USART1_RX_FromIT_Handler();

#ifdef __cplusplus
}
#endif
#endif /*__ USART_H */

