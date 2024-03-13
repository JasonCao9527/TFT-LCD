#ifndef STM32F103C8TX_PROJECT_LCD_H
#define STM32F103C8TX_PROJECT_LCD_H

#include "stm32f10x.h"                  // Device header
#include "Delay.h"
#include "LCD_TFTColor.h"

#define USE_HORIZONTAL 0  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏;圆形屏幕要设置成0
#define LCD_LengthA 320     //较长边
#define LCD_LengthB 240     //较短边

#define LCD_W LCD_LengthA
#define LCD_H LCD_LengthB

#define TFT_textwidth   LCD_W
#define TFT_textheight  LCD_H

//***

//驱动方式选择
//#define __SoftSPI_LCD_DRIVER__ 1
//#define __HardSPI_LCD_DRIVER__ 1

//驱动芯片选择
//#define __LCD_ST7735S__ 1
//#define __LCD_ST7789V__ 1
//#define __LCD_GC9A01__ 1
#define __LCD_JBT6K71_AS__ 1


uint16_t LCD_ColorHEX(const char *TrueColorHEX);
uint16_t LCD_ColorRGB(uint8_t Red,uint8_t Green,uint8_t Blue);


void LCD_Init(void);//LCD初始化
void LCD_Clear(uint16_t Color);

//
void LCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);//指定区域填充颜色
void LCD_DrawPoint(u16 x,u16 y,u16 color);//在指定位置画一个点
void LCD_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);//在指定位置画一条线
void LCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);//在指定位置画一个矩形
void Draw_Circle(u16 x0,u16 y0,u8 r,u16 color);//在指定位置画一个圆

void LCD_ShowChinese(u16 x,u16 y,u8 *s,u16 fc,u16 bc,u8 sizey,u8 mode);//显示汉字串
void LCD_ShowChinese12x12(u16 x,u16 y,u8 *s,u16 fc,u16 bc,u8 sizey,u8 mode);//显示单个12x12汉字
void LCD_ShowChinese16x16(u16 x,u16 y,u8 *s,u16 fc,u16 bc,u8 sizey,u8 mode);//显示单个16x16汉字
void LCD_ShowChinese24x24(u16 x,u16 y,u8 *s,u16 fc,u16 bc,u8 sizey,u8 mode);//显示单个24x24汉字
void LCD_ShowChinese32x32(u16 x,u16 y,u8 *s,u16 fc,u16 bc,u8 sizey,u8 mode);//显示单个32x32汉字

void LCD_ShowChar(u16 x,u16 y,u8 num,u16 fc,u16 bc,u8 sizey,u8 mode);//显示一个字符
void LCD_ShowString(u16 x,u16 y,const u8 *p,u16 fc,u16 bc,u8 sizey,u8 mode);//显示字符串
u32 mypow(u8 m,u8 n);//求幂
void LCD_ShowIntNum(u16 x,u16 y,u16 num,u8 len,u16 fc,u16 bc,u8 sizey);//显示整数变量
void LCD_ShowFloatNum1(u16 x,u16 y,float num,u8 len,u16 fc,u16 bc,u8 sizey);//显示两位小数变量

void LCD_ShowPicture(u16 x,u16 y,u16 length,u16 width,const u8 pic[]);//显示图片

#endif //STM32F103C8TX_PROJECT_LCD_H
