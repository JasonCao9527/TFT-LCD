/**
  ******************************************************************************
  * @file             LCD_TFTColor.h
  * @author           Jason
  * @brief            TFT常用颜色表
  * @note             None
  * @date             2024/2/6
  ******************************************************************************
  */

#include "LCD.h"

#ifndef STM32F103C8TX_PROJECT_LCD_TFTCOLOR_H
#define STM32F103C8TX_PROJECT_LCD_TFTCOLOR_H


/***************************************************************************************
**                         Section 6: Colour enumeration
***************************************************************************************/
// Default color definitions
#define TFT_BLACK       0x0000      /*   0,   0,   0 */
#define TFT_NAVY        0x000F      /*   0,   0, 128 */
#define TFT_DARKGREEN   0x03E0      /*   0, 128,   0 */
#define TFT_DARKCYAN    0x03EF      /*   0, 128, 128 */
#define TFT_MAROON      0x7800      /* 128,   0,   0 */
#define TFT_PURPLE      0x780F      /* 128,   0, 128 */
#define TFT_OLIVE       0x7BE0      /* 128, 128,   0 */
#define TFT_LIGHTGREY   0xD69A      /* 211, 211, 211 */
#define TFT_DARKGREY    0x7BEF      /* 128, 128, 128 */
#define TFT_BLUE        0x001F      /*   0,   0, 255 */
#define TFT_GREEN       0x07E0      /*   0, 255,   0 */
#define TFT_CYAN        0x07FF      /*   0, 255, 255 */
#define TFT_RED         0xF800      /* 255,   0,   0 */
#define TFT_MAGENTA     0xF81F      /* 255,   0, 255 */
#define TFT_YELLOW      0xFFE0      /* 255, 255,   0 */
#define TFT_WHITE       0xFFFF      /* 255, 255, 255 */
#define TFT_ORANGE      0xFDA0      /* 255, 180,   0 */
#define TFT_GREENYELLOW 0xB7E0      /* 180, 255,   0 */
#define TFT_PINK        0xFE19      /* 255, 192, 203 */ //Lighter pink, was 0xFC9F
#define TFT_BROWN       0x9A60      /* 150,  75,   0 */
#define TFT_GOLD        0xFEA0      /* 255, 215,   0 */
#define TFT_SILVER      0xC618      /* 192, 192, 192 */
#define TFT_SKYBLUE     0x867D      /* 135, 206, 235 */
#define TFT_VIOLET      0x915C      /* 180,  46, 226 */
#define TFT_TRANSPARENT 0x0120 // This is actually a dark green

//下面是TFT_espi库自己的编码定义，暂时用不上

/*// Next is a special 16-bit colour value that encodes to 8 bits
// and will then decode back to the same 16-bit value.
// Convenient for 8-bit and 16-bit transparent sprites.
#define TFT_TRANSPARENT 0x0120 // This is actually a dark green

// Default palette for 4-bit colour sprites
static const uint16_t default_4bit_palette[] PROGMEM = {
        TFT_BLACK,    //  0  ^
        TFT_BROWN,    //  1  |
        TFT_RED,      //  2  |
        TFT_ORANGE,   //  3  |
        TFT_YELLOW,   //  4  Colours 0-9 follow the resistor colour code!
        TFT_GREEN,    //  5  |
        TFT_BLUE,     //  6  |
        TFT_PURPLE,   //  7  |
        TFT_DARKGREY, //  8  |
        TFT_WHITE,    //  9  v
        TFT_CYAN,     // 10  Blue+green mix
        TFT_MAGENTA,  // 11  Blue+red mix
        TFT_MAROON,   // 12  Darker red colour
        TFT_DARKGREEN,// 13  Darker green colour
        TFT_NAVY,     // 14  Darker blue colour
        TFT_PINK      // 15
};*/

#endif //STM32F103C8TX_PROJECT_LCD_TFTCOLOR_H
