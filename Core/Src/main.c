/**
  ******************************************************************************
  * @file           : main.c
  * @brief          : Main program body
  ******************************************************************************
  * @attention
  *
  ******************************************************************************
  */

/* Includes ------------------------------------------------------------------*/
#include "main.h"

/* Global variables ---------------------------------------------------------*/
uint32_t sysQuantum       = 0;
uint32_t millis           = 0;
uint32_t seconds          = 0;
uint32_t minutes          = 0;
uint32_t _EREG_           = 0;
uint32_t delay_tmp        = 0;
uint32_t check            = 0;
uint32_t SystemCoreClock  = 16000000;
uint8_t eepromReady = 0;

/* Private variables ---------------------------------------------------------*/
static uint32_t millis_tmp    = 100;
static uint32_t seconds_tmp   = 1000;
static uint32_t minutes_tmp   = 60;

/* Private function prototypes -----------------------------------------------*/
static void CronSysQuantum_Handler(void);
static void CronMillis_Handler(void);
static void CronSeconds_Handler(void);
static void CronMinutes_Handler(void);
static void Flags_Handler(void);

static void IWDG_Init(void);








////////////////////////////////////////////////////////////////////////////////

/**
  * @brief  The application entry point.
  * @retval int
  */
int main(void) {
  Delay(500);
  IWDG_Init();
  USART1_Init();
  TIM6_Init();
  ILI9341_Init();
  SPI1_Init();
  if (W25qxx_Init()) {
    eepromReady = 1;
  }

  while (1) {
    Delay_Handler(0);
    Cron_Handler();
    Flags_Handler();
  }
}






/********************************************************************************/
/*                                     CRON                                     */
/********************************************************************************/
void Cron_Handler() {
  $CronStart:
  if (SysTick->CTRL & (1 << SysTick_CTRL_COUNTFLAG_Pos)) { 
    sysQuantum++;
    CronSysQuantum_Handler();
  }

  if (sysQuantum >= millis_tmp) {
    millis++;
    millis_tmp = sysQuantum + 100;
    CronMillis_Handler();
  }
  
  if (millis >= seconds_tmp) {
    seconds++;
    seconds_tmp += 1000;
    CronSeconds_Handler();
  }
  
  if (seconds >= minutes_tmp) {
    minutes++;
    minutes_tmp += 60;
    CronMinutes_Handler();
  }

  while (sysQuantum < delay_tmp) {
    goto $CronStart;
  }
  // !!!!!!!!! The bug!!!!!!!!
  delay_tmp = 0;
  FLAG_CLR(_EREG_, _DELAYF_);
}






/********************************************************************************/
/*                             CRON EVENTS HANDLERS                             */
/********************************************************************************/
// ---- System Quantum ---- //
static void CronSysQuantum_Handler(void) {
  //
}

// ---- Milliseconds ---- //
static void CronMillis_Handler(void) {
  //
}

// ---- Seconds ---- //
static void CronSeconds_Handler(void) {
  /* Reload IWDG counter */
  IWDG->KR = IWDG_KEY_RELOAD;
  // /* Set Run Display flag, i.e. Display_Handler() */
  // FLAG_SET(_EREG_, _RDF_);
}

// ---- Minutes ---- //
static void CronMinutes_Handler(void) {
  //
  printf("A minute left.\n");
}






/********************************************************************************/
/*                                     FLAGS                                    */
/********************************************************************************/
void Flags_Handler(void){
  if (FLAG_CHECK(_EREG_, _BT6F_)) {
    BasicTimer_Handler(TIM6);
    FLAG_CLR(_EREG_, _BT6F_);
  }

  if (FLAG_CHECK(_EREG_, _U1RXF_)) {
    USART1_RX_Handler();
    FLAG_CLR(_EREG_, _U1RXF_);
  }

  if (FLAG_CHECK(_EREG_, _RDF_)) {
    Display_Handler();
    FLAG_CLR(_EREG_, _RDF_);
  }
}






/**
  * @brief  Setup the microcontroller system
  *         Initialize the Embedded Flash Interface, the PLL and update the 
  *         SystemCoreClock variable.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
void SystemInit (void) {
  #if (PREFETCH_ENABLE != 0)
    FLASH->ACR |= FLASH_ACR_PRFTBE;
  #else
    FLASH->ACR &= ~FLASH_ACR_PRFTBE;
  #endif /* PREFETCH_ENABLE */

  NVIC_SetPriorityGrouping(NVIC_PRIORITYGROUP_4);

  /* Setup and enable SysTick */
  SysTick->CTRL  = SysTick_CTRL_CLKSOURCE_Msk | SysTick_CTRL_TICKINT_Msk;
  SysTick->LOAD  = 480U - 1U;
  SysTick->VAL   = 0U;
  SysTick->CTRL |= SysTick_CTRL_ENABLE_Msk;

  /* Set SysTick interrupt */
  NVIC_SetPriority(SysTick_IRQn, 0);
  NVIC_EnableIRQ(SysTick_IRQn);

  /* Enable SysCfg, Debug Freezer and PWR  */
  SET_BIT(RCC->APB2ENR, (RCC_APB2ENR_SYSCFGEN | RCC_APB2ENR_DBGMCUEN));
  SET_BIT(RCC->APB1ENR, RCC_APB1ENR_PWREN);

  /* Set FLASH interrupt */
  NVIC_SetPriority(FLASH_IRQn, 0);
  NVIC_EnableIRQ(FLASH_IRQn);

  /* Set RCC interrupt */
  NVIC_SetPriority(RCC_IRQn, 0);
  NVIC_EnableIRQ(RCC_IRQn);

  /* Stop ticking peripheral while debugging */
  #if (DEBUG != 0)
    SET_BIT(DBGMCU->APB1FZ, (
        DBGMCU_APB1_FZ_DBG_TIM6_STOP
      | DBGMCU_APB1_FZ_DBG_IWDG_STOP
      | DBGMCU_APB1_FZ_DBG_WWDG_STOP
    ));
  #endif /* DEBUG */

  /* Set FLASH Latency and chack it */
  MODIFY_REG(FLASH->ACR, FLASH_ACR_LATENCY, FLASH_ACR_LATENCY);
  if (READ_BIT(FLASH->ACR, FLASH_ACR_LATENCY) != FLASH_ACR_LATENCY) {
    Error_Handler();
  }

  /* Enable HSI and wailt until it reaady*/
  SET_BIT(RCC->CR, RCC_CR_HSION);
  while(!(READ_BIT(RCC->CR, RCC_CR_HSIRDY) == (RCC_CR_HSIRDY)));

  /* Set HSI calibration trimming */
  MODIFY_REG(RCC->CR, RCC_CR_HSITRIM, 16 << RCC_CR_HSITRIM_Pos);

  /* Enable LSI and wailt until it reaady*/
  SET_BIT(RCC->CSR, RCC_CSR_LSION);
  while(!(READ_BIT(RCC->CSR, RCC_CSR_LSIRDY) == (RCC_CSR_LSIRDY)));

  /* Configure siurce domain */
  MODIFY_REG(RCC->CFGR, RCC_CFGR_PLLSRC | RCC_CFGR_PLLMUL, (RCC_CFGR_PLLSRC_HSI_DIV2 & RCC_CFGR_PLLSRC) | RCC_CFGR_PLLMUL12);
  MODIFY_REG(RCC->CFGR2, RCC_CFGR2_PREDIV, (RCC_CFGR_PLLSRC_HSI_DIV2 & RCC_CFGR2_PREDIV));
  
  
  /* Enable PLL and wailt until it reaady*/
  SET_BIT(RCC->CR, RCC_CR_PLLON);
  while(!(READ_BIT(RCC->CR, RCC_CR_PLLRDY) == (RCC_CR_PLLRDY)));

  /* AHB clock isn't divided */
  /* APB1 clock isn't divided */

  /* Set PLL as clock source and wailt until it reaady*/
  MODIFY_REG(RCC->CFGR, RCC_CFGR_SW, RCC_CFGR_SW_PLL);

   /* Wait till System clock is ready */
  while(READ_BIT(RCC->CFGR, RCC_CFGR_SWS) != RCC_CFGR_SWS_PLL);

  SystemCoreClock = 48000000;

  /* USART clock now is APH1 PCLK1 clock */





  /*----------------------------------------------------------------------------*/
  /*                          Set peripheral clocks                             */
  /*----------------------------------------------------------------------------*/
  /* AHB peripherals */
  SET_BIT(RCC->AHBENR, (
      RCC_AHBENR_GPIOAEN
    | RCC_AHBENR_GPIOBEN
    | RCC_AHBENR_GPIOFEN
    | RCC_AHBENR_DMAEN
  ));

  /* APB1 peripherals */
  SET_BIT(RCC->APB1ENR, (
    RCC_APB1ENR_TIM6EN
  ));

  /* APB2 peripherals */
  SET_BIT(RCC->APB2ENR, (
      RCC_APB2ENR_USART1EN
    | RCC_APB2ENR_SPI1EN
  ));
}




/**
  * @brief  Setup the Independent Watchdog.
  * @note   This function should be used only after reset.
  * @param  None
  * @retval None
  */
static void IWDG_Init(void) {
  // prescaler of 40KHz is 128 
  // counter 624 gives a threshold ~2s
  uint32_t counter = 625U - 1U;

  /* in case the reset bit in RCC_CSR is set, clear it */
  if (READ_BIT(RCC->CSR, RCC_CSR_IWDGRSTF)) {
    SET_BIT(RCC->CSR, RCC_CSR_RMVF);
  }

  /* Enable IWDG and set write access to the register */
  IWDG->KR = IWDG_KEY_ENABLE;
  IWDG->KR = IWDG_KEY_WR_ACCESS_ENABLE;

  /* Set prescaller and wait until it ready */
  IWDG->PR= (IWDG_PR_PR & (IWDG_PR_PR_2 | IWDG_PR_PR_0));
  while (READ_BIT(IWDG->SR, IWDG_SR_PVU));

  /* Set counter and wait until it ready */
  IWDG->RLR = (IWDG_RLR_RL & counter);
  while (READ_BIT(IWDG->SR, IWDG_SR_RVU));

  /* Set window and wait until it ready */
  IWDG->WINR = (IWDG_WINR_WIN & counter);
  while (READ_BIT(IWDG->SR, IWDG_SR_WVU));

  /* Reload the reset key */
  IWDG->KR = IWDG_KEY_RELOAD;

}