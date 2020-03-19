/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* Private variables ---------------------------------------------------------*/
static uint8_t rxBuf[32];










////////////////////////////////////////////////////////////////////////////////

void USART1_Init(void) {
  uint32_t baudRate = 115200;

  /* Enable GPIO alternative #1 on hight speed */
  USART_Port->MODER   |= ((_AF << (TX_Pin_Pos * 2U)) | (_AF << (RX_Pin_Pos * 2U)));
  USART_Port->OSPEEDR |= ((_HS << (TX_Pin_Pos * 2U)) | (_HS << (RX_Pin_Pos * 2U)));
  USART_Port->AFR[1]  |= ((1 << ((TX_Pin_Pos - 8) * 4U)) | (1 << ((RX_Pin_Pos - 8) * 4U)));

  NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 15, 0));
  NVIC_EnableIRQ(USART1_IRQn);
  
  /* Transmit enable */
  SET_BIT(USART1->CR1, USART_CR1_TE);
  /* Receive enable */
  SET_BIT(USART1->CR1, USART_CR1_RE);
  /* Set Baudrate */
  USART1->BRR = ((SystemCoreClock + (baudRate / 2)) / baudRate);
  /* Enable USART1 */
  SET_BIT(USART1->CR1, USART_CR1_UE);
  /* Enable RXNE Interrupt */
  //SET_BIT(USART1->CR1, USART_CR1_RXNEIE);
}