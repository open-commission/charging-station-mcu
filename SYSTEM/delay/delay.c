#include "delay.h"

/*
 * 基于 DWT 的微秒延时
 * 适用于 Cortex-M3/M4/M7
 */

static uint32_t cpu_freq_hz = 0;

/**
 * @brief 初始化延时模块
 *        必须在 HAL_Init() 之后调用
 */
void delay_init(void) {
  cpu_freq_hz = HAL_RCC_GetHCLKFreq();

  /* 使能 DWT */
  CoreDebug->DEMCR |= CoreDebug_DEMCR_TRCENA_Msk;

  /* 清零计数器 */
  DWT->CYCCNT = 0;

  /* 使能 CYCCNT */
  DWT->CTRL |= DWT_CTRL_CYCCNTENA_Msk;
}

/**
 * @brief 微秒级延时
 */
void delay_us(uint32_t us) {
  uint32_t start = DWT->CYCCNT;
  uint32_t ticks = us * (cpu_freq_hz / 1000000);

  while ((DWT->CYCCNT - start) < ticks) {
    __NOP();
  }
}

/**
 * @brief 毫秒级延时
 */
void delay_ms(uint32_t ms) { HAL_Delay(ms); }
