/**
  ******************************************************************************
  * File Name          : TIM.h
  * Description        : This file provides code for the configuration
  *                      of the TIM instances.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

#ifndef __tim_H
#define __tim_H
#ifdef __cplusplus
 extern "C" {
#endif

/* Includes ------------------------------------------------------------------*/
#include "main.h"


/* Exported functions prototypes ---------------------------------------------*/
void TIM6_Init(void);
void BasicTimer_Handler(TIM_TypeDef *tim);


#ifdef __cplusplus
}
#endif
#endif /*__ tim_H */

