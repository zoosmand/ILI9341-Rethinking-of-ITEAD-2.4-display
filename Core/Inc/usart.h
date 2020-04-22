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
/* Pins defines */
#define TX_Pin          GPIO_PIN_9
#define TX_Pin_Pos      GPIO_PIN_9_Pos
#define RX_Pin          GPIO_PIN_10
#define RX_Pin_Pos      GPIO_PIN_10_Pos
#define USART_Port      GPIOA

/* Circular buffer defines */
#define RXBUF_LEN       64
#define RXBUF_MASK      (RXBUF_LEN - 1)


/* Exported functions prototypes ---------------------------------------------*/
void USART1_Init(void);
void USART1_RX_Handler(void);
uint8_t USART_RxBufferRead(uint8_t *buf, uint16_t len);

#ifdef __cplusplus
}
#endif
#endif /*__ USART_H */

