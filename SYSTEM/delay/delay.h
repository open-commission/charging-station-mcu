#ifndef __DELAY_H
#define __DELAY_H

#include "stm32f1xx_hal.h" // 根据你的芯片修改

void delay_init(void);
void delay_us(uint32_t us);
void delay_ms(uint32_t ms);

#endif
