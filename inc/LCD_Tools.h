/**
  ******************************************************************************
  * @file             LCD_Tools.h
  * @author           Jason
  * @brief            用于存放LCD驱动的工具函数，不会出现在外部调用的函数中，以保持代码简洁性
  * @date             2024/2/6
  ******************************************************************************
  */

#ifndef STM32F103C8TX_PROJECT_LCD_TOOLS_H
#define STM32F103C8TX_PROJECT_LCD_TOOLS_H

#include "stm32f10x.h"                  // Device header

uint16_t LCD_ColorHEX(const char *TrueColorHEX);
uint16_t LCD_ColorRGB(uint8_t Red,uint8_t Green,uint8_t Blue);

void LCD_Clear(uint16_t Color);
void LCD_DrawPoint(u16 x,u16 y,u16 color);
void LCD_SetZone(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2);//设置坐标函数


#endif //STM32F103C8TX_PROJECT_LCD_TOOLS_H
