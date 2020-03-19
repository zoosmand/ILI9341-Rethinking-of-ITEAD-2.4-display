/* Includes ------------------------------------------------------------------*/
#include "ili9341.h"


/* Private variables ---------------------------------------------------------*/

/* Private function prototypes -----------------------------------------------*/









////////////////////////////////////////////////////////////////////////////////

void ILI9341_Init(void) {

  /* Enable GPIO Oupput on hight speed */
  // RS, RD, WR, Backlight
  GPIOA->MODER |= (
      (_PU << (BL_Pos * 2U))
    | (_PU << (RS_Pos * 2U))
    | (_PU << (RD_Pos * 2U))
    | (_PU << (WR_Pos * 2U))
  );
  GPIOA->OSPEEDR |= (
      (_PU << (BL_Pos * 2U))
    | (_HS << (RS_Pos * 2U))
    | (_HS << (RD_Pos * 2U))
    | (_HS << (WR_Pos * 2U))
  );

  // CS, Reset
  GPIOF->MODER |= (
      (_PU << (RST_Pos * 2U))
    | (_PU << (CS_Pos * 2U))
  );
  GPIOF->OSPEEDR |= (
      (_PU << (RST_Pos * 2U))
    | (_HS << (CS_Pos * 2U))
  );

  // 16-bit data bus
  GPIOB->MODER = 0x55555555;
  GPIOB->OSPEEDR = 0xffffffff;

  Delay(50);

  /* Initialization starts from here */
  RST_H;
  CS_H;
  RS_H;
  WR_H;
  RD_H;

  Delay(50);

  RST_L;
  Delay(5);
  RST_H;
  Delay(5);

  CS_L;

  uint16_t ILI1394_Id = 0;
  ILI9341_WriteCmd(ILI9341_READID); // 0xd3

  ILI9341_ReadData();
  if (!ILI9341_ReadData()) {
    ILI1394_Id = (ILI9341_ReadData() << 8) & 0xff00;
    ILI1394_Id |= ILI9341_ReadData() & 0x00ff;
  }
  if (ILI1394_Id != 0x9341) return;


  ILI9341_WriteCmd(ILI9341_SOFTRESET); // 0x01
  Delay(5);

  ILI9341_WriteCmd(ILI9341_DISPLAYOFF); // 0x28
  Delay(5);
 
  // ----------------- Power ------------------
  ILI9341_WriteCmd(ILI9341_POWERCONTROL1); // 0xc0
  ILI9341_WriteData8(0x26);
  ILI9341_WriteCmd(ILI9341_POWERCONTROL2); // 0xc1
  ILI9341_WriteData8(0x11);
  ILI9341_WriteCmd(ILI9341_VCOMCONTROL1); // 0xc5
  ILI9341_WriteData8(0x5c);
  ILI9341_WriteData8(0x4c);
  ILI9341_WriteCmd(ILI9341_VCOMCONTROL2); // 0xc7
  ILI9341_WriteData8(0x0094);
  
  // ---------------- Memory ------------------
  ILI9341_WriteCmd(ILI9341_MEMCONTROL); // 0x36
  // -------- Portrait ---------
  //ILI9341_WriteData8(ILI9341_MADCTL_BGR | ILI9341_MADCTL_MV | ILI9341_MADCTL_MX | ILI9341_MADCTL_MY);
  // -------- Landscape --------
  ILI9341_WriteData8(ILI9341_MADCTL_BGR | ILI9341_MADCTL_MY);
  
  ILI9341_WriteCmd(ILI9341_PIXELFORMAT); // 0x3a
  ILI9341_WriteData8(0x55);

  
  // // -------------- Frame rate ---------------
  ILI9341_WriteCmd(ILI9341_FRAMECONTROL); // 0xb1
  ILI9341_WriteData8(0x00);
  ILI9341_WriteData8(0x1b);
  
  // ---------------- Gamma ------------------
  ILI9341_WriteCmd(ILI9341_GAMMASET); // 0x26
  ILI9341_WriteData8(0x01);
  // ILI9341_WriteCmd(ILI9341_POSGAMMACORR); // 0xe0
  // ILI9341_WriteData(0x001f);
  // ILI9341_WriteData(0x001a);
  // ILI9341_WriteData(0x0018);
  // ILI9341_WriteData(0x000a);
  // ILI9341_WriteData(0x000f);
  // ILI9341_WriteData(0x0006);
  // ILI9341_WriteData(0x0045);
  // ILI9341_WriteData(0x0087);
  // ILI9341_WriteData(0x0032);
  // ILI9341_WriteData(0x000a);
  // ILI9341_WriteData(0x0007);
  // ILI9341_WriteData(0x0002);
  // ILI9341_WriteData(0x0007);
  // ILI9341_WriteData(0x0005);
  // ILI9341_WriteData(0x0000);
  // ILI9341_WriteCmd(ILI9341_NEGGAMMACORR); // 0xe1
  // ILI9341_WriteData(0x0000);
  // ILI9341_WriteData(0x0025);
  // ILI9341_WriteData(0x0027);
  // ILI9341_WriteData(0x0005);
  // ILI9341_WriteData(0x0010);
  // ILI9341_WriteData(0x0009);
  // ILI9341_WriteData(0x003a);
  // ILI9341_WriteData(0x0078);
  // ILI9341_WriteData(0x004d);
  // ILI9341_WriteData(0x0005);
  // ILI9341_WriteData(0x0018);
  // ILI9341_WriteData(0x000d);
  // ILI9341_WriteData(0x0038);
  // ILI9341_WriteData(0x003a);
  // ILI9341_WriteData(0x001f);
  
  // // ---------------- DDRAM -------------------  
  // ILI9341_WriteCmd(ILI9341_CASET); // 0x2a
  // ILI9341_WriteData(0x0000);
  // ILI9341_WriteData(0x0000);
  // ILI9341_WriteData(0x0000);
  // ILI9341_WriteData(0x00ef);
  // ILI9341_WriteCmd(ILI9341_PASET); // 0x2b
  // ILI9341_WriteData(0x0000);
  // ILI9341_WriteData(0x0000);
  // ILI9341_WriteData(0x0001);
  // ILI9341_WriteData(0x003f);
  // ILI9341_WriteCmd(ILI9341_RAMWR); // 0x2c
  ILI9341_WriteCmd(ILI9341_ENTRYMODE); // 0xb7
  ILI9341_WriteData8(0x07);

  // --------------- Display -----------------
  ILI9341_WriteCmd(ILI9341_DISPLAYFUNC); // 0xb6
  ILI9341_WriteData8(0x0a);
  ILI9341_WriteData8(0x82);
  ILI9341_WriteData8(0x27);
  ILI9341_WriteData8(0x00);
  // ILI9341_WriteCmd(ILI9341_INVERTON);

  ILI9341_WriteCmd(ILI9341_ENABLE3G); // 0xf2
  ILI9341_WriteData8(0x03);
  
  ILI9341_WriteCmd(ILI9341_PUMPRATIOCONTROL); //0xf7
  ILI9341_WriteData8(0x20);

  ILI9341_WriteCmd(ILI9341_SLEEPOUT); // 0x11
  Delay(50);
  ILI9341_WriteCmd(ILI9341_DISPLAYON); // 0x29

  CS_H;

  FillRectangle(0, 0, ILI9341_WIDTH, ILI9341_HEIGHT, RGB565_Darkgreen);

  Delay(100);
  BL_H;
}











uint16_t ILI9341_ReadData(void) {
  uint16_t data = 0;
  GPIOB->ODR = 0UL;
  GPIOB->MODER = 0UL; // Input mode
  RD_L;
  __NOP();
  data = GPIOB->IDR;
  RD_H;
  GPIOB->MODER = 0x55555555; // Output mode
  return (data);
}


