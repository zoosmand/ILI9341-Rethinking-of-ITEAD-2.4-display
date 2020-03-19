#ifndef __ILI9325_H
#define __ILI9325_H

#ifdef __cplusplus
  extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Private typedef -----------------------------------------------------------*/
#define BL_Pos      GPIO_PIN_8_Pos
#define RST_Pos     GPIO_PIN_7_Pos
#define CS_Pos      GPIO_PIN_6_Pos
#define RS_Pos      GPIO_PIN_15_Pos
#define RD_Pos      GPIO_PIN_11_Pos
#define WR_Pos      GPIO_PIN_12_Pos

#define BL_H        PIN_H(GPIOA, GPIO_PIN_8)
#define BL_L        PIN_L(GPIOA, GPIO_PIN_8)
#define RST_H       PIN_H(GPIOF, GPIO_PIN_7)
#define RST_L       PIN_L(GPIOF, GPIO_PIN_7)
#define CS_H        PIN_H(GPIOF, GPIO_PIN_6)
#define CS_L        PIN_L(GPIOF, GPIO_PIN_6)
#define RS_H        PIN_H(GPIOA, GPIO_PIN_15)
#define RS_L        PIN_L(GPIOA, GPIO_PIN_15)
#define RD_H        PIN_H(GPIOA, GPIO_PIN_11)
#define RD_L        PIN_L(GPIOA, GPIO_PIN_11)
#define WR_H        PIN_H(GPIOA, GPIO_PIN_12)
#define WR_L        PIN_L(GPIOA, GPIO_PIN_12)

/* Private defines -----------------------------------------------------------*/
// -------- Portrait ---------
//#define ILI9341_HEIGHT              320
//#define ILI9341_WIDTH               240
// -------- Landscape --------
#define ILI9341_HEIGHT              240
#define ILI9341_WIDTH               320

#define ILI9341_SOFTRESET           0x01
#define ILI9341_SLEEPIN             0x10
#define ILI9341_SLEEPOUT            0x11
#define ILI9341_NORMALDISP          0x13
#define ILI9341_INVERTOFF           0x20
#define ILI9341_INVERTON            0x21
#define ILI9341_GAMMASET            0x26
#define ILI9341_DISPLAYOFF          0x28
#define ILI9341_DISPLAYON           0x29
#define ILI9341_CASET               0x2a
#define ILI9341_PASET               0x2b
#define ILI9341_RAMWR               0x2c
#define ILI9341_RAMRD               0x2e
#define ILI9341_MEMCONTROL          0x36
#define ILI9341_PIXELFORMAT         0x3a
#define ILI9341_RGBSIGNAL           0xb0
#define ILI9341_FRAMECONTROL        0xb1
#define ILI9341_INVERSIONCONRTOL    0xb4
#define ILI9341_DISPLAYFUNC         0xb6
#define ILI9341_ENTRYMODE           0xb7
#define ILI9341_POWERCONTROL1       0xc0
#define ILI9341_POWERCONTROL2       0xc1
#define ILI9341_VCOMCONTROL1        0xc5
#define ILI9341_VCOMCONTROL2        0xc7
#define ILI9341_POWERCONTROLB       0xcf
#define ILI9341_POWERCONTROLA       0xcb
#define ILI9341_READID              0xd3
#define ILI9341_POSGAMMACORR        0xe0
#define ILI9341_NEGGAMMACORR        0xe1
#define ILI9341_DRIVERTIMINGA       0xe8
#define ILI9341_DRIVERTIMINGB       0xea
#define ILI9341_POWERONSEQ          0xed
#define ILI9341_ENABLE3G            0xf2
#define ILI9341_INTERFACECONTROL    0xf6
#define ILI9341_PUMPRATIOCONTROL    0xf7

// MADCTL Control Bit Definition
#define ILI9341_MADCTL_MY           0x80
#define ILI9341_MADCTL_MX           0x40
#define ILI9341_MADCTL_MV           0x20
#define ILI9341_MADCTL_ML           0x10
#define ILI9341_MADCTL_BGR          0x08
#define ILI9341_MADCTL_MH           0x04

/* Exported macro ------------------------------------------------------------*/
#define ILI9341_WriteCmd(cmd) do { \
  RS_L; \
  GPIOB->ODR = (uint16_t)(cmd); \
  WR_L; \
  WR_H; \
  RS_H; \
} while (0);

#define ILI9341_WriteData8(data) do { \
  GPIOB->ODR = (uint16_t)(data); \
  WR_L; \
  WR_H; \
} while (0);

#define ILI9341_WriteData(data) do { \
  ILI9341_WriteData8(((data) >> 8) & 0xff); \
  ILI9341_WriteData8((data) & 0xff); \
} while (0);

#define ILI9341_SetColor(color)     (GPIOB->ODR = (color))

/* Exported functions prototypes ---------------------------------------------*/
void ILI9341_Init(void);
uint16_t ILI9341_ReadData();


#ifdef __cplusplus
}
#endif

#endif /* __ILI9325_H */
