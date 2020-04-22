#ifndef _W25QXX_H
#define _W25QXX_H

#include "main.h"

#ifdef __cplusplus
 extern "C" {
#endif

#define WriteEnable             0x06
#define WriteDisable            0x04
#define Read_JedecID            0x9f
#define Read_UniqueID           0x4b
#define Read_DeviceID           0xab
#define ReleasePowerDown        0xab
#define Read_StatusRegister_1   0x05
#define Read_StatusRegister_2   0x35
#define Read_StatusRegister_3   0x15
#define Write_StatusNVRegEnable 0x50
#define Write_StatusRegister    0x01
#define Write_StatusRegister_1  0x01
#define Write_StatusRegister_2  0x31
#define Write_StatusRegister_3  0x11
#define PageProgram             0x02
#define ReadData                0x03
#define FastRead                0x0b
#define Erase_Chip              0xc7
#define Erase_Block_64          0xd8
#define Erase_Block_32          0x52
#define Erase_Sector            0x20
#define Erase_Suspend           0x75
#define Erase_Resume            0x7h
#define PowerDown               0xb9
#define PowerDown_Release       0xab
#define EnableReset             0x66
#define ResetProccess           0x99

#define _BUSY_                  0x01 // Erase or write in progress
#define _WEL_                   0x02 // Write enable Latch
#define _BP0_                   0x04 // Block protect bit 0 (non-volatile)
#define _BP1_                   0x08 // Block protect bit 1 (non-volatile)
#define _BP2_                   0x10 // Block protect bit 2 (non-volatile)
#define _TB_                    0x20 // Top/Bottom write protect (non-volatile)
#define _SEC_                   0x40 // Sector protect (non-volatile)
#define _SRP0_                  0x80 // Status register protect bit 0 (non-volatile)

#define _SRP1_                  0x01 // Status register protect bit 1 (non-volatile)
#define _SREQ_                  0x02 // Quad enable

#define PAGE_SIZE               (uint16_t)0x0100 // 256
#define SECTOR_SIZE             (uint16_t)0x1000 // 4096
#define BLOCK_32K_SIZE          (uint16_t)0x8000 // 32768
#define BLOCK_SIZE              (uint32_t)0x00010000 // 64536


  typedef struct {
    uint8_t   ID;
    uint8_t   ManID;
    uint8_t   Type;
    uint64_t  UniqID;
    uint16_t  BlockCount;
    uint32_t  Capacity;
    uint8_t   Lock;	
  } w25qxx_t;

// Address Pattern
// 0x00BBBBSP
// bits 3..0 - number of a page - P
// bits 7..4 - number of a sector - S
// bits 23..8 - number of a block - B

extern w25qxx_t	w25qxx;




uint8_t W25qxx_Init(void);
void W25qxx_Read(uint32_t addr, uint16_t cnt, uint8_t *buf);
void W25qxx_Write(uint32_t addr, uint16_t cnt, uint8_t *buf);
void W25qxx_Erase(uint32_t addr, uint16_t sectors);
void W25qxx_IsBusy(void);
void W25qxx_Reset(void);
uint8_t W25qxx_WriteStatusRegister(uint8_t type, uint8_t status);

#ifdef __cplusplus
}
#endif
#endif /* _W25QXX_H */

