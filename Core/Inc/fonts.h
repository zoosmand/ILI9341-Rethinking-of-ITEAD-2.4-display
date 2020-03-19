/*
 * fonts.h
 *
 * Created: 14.12.2019 22:29:18
 *  Author: zoosman
 */ 


#ifndef FONTS_H_
#define FONTS_H_

#ifdef __cplusplus
extern "C" {
#endif

#include "main.h"

//////////////////////////////////////////////////////////////////////////
#define RGB565_Red                  (uint16_t)0xf800
#define RGB565_Green                (uint16_t)0x07e0
#define RGB565_Blue                 (uint16_t)0x001f
#define RGB565_Yellow               (uint16_t)0xffe0
#define RGB565_Black                (uint16_t)0x0000
#define RGB565_White                (uint16_t)0xffff
#define RGB565_Orange               (uint16_t)0xfbe0
#define RGB565_Lightblue            (uint16_t)0x07ff
#define RGB565_Lemon                (uint16_t)0xe7e7
#define RGB565_Apple                (uint16_t)0x0400
#define RGB565_Darkgreen            (uint16_t)0x0380

#define ARGB8888_Red                (uint32_t)0x00ff0000
#define ARGB8888_Green              (uint32_t)0x0000ff00
#define ARGB8888_Blue               (uint32_t)0x000000ff
#define ARGB8888_Yellow             (uint32_t)0x00ffff00
#define ARGB8888_Black              (uint32_t)0x00000000
#define ARGB8888_White              (uint32_t)0x00ffffff
#define ARGB8888_Orange             (uint32_t)0x00ff7f00
#define ARGB8888_Lemon              (uint32_t)0x007fff7f
#define ARGB8888_Lightblue          (uint32_t)0x0000cfff
#define ARGB8888_Apple              (uint32_t)0x0099ee2f
#define ARGB8888_Darkgreen          (uint32_t)0x00003f00



//////////////////////////////////////////////////////////////////////////
extern const uint8_t font_5x7[(96 * 6)];
extern const uint8_t font_10x14[(96 * 24)];
extern const uint8_t font_15x21[(96 * 54)];
extern const uint8_t font_20x28[(96 * 96)];



#ifdef __cplusplus
}
#endif

#endif /* FONTS_H_ */
