#ifndef __DISPLAY_H
#define __DISPLAY_H

#ifdef __cplusplus
  extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "main.h"



/* Private typedef -----------------------------------------------------------*/
typedef enum {
  ILI1394   = 0,
  ILI9325   = 1 
} Display_TypeDef;

typedef struct {
  uint8_t     width;
  uint8_t     height;
  uint32_t    color;
  uint32_t    bgcolor;
  uint8_t     use_bg;
  uint8_t     *font;
} Font_TypeDef;

/* Private defines -----------------------------------------------------------*/

/* Exported functions prototypes ---------------------------------------------*/
void Display_Handler(Display_TypeDef device);
void SetRectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1);
void FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color);
void DrawVLine(uint16_t x, uint16_t y, uint16_t h, uint16_t color);
void DrawHLine(uint16_t x, uint16_t y, uint16_t w, uint16_t color);
void DrawSymbol(uint16_t *x, uint16_t *y, const Font_TypeDef *font, uint8_t pos);
void PrintString(uint16_t *x, uint16_t *y, const Font_TypeDef *font, const char *buf, uint8_t wrap);



#ifdef __cplusplus
}
#endif

#endif /* __DISPLAY_H */
