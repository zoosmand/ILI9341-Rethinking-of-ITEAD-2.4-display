/**
  ******************************************************************************
  * File Name          : spi.c
  * Description        : This file provides code for the configuration
  *                      of the SPI instances.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "spi.h"









////////////////////////////////////////////////////////////////////////////////

/**
  * @brief  SPI1 Initialization procedure
  * @param  none
  * @retval none
  */
void SPI1_Init(void) {
  uint8_t pump = 0;

  /* Enable GPIO alternative on hight speed */
  SPI_Port->MODER   |= ((_AF << (SCK_Pin_Pos * 2U)) | (_AF << (MISO_Pin_Pos * 2U)) | (_AF << (MOSI_Pin_Pos * 2U)));
  SPI_Port->OSPEEDR |= ((_HS << (SCK_Pin_Pos * 2U)) | (_HS << (MISO_Pin_Pos * 2U)) | (_HS << (MOSI_Pin_Pos * 2U)));
  // SPI_Port->PUPDR   |= ((_PD << (MISO_Pin_Pos * 2U)) | (_PD << (MOSI_Pin_Pos * 2U)) | (_PD << (SCK_Pin_Pos * 2U)));

  /* Enable GPIO output for NSS on lowest speed */
  SPI_Port->MODER   |= (_OUT << (NSS_0_Pin_Pos * 2U));
  NSS_0_H;

  /* Set fractal part for 8-bit mode */
  /* Enable software output */
  /* Data size is automaticaly set by 8-bit bus */
  SET_BIT(SPI1->CR2, (SPI_CR2_FRXTH | SPI_CR2_SSOE));

  /* Set software NSS master */
  /* Set baud rate fPCLK/4, 12Mb/s */
  /* Enbale master SPI */
  /* Enbale SPI */
  SET_BIT(SPI1->CR1, (SPI_CR1_SSM | SPI_CR1_BR_0 | SPI_CR1_MSTR | SPI_CR1_SPE));


  /* Configure DMA, Channel2 - RX, Channel3 - TX */
  /* Set priority high*/
  /* Set memory to increment */
  DMA1_Channel2->CCR = (DMA_CCR_PL_1 | DMA_CCR_MINC);
  /* Set buffer size to 0 */
  DMA1_Channel2->CNDTR = 0U;
  /* Set peripheral address */
  DMA1_Channel2->CPAR = (uint32_t)&SPI1->DR;
  /* Set memory address */
  DMA1_Channel2->CMAR = (uint32_t)&pump;

  /* Set priority high*/
  /* Set memory to increment */
  /* Set direction from memory to peripheral */
  DMA1_Channel3->CCR = (DMA_CCR_PL_1 | DMA_CCR_MINC | DMA_CCR_DIR);
  /* Set buffer size to 0 */
  DMA1_Channel3->CNDTR = 0U;
  /* Set peripheral address */
  DMA1_Channel3->CPAR = (uint32_t)&SPI1->DR;
  /* Set memory address */
  DMA1_Channel3->CMAR = (uint32_t)&pump;
}






/**
  * @brief  SPI1 enabling procedure
  * @param  none
  * @retval none
  */
void SPI1_Enable() {
  SET_BIT(SPI1->CR1, SPI_CR1_SPE);
}





/**
  * @brief  SPI1 disabling procedure
  * @param  none
  * @retval none
  */
void SPI1_Disable() {
  while (READ_BIT(SPI1->SR, SPI_SR_FTLVL) == SPI_SR_FTLVL);
  while (READ_BIT(SPI1->SR, SPI_SR_BSY));
  CLEAR_BIT(SPI1->CR1, SPI_CR1_SPE);
  while (READ_BIT(SPI1->SR, SPI_SR_FTLVL) == SPI_SR_FTLVL);
}






/**
  * @brief  Reads data from SPI bus
  * @param  buf: pointer to buffer to read, the first item of buffer could contain
  *              a command data. Beginning iteration reads a dummy byte.
  *         cnt: count of bytes to read.
  * @retval none
  */
void SPI_Read(uint8_t *buf, uint8_t cnt) {
  // SPI1_Enable();
  NSS_0_L;
  while (PIN_LEVEL(SPI_Port, NSS_0_Pin));

  *(__IO uint8_t*)&SPI1->DR = buf[0];
  while (!(READ_BIT(SPI1->SR, SPI_SR_TXE)));
  while (!(READ_BIT(SPI1->SR, SPI_SR_RXNE)));
  SPI1->DR;

  while (cnt--) {
    *(__IO uint8_t*)&SPI1->DR = 0;
    while (!(READ_BIT(SPI1->SR, SPI_SR_TXE)));
    while (!(READ_BIT(SPI1->SR, SPI_SR_RXNE)));
    *buf++ = (uint8_t)SPI1->DR;
  }
    
  NSS_0_H;
  // SPI1_Disable();
}






/**
  * @brief  Writes data into SPI bus
  * @param  buf: pointer to buffer to write.
  *         cnt: count of bytes to write.
  * @retval none
  */
void SPI_Write(uint8_t *buf, uint8_t cnt) {
  // SPI1_Enable();
  NSS_0_L;
  while (PIN_LEVEL(SPI_Port, NSS_0_Pin));

  if (cnt) {
    while (cnt--) {
      *(__IO uint8_t*)&SPI1->DR = *buf++;
      while (!(READ_BIT(SPI1->SR, SPI_SR_TXE)));
      while (!(READ_BIT(SPI1->SR, SPI_SR_RXNE)));
      SPI1->DR;
    }
  }
    
  NSS_0_H;
  // SPI1_Disable();
}
