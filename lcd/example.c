//////////////////////////////////////////////////////////////////////////////////
//  文 件 名   : main.c
//  版 本 号   : v2.0
//  作    者   : luxban
//  生成日期   : 2022-6-01
//  最近修改   :
//  功能描述   :演示例程(STM32F103系列)
//              接口说明:
//              LED:PA8
//
//              TFT-LCD:
//              GND   电源地
//              VCC   3.3v电源
//              SCL   PB4（SCLK）
//              SDA   PB5（MOSI）
//              RES   PB6
//              DC    PB7
//              CS    PB8
//              BLK   PB9
//              ----------------------------------------------------------------
//******************************************************************************/
#include "delay.h"
#include "lcd.h"
#include "lcd_init.h"
#include "pic.h"
#include "sys.h"

int main(void) {
  float t = 0;
  delay_init();
  LCD_Init(); // LCD初始化
  LCD_Fill(0, 0, LCD_W, LCD_H, WHITE);
  while (1) {
    LCD_ShowChinese(0, 0, "中景园电子", RED, WHITE, 24, 0);
    LCD_ShowString(24, 30, "LCD_W:", RED, WHITE, 16, 0);
    LCD_ShowIntNum(72, 30, LCD_W, 3, RED, WHITE, 16);
    LCD_ShowString(24, 50, "LCD_H:", RED, WHITE, 16, 0);
    LCD_ShowIntNum(72, 50, LCD_H, 3, RED, WHITE, 16);
    LCD_ShowFloatNum1(20, 80, t, 4, RED, WHITE, 16);
    t += 0.11;
    LCD_ShowPicture(65, 80, 40, 40, gImage_1);
  }
}
