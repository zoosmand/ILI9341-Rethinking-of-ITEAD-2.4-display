/**
  ******************************************************************************
  * @file           : common.h
  * @brief          : Header for common.c file.
  *                   This file contains the common defines of the application.
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */
 
/* Define to prevent recursive inclusion -------------------------------------*/
#ifndef __COMMON_H
#define __COMMON_H

#ifdef __cplusplus
  extern "C" {
#endif 

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Exported types ------------------------------------------------------------*/
    
/* Private typedef -----------------------------------------------------------*/
struct __FILE {
  int handle;
  /* Whatever you require here. If the only file you are using is */
  /* standard output using printf() for debugging, no file handling */
  /* is required. */
};


/* Private defines -----------------------------------------------------------*/
#define NVIC_PRIORITYGROUP_0        ((uint32_t)0x00000007) /*!< 0 bit  for pre-emption priority, 4 bits for subpriority */
#define NVIC_PRIORITYGROUP_1        ((uint32_t)0x00000006) /*!< 1 bit  for pre-emption priority, 3 bits for subpriority */
#define NVIC_PRIORITYGROUP_2        ((uint32_t)0x00000005) /*!< 2 bits for pre-emption priority, 2 bits for subpriority */
#define NVIC_PRIORITYGROUP_3        ((uint32_t)0x00000004) /*!< 3 bits for pre-emption priority, 1 bit  for subpriority */
#define NVIC_PRIORITYGROUP_4        ((uint32_t)0x00000003) /*!< 4 bits for pre-emption priority, 0 bit  for subpriority */

#define GPIO_PIN_0                  GPIO_BSRR_BS_0 /*!< Select pin 0 */
#define GPIO_PIN_0_Pos              0
#define GPIO_PIN_1                  GPIO_BSRR_BS_1 /*!< Select pin 1 */
#define GPIO_PIN_1_Pos              1
#define GPIO_PIN_2                  GPIO_BSRR_BS_2 /*!< Select pin 2 */
#define GPIO_PIN_2_Pos              2
#define GPIO_PIN_3                  GPIO_BSRR_BS_3 /*!< Select pin 3 */
#define GPIO_PIN_3_Pos              3
#define GPIO_PIN_4                  GPIO_BSRR_BS_4 /*!< Select pin 4 */
#define GPIO_PIN_4_Pos              4
#define GPIO_PIN_5                  GPIO_BSRR_BS_5 /*!< Select pin 5 */
#define GPIO_PIN_5_Pos              5
#define GPIO_PIN_6                  GPIO_BSRR_BS_6 /*!< Select pin 6 */
#define GPIO_PIN_6_Pos              6
#define GPIO_PIN_7                  GPIO_BSRR_BS_7 /*!< Select pin 7 */
#define GPIO_PIN_7_Pos              7
#define GPIO_PIN_8                  GPIO_BSRR_BS_8 /*!< Select pin 8 */
#define GPIO_PIN_8_Pos              8
#define GPIO_PIN_9                  GPIO_BSRR_BS_9 /*!< Select pin 9 */
#define GPIO_PIN_9_Pos              9
#define GPIO_PIN_10                 GPIO_BSRR_BS_10 /*!< Select pin 10 */
#define GPIO_PIN_10_Pos             10
#define GPIO_PIN_11                 GPIO_BSRR_BS_11 /*!< Select pin 11 */
#define GPIO_PIN_11_Pos             11
#define GPIO_PIN_12                 GPIO_BSRR_BS_12 /*!< Select pin 12 */
#define GPIO_PIN_12_Pos             12
#define GPIO_PIN_13                 GPIO_BSRR_BS_13 /*!< Select pin 13 */
#define GPIO_PIN_13_Pos             13
#define GPIO_PIN_14                 GPIO_BSRR_BS_14 /*!< Select pin 14 */
#define GPIO_PIN_14_Pos             14
#define GPIO_PIN_15                 GPIO_BSRR_BS_15 /*!< Select pin 15 */
#define GPIO_PIN_15_Pos             15
#define GPIO_PIN_ALL                (uint16_t)0xffff /*!< Select all pins */

#define _IN                         0b00  // Input mode
#define _OUT                        0b01  // General purpose output mode
#define _AF                         0b10  // Alternate mode
#define _AN                         0b10  // Analog mode
#define _PP                         0b0   // Push-pull output
#define _OD                         0b1   // Open-drain output
#define _PD                         0b10  // Push-Down
#define _PU                         0b01  // Push-Up
#define _LS                         0b00  // Low speed
#define _MS                         0b01  // Medium speed
#define _HS                         0b11  // High speed

#define IWDG_KEY_RELOAD             0x0000aaaa               /*!< IWDG Reload Counter Enable   */
#define IWDG_KEY_ENABLE             0x0000cccc               /*!< IWDG Peripheral Enable       */
#define IWDG_KEY_WR_ACCESS_ENABLE   0x00005555               /*!< IWDG KR Write Access Enable  */


/* Exported macro ------------------------------------------------------------*/
#define FLAG_SET(registry, flag)        SET_BIT(registry, (1 << flag))
#define FLAG_CLR(registry, flag)        CLEAR_BIT(registry, (1 << flag))
#define FLAG_CHECK(registry, flag)      (READ_BIT(registry, (1 << flag)))

#define PIN_H(port, pin)                SET_BIT(port->BSRR, pin)
#define PIN_L(port, pin)                SET_BIT(port->BRR, pin)
#define PIN_LEVEL(port, pin)            (READ_BIT(port->IDR, pin))

#define PREG_SET(registry, key)         SET_BIT(registry, (1 << key))
#define PREG_CLR(registry, key)         CLEAR_BIT(registry, (1 << key))
#define PREG_CHECK(registry, key)       (READ_BIT(registry, (1 << key)))

#define BIT_2_0(per)        (per * 2U)
#define BIT_2_1(per)        (per * 2U + 1U)
#define BIT_4_0(per)        (per * 4U)
#define BIT_4_1(per)        (per * 4U + 1U)
#define BIT_4_2(per)        (per * 4U + 2U)
#define BIT_4_3(per)        (per * 4U + 3U)


/* Exported functions prototypes ---------------------------------------------*/
void Error_Handler(void);
void LED_Blink(GPIO_TypeDef* port, uint16_t pinSource);



#ifdef __cplusplus
}
#endif

#endif /* __COMMON_H */