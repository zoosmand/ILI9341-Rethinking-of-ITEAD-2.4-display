/**
  ******************************************************************************
  * File Name          : spi.h
  * Description        : This file provides code for the configuration
  *                      of the SPI instances.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef __SPI_H
#define __SPI_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private defines -----------------------------------------------------------*/
#define NSS_0_Pin       GPIO_PIN_4
#define NSS_0_Pin_Pos   GPIO_PIN_4_Pos
#define SCK_Pin         GPIO_PIN_5
#define SCK_Pin_Pos     GPIO_PIN_5_Pos
#define MISO_Pin        GPIO_PIN_6
#define MISO_Pin_Pos    GPIO_PIN_6_Pos
#define MOSI_Pin        GPIO_PIN_7
#define MOSI_Pin_Pos    GPIO_PIN_7_Pos
#define SPI_Port        GPIOA

#define NSS_1_Pin       GPIO_PIN_13
#define NSS_1_Pin_Pos   GPIO_PIN_13_Pos
#define SPI_SD_Port     GPIOC

typedef enum {
  NEUTRAL   = 2,
  READ      = 1,
  WRITE     = 0
} Direction_TypeDef;



/* Exported macro ------------------------------------------------------------*/
#define NSS_0_H         PIN_H(SPI_Port, NSS_0_Pin)
#define NSS_0_L         PIN_L(SPI_Port, NSS_0_Pin)
#define NSS_1_H         PIN_H(SPI_SD_Port, NSS_1_Pin)
#define NSS_1_L         PIN_L(SPI_SD_Port, NSS_1_Pin)

/* Exported functions prototypes ---------------------------------------------*/
void SPI1_Init(void);
void SPI1_Enable();
void SPI1_Disable();
void SPI_Read(uint8_t *buf, uint8_t cnt);
void SPI_Write(uint8_t *buf, uint8_t cnt);


#ifdef __cplusplus
}
#endif
#endif /*__ SPI_H */

