/**
  ******************************************************************************
  * @file             LCD.c
  * @author           Jason
  * @brief            LCD相关应用函数
  * @note             None
  * @attention        None
  * @date             2023/9/23
  ******************************************************************************
  */

#include "LCD.h"
#include "LCD_Tools.h"
#include "LCD_Data.h"

/**
  * @brief  颜色转换函数，将真彩色转换为高彩色
  * @param  Red:红色值，范围：0~255
  * @param  Green: 绿色值，范围：0~255
  * @param  Blue: 蓝色值，范围：0~255
  * @retval TFT_Color:用于TFT上显示的颜色（RGB565）
  * @note   像其他软件一样输入RGB值即可
  */
uint16_t LCD_ColorRGB(uint8_t Red,uint8_t Green,uint8_t Blue)
{
//    本函数参考自: 参考：https://blog.csdn.net/qq_42059474/article/details/132984922
    uint16_t TFT_Color=0;
    TFT_Color |= (Red >> 3) << 11;      //将red的高5位放到color的高5位
    TFT_Color |= (Green >> 2) << 5;     //将green的高6位放到color的中间6位
    TFT_Color |= Blue >> 3;             //将blue的高5位放到color的低5位
    return TFT_Color;
}

/**
  * @brief  颜色转换函数，将真彩色转换为高彩色
  * @param  TrueColorHEX:HEX编码下的RGB值，范围："#000000~FFFFFF"
  * @retval TFT_Color:用于TFT上显示的颜色（RGB565）
  * @note   输入的样式需要为字符串且带有'#'号，例如："#FFFFFF"
  */
uint16_t LCD_ColorHEX(const char *TrueColorHEX)
{
    uint32_t HEX_Color=0;
    uint8_t Red=0;
    uint8_t Green=0;
    uint8_t Blue=0;
    uint16_t TFT_Color=0;

    //十六进制数位移位数是4倍于二进制的
    //在ASCII码表中，'0'=48，'A'=65
    for (int i = 1; i < 7; ++i) {
        if(TrueColorHEX[i]>='0'&&TrueColorHEX[i]<='9'){
            HEX_Color |= ((TrueColorHEX[i]-48)<<4*(6-i));
        } else if(TrueColorHEX[i]>='A'&&TrueColorHEX[i]<='F'){
            HEX_Color |= ((TrueColorHEX[i]-65+10)<<4*(6-i));
        } else
        {
            HEX_Color |= (0x0000000F<<4*(6-i));
        }
    }

    //HEX_Color的样式为0x00FFFFFF;
    Red=(HEX_Color>>(4*4))&0x000000FF;//单独取出红色值
    Green=(HEX_Color>>(2*4))&0x000000FF;//单独取出绿色值
    Blue=(HEX_Color>>(0*4))&0x000000FF;//单独取出蓝色值

    TFT_Color=LCD_ColorRGB(Red,Green,Blue);

    return TFT_Color;
}
