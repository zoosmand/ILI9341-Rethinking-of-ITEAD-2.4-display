/**
  ******************************************************************************
  * File Name          : display.c
  * Description        : This file provides code for ili9341 TFT display
  ******************************************************************************
  * @attention
  *
  *
  ******************************************************************************
  */
/* Includes ------------------------------------------------------------------*/
#include "display.h"


/* Private variables ---------------------------------------------------------*/
#ifdef FONTS_EEPROM
static Font_TypeDef font_dot15x21 = {
  .width    = 18,
  .height   = 24,
  .color    = RGB565_White,
  .bgcolor  = RGB565_Darkgreen,
  .use_bg   = 1,
  .address  = 0x00001000
};

static Font_TypeDef font_dot20x28 = {
  .width    = 24,
  .height   = 32,
  .color    = RGB565_White,
  .bgcolor  = RGB565_Darkgreen,
  .use_bg   = 1,
  .address  = 0x00003000
};
#endif

#ifdef FONTS_RAM
static Font_TypeDef font_dot15x21 = {
  .width    = 18,
  .height   = 24,
  .color    = RGB565_White,
  .bgcolor  = RGB565_Darkgreen,
  .use_bg   = 1,
  .font     = (uint8_t*)font_15x21
};

static Font_TypeDef font_dot20x28 = {
  .width    = 24,
  .height   = 32,
  .color    = RGB565_White,
  .bgcolor  = RGB565_Darkgreen,
  .use_bg   = 1,
  .font =   (uint8_t*)font_20x28
};
#endif

static uint16_t xStart = 0;
static uint16_t yStart = 0;

/* Private function prototypes -----------------------------------------------*/
#ifdef FONTS_EEPROM
static void BeginCollectSymbol(uint32_t addr);
static void EndCollectSymbol(void);
#endif









////////////////////////////////////////////////////////////////////////////////
/**
  * @brief  Simple demonstration 
  * @param  none 
  * @retval none
  */
void Display_Handler(void) {
  if (eepromReady) {
    DrawVLine(60, 20, 50, RGB565_White);
    DrawHLine(30, 120, 180, RGB565_Yellow);

    xStart = 20;
    yStart = 160;
    PrintString(&xStart, &yStart, &font_dot20x28, "Hello!!!", 0);

    xStart = 20;
    yStart = 90;
    char secs[20];
    sprintf(secs, "%ld", sysQuantum); 
    PrintString(&xStart, &yStart, &font_dot15x21, secs, 0);
  }
}




/**
  * @brief  Sets rectangle coordinates into display memory
  * @param  x0: begin x coordinate
  * @param  y0: begin y coordinate
  * @param  x1: end x coordinate
  * @param  y1: end y coordinate
  * @retval none
  */
void SetRectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1) {
  ILI9341_WriteCmd(ILI9341_CASET);
  ILI9341_WriteData(y0);
  ILI9341_WriteData(y1);
  
  ILI9341_WriteCmd(ILI9341_PASET);
  ILI9341_WriteData(x0);
  ILI9341_WriteData(x1);

  ILI9341_WriteCmd(ILI9341_RAMWR);
}






/**
  * @brief  Fills rectangle with color
  * @param  x0: begin x coordinate
  * @param  y0: begin y coordinate
  * @param  x1: end x coordinate
  * @param  y1: end y coordinate
  * @param  color: color
  * @retval none
  */
void FillRectangle(uint16_t x, uint16_t y, uint16_t w, uint16_t h, uint16_t color) {
  if ((x >= ILI9341_WIDTH) || (y >= ILI9341_HEIGHT) || (w == 0) || (h == 0)) return;
  if ((x + w - 1) >= ILI9341_WIDTH)  w = ILI9341_WIDTH  - x;
  if ((y + h - 1) >= ILI9341_HEIGHT) h = ILI9341_HEIGHT - y;
  
  CS_L;
  
  SetRectangle(x, y, (x + w - 1), (y + h -1));
  ILI9341_SetColor(color);
  
  uint16_t ww = 0;
  while (h--) {
    ww = w;
    while (ww--) {
      WR_L;
      WR_H;
    }
  }

  CS_H;
}







/**
  * @brief  Draws colored vertical line
  * @param  x: begin x coordinate
  * @param  y: begin y coordinate
  * @param  h: height of a line
  * @param  color: color
  * @retval none
  */
void DrawVLine(uint16_t x, uint16_t y, uint16_t h, uint16_t color) {
  if ((x >= ILI9341_HEIGHT) || (y >= ILI9341_WIDTH)) return;
  if ((y + h - 1) >= ILI9341_HEIGHT)  h = ILI9341_HEIGHT - y;

  CS_L;
  
  ILI9341_WriteCmd(ILI9341_CASET);
  ILI9341_WriteData(y);
  ILI9341_WriteData(y + h - 1);

  ILI9341_WriteCmd(ILI9341_PASET);
  ILI9341_WriteData(x);
  ILI9341_WriteData(x);
  
  ILI9341_WriteCmd(ILI9341_RAMWR);
  ILI9341_SetColor(color);
  
  while (h--) {
    WR_L;
    WR_H;
  }

  CS_H;
}







/**
  * @brief  Draws colored horizontal line
  * @param  x: begin x coordinate
  * @param  y: begin y coordinate
  * @param  h: width of a line
  * @param  color: color
  * @retval none
  */
void DrawHLine(uint16_t x, uint16_t y, uint16_t w, uint16_t color) {
  if ((x >= ILI9341_HEIGHT) || (y >= ILI9341_WIDTH)) return;
  if ((x + w - 1) >= ILI9341_WIDTH)  w = ILI9341_WIDTH - x;

  CS_L;

  ILI9341_WriteCmd(ILI9341_CASET);
  ILI9341_WriteData(y);
  ILI9341_WriteData(y);

  ILI9341_WriteCmd(ILI9341_PASET);
  ILI9341_WriteData(x);
  ILI9341_WriteData(x + w - 1);
  
  ILI9341_WriteCmd(ILI9341_RAMWR);
  ILI9341_SetColor(color);
  
  while (w--) {
    WR_L;
    WR_H;
  }

  CS_H;
}






#ifdef FONTS_EEPROM
/**
  * @brief  Draws symbol
  * @param  x: pointer of begin x coordinate
  * @param  y: pointer of begin y coordinate
  * @param  font: pointer of a Font_TypeDef struct
  * @param  pos: position of a symbol in symbol's array
  * @retval none
  */
void DrawSymbol(uint16_t *x, uint16_t *y, const Font_TypeDef *font, uint8_t pos) {
  if ((pos > 126) || (pos < 32)) {
    if (pos == 176) pos = 95;
    else return;
  } else {
    pos -= 32;
  }   

  int16_t w = font->width;
  int16_t h = font->height;
  if ((*x >= ILI9341_WIDTH) || (*y >= ILI9341_HEIGHT) || (w == 0) || (h == 0)) return;
  if ((*x + w - 1) >= ILI9341_WIDTH)  w = ILI9341_WIDTH  - *x;
  if ((*y + h - 1) >= ILI9341_HEIGHT) h = ILI9341_HEIGHT - *y;

  uint8_t smb = 0;
  uint8_t z = 0;
  uint8_t hh = 0;

  BeginCollectSymbol(font->address + (pos * font->width * (font->height / 8)));  
  
  CS_L;

  SetRectangle(*x, *y, (*x + w - 1), (*y + h -1));
  *x += w;
  
  while (w--) {
    z = font->height / 8;
    while (z--) {

      *(__IO uint8_t*)&SPI1->DR = 0;
      while (!(READ_BIT(SPI1->SR, SPI_SR_TXE)));
      while (!(READ_BIT(SPI1->SR, SPI_SR_RXNE)));
      smb = (uint8_t)SPI1->DR;

      hh = 8;
      while (hh--) {
        if (smb & 0x01) {
          ILI9341_SetColor(font->color);
        } else {
          if (font->use_bg) {
            ILI9341_SetColor(font->bgcolor);
          } else {
            // ToDo; to read the pixel and write it down again
          }
        }
        WR_L;
        WR_H;
        smb >>= 1;
      }
    }
  }

  CS_H;
  EndCollectSymbol();
}
#endif





#ifdef FONTS_RAM
/**
  * @brief  Draws symbol
  * @param  x: pointer of begin x coordinate
  * @param  y: pointer of begin y coordinate
  * @param  font: pointer of a Font_TypeDef struct
  * @param  pos: position of a symbol in symbol's array
  * @retval none
  */
void DrawSymbol(uint16_t *x, uint16_t *y, const Font_TypeDef *font, uint8_t pos) {
  if ((pos > 126) || (pos < 32)) {
    if (pos == 176) pos = 95;
    else return;
  } else {
    pos -= 32;
  }   

  int16_t w = font->width;
  int16_t h = font->height;
  if ((*x >= ILI9341_WIDTH) || (*y >= ILI9341_HEIGHT) || (w == 0) || (h == 0)) return;
  if ((*x + w - 1) >= ILI9341_WIDTH)  w = ILI9341_WIDTH  - *x;
  if ((*y + h - 1) >= ILI9341_HEIGHT) h = ILI9341_HEIGHT - *y;

  uint8_t smb = 0;
  uint8_t z = 0;
  uint8_t hh = 0;
  uint8_t *symbols = font->font;
  
  CS_L;

  SetRectangle(*x, *y, (*x + w - 1), (*y + h -1));
  *x += w;
  

  while (w--) {
    z = font->height / 8;
    while (z--) {
      smb = symbols[(pos * font->width * (font->height / 8))];
      symbols++;
      
      hh = 8;
      while (hh--) {
        if (smb & 0x01) {
          ILI9341_SetColor(font->color);
        } else {
          if (font->use_bg) {
            ILI9341_SetColor(font->bgcolor);
          } else {
            // ToDo; to read the pixel and write it down again
          }
        }
        WR_L;
        WR_H;
        smb >>= 1;
      }
    }
  }

  CS_H;
}
#endif







/**
  * @brief  Print a string on a layer of display
  * @param  layer: number of layer
  * @param  x: pointer to x coordinate
  * @param  y: pointer to y coordinate 
  * @param  font: pointer to font structure containes font paramenters:
  *               - width of a symbol
  *               - height of a symbol
  *               - color of a symbol
  *               - background color behind a symbol
  *               - flag - use or not use background color
  *               - array of symbols or address of EEPROM storage
  * @param  buf: pointer to buffer with a string
  * @param  wrap: wrap or not wrap to the next line 
  * @retval None
  */
void PrintString(uint16_t *x, uint16_t *y, const Font_TypeDef *font, const char *buf, uint8_t wrap) {
  while (*buf) {
    if (*x > ILI9341_WIDTH - 20) {
      if (wrap) {
        *x = 20;
        *y -= font->height;
      } else {
        return;
      }
    }
    DrawSymbol(x, y, font, *buf);
    buf++;
  }
}




#ifdef FONTS_EEPROM
/**
  * @brief  Begins SPI transaction, sends an address into EEPROM
  *         and necessary movements
  * @param  addr: EEPROM address
  * @retval none
  */
static void BeginCollectSymbol(uint32_t addr) {
  W25qxx_IsBusy();
  NSS_0_L;

  /* Send command and skip dummy byte */
  *(__IO uint8_t*)&SPI1->DR = FastRead;
  while (!(READ_BIT(SPI1->SR, SPI_SR_TXE)));
  while (!(READ_BIT(SPI1->SR, SPI_SR_RXNE)));
  SPI1->DR;

  int i = 4;
  while (--i) {
    *(__IO uint8_t*)&SPI1->DR = ((addr >> (8 * (i - 1))) & 0xff);
    while (!(READ_BIT(SPI1->SR, SPI_SR_TXE)));
    while (!(READ_BIT(SPI1->SR, SPI_SR_RXNE)));
    SPI1->DR;
  }
  
  /* FastRead requires to send another dummy byte */
  *(__IO uint8_t*)&SPI1->DR = 0;
  while (!(READ_BIT(SPI1->SR, SPI_SR_TXE)));
  while (!(READ_BIT(SPI1->SR, SPI_SR_RXNE)));
  SPI1->DR;

}




/**
  * @brief  Ends SPI transaction
  * @param  none
  * @retval none
  */
static void EndCollectSymbol(void) {
  NSS_0_H;
}
#endif