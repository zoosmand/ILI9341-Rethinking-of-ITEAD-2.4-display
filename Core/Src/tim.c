/**
  ******************************************************************************
  * File Name          : TIM.c
  * Description        : This file provides code for the configuration
  *                      of the TIM instances.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "tim.h"










////////////////////////////////////////////////////////////////////////////////

void TIM6_Init(void) {

  /* Set interrupt and its priority */
  NVIC_SetPriority(TIM6_IRQn, NVIC_EncodePriority(NVIC_GetPriorityGrouping(), 14, 0));
  NVIC_EnableIRQ(TIM6_IRQn);
  /* Set prescaler */
  TIM6->PSC = 4800U - 1U;
  /* Set autoreload value */
  TIM6->ARR = 10000U - 1U;
  /* Enable autoreload to be cached */
  SET_BIT(TIM6->CR1, TIM_CR1_ARPE);
  /* Clear update flag */
  CLEAR_BIT(TIM6->SR, TIM_SR_UIF);
  /* Enable update interrupt */
  SET_BIT(TIM6->DIER, TIM_DIER_UIE);
  /* Enable counter */
  SET_BIT(TIM6->CR1, TIM_CR1_CEN);
}



void BasicTimer_Handler(TIM_TypeDef *tim) {
  //
  if (tim == TIM6) {
    /* Set Run Display flag, i.e. Display_Handler() */
    FLAG_SET(_EREG_, _RDF_);

    // LED_Blink(GPIOA, GPIO_PIN_8);
  }
}
