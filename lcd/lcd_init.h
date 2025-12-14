#ifndef __LCD_INIT_H
#define __LCD_INIT_H

#include "sys.h"

#define USE_HORIZONTAL 1 // 设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏

#if USE_HORIZONTAL == 0 || USE_HORIZONTAL == 1
#define LCD_W 128
#define LCD_H 160

#else
#define LCD_W 160
#define LCD_H 128
#endif

/* ===== LCD GPIO 端口定义 ===== */
#define LCD_CS_PORT GPIOB
#define LCD_BLK_PORT GPIOB
#define LCD_RES_PORT GPIOB
#define LCD_DC_PORT GPIOB
#define LCD_SCLK_PORT GPIOA
#define LCD_MOSI_PORT GPIOA

/* ===== LCD GPIO 引脚定义 ===== */
#define LCD_CS_PIN GPIO_PIN_9
#define LCD_BLK_PIN GPIO_PIN_8
#define LCD_RES_PIN GPIO_PIN_7
#define LCD_DC_PIN GPIO_PIN_6
#define LCD_SCLK_PIN GPIO_PIN_5
#define LCD_MOSI_PIN GPIO_PIN_7

/* ===== CS ===== */
#define LCD_CS_Clr() HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_RESET)
#define LCD_CS_Set() HAL_GPIO_WritePin(LCD_CS_PORT, LCD_CS_PIN, GPIO_PIN_SET)

/* ===== BLK ===== */
#define LCD_BLK_Clr()                                                          \
  HAL_GPIO_WritePin(LCD_BLK_PORT, LCD_BLK_PIN, GPIO_PIN_RESET)
#define LCD_BLK_Set() HAL_GPIO_WritePin(LCD_BLK_PORT, LCD_BLK_PIN, GPIO_PIN_SET)

/* ===== RES ===== */
#define LCD_RES_Clr()                                                          \
  HAL_GPIO_WritePin(LCD_RES_PORT, LCD_RES_PIN, GPIO_PIN_RESET)
#define LCD_RES_Set() HAL_GPIO_WritePin(LCD_RES_PORT, LCD_RES_PIN, GPIO_PIN_SET)

/* ===== DC ===== */
#define LCD_DC_Clr() HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_RESET)
#define LCD_DC_Set() HAL_GPIO_WritePin(LCD_DC_PORT, LCD_DC_PIN, GPIO_PIN_SET)

/* ===== SCLK ===== */
#define LCD_SCLK_Clr()                                                         \
  HAL_GPIO_WritePin(LCD_SCLK_PORT, LCD_SCLK_PIN, GPIO_PIN_RESET)
#define LCD_SCLK_Set()                                                         \
  HAL_GPIO_WritePin(LCD_SCLK_PORT, LCD_SCLK_PIN, GPIO_PIN_SET)

/* ===== MOSI ===== */
#define LCD_MOSI_Clr()                                                         \
  HAL_GPIO_WritePin(LCD_MOSI_PORT, LCD_MOSI_PIN, GPIO_PIN_RESET)
#define LCD_MOSI_Set()                                                         \
  HAL_GPIO_WritePin(LCD_MOSI_PORT, LCD_MOSI_PIN, GPIO_PIN_SET)

void LCD_Writ_Bus(uint8_t dat); // 模拟SPI时序
void LCD_WR_DATA8(uint8_t dat); // 写入一个字节
void LCD_WR_DATA(uint16_t dat); // 写入两个字节
void LCD_WR_REG(uint8_t dat);   // 写入一个指令
void LCD_Address_Set(uint16_t x1, uint16_t y1, uint16_t x2,
                     uint16_t y2); // 设置坐标函数
void LCD_Init(void);               // LCD初始化
#endif
