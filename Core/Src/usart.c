/**
  ******************************************************************************
  * File Name          : USART.c
  * Description        : This file provides code for the configuration
  *                      of the USART instances.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "usart.h"

/* Private variables ---------------------------------------------------------*/
static uint8_t rxBuffer[RXBUF_LEN];
static uint8_t rxBufPrtIn = 0;
static uint8_t rxBufPrtOut = 0;

/* Private function prototypes -----------------------------------------------*/









////////////////////////////////////////////////////////////////////////////////

/**
  * @brief  USART1 Initialization procedure.
  * @param  none
  * @retval none
  */
void USART1_Init(void) {
  uint32_t baudRate = 115200;

  /* Enable GPIO alternative #1 on hight speed */
  USART_Port->MODER   |= ((_AF << (TX_Pin_Pos * 2U)) | (_AF << (RX_Pin_Pos * 2U)));
  USART_Port->OSPEEDR |= ((_HS << (TX_Pin_Pos * 2U)) | (_HS << (RX_Pin_Pos * 2U)));
  USART_Port->AFR[1]  |= ((1 << ((TX_Pin_Pos - 8) * 4U)) | (1 << ((RX_Pin_Pos - 8) * 4U)));

  NVIC_SetPriority(USART1_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 15, 0));
  NVIC_EnableIRQ(USART1_IRQn);
  
  /* Transmit enable */
  /* Receive enable */
  /* Enable RXNE Interrupt */
  SET_BIT(USART1->CR1, (USART_CR1_TE | USART_CR1_RE | USART_CR1_RXNEIE));
  /* Set Baudrate */
  USART1->BRR = ((SystemCoreClock + (baudRate / 2)) / baudRate);
  /* Enable USART1 */
  SET_BIT(USART1->CR1, USART_CR1_UE);
}






/**
  * @brief  Writes RX data into the circular buffer.
  * @param  none
  * @retval none
  */
void USART1_RX_Handler(void) {
  rxBuffer[(rxBufPrtIn++)] = (uint8_t)USART1->RDR;;
  rxBufPrtIn &= RXBUF_MASK;
}





/**
  * @brief  Reads payload data into the circle buffer.
  * @param  buf: pointer to a buffer where dala to be placed.
  * @param  len: length of reading data. Lenght of readng data 
  *              could be more than recorded data in RX buf.
  *              In this case reading will be broken and payload
  *              length will be returned.  
  * @retval Payload length data from RX Buffer.
  */
uint8_t USART_RxBufferRead(uint8_t *buf, uint16_t len) {
  uint8_t payloadLen = 0;
  while (rxBufPrtOut != rxBufPrtIn) {
    buf[(payloadLen++)] = rxBuffer[(rxBufPrtOut++)];
    rxBufPrtOut &= RXBUF_MASK;
  }
  return (payloadLen);
}
