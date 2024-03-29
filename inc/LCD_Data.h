#ifndef STM32F103C8TX_PROJECT_LCD_DATA_H
#define STM32F103C8TX_PROJECT_LCD_DATA_H

/*定义中文字符宽度*/
//UTF8编码给3，GB2312编码给2
#define LCD_CHN_CHAR_WIDTH 3

// https://blog.csdn.net/u012206617/article/details/94383568

typedef struct
{
    unsigned char Index[LCD_CHN_CHAR_WIDTH+1];
    unsigned char Msk[24];
}typFNT_GB12;

typedef struct
{
    unsigned char Index[LCD_CHN_CHAR_WIDTH+1];
    unsigned char Msk[32];
}typFNT_GB16;

typedef struct
{
    unsigned char Index[LCD_CHN_CHAR_WIDTH+1];
    unsigned char Msk[72];
}typFNT_GB24;

typedef struct
{
    unsigned char Index[LCD_CHN_CHAR_WIDTH+1];
    unsigned char Msk[128];
}typFNT_GB32;

extern const unsigned char ascii_1206[][12];
extern const unsigned char ascii_1608[][16];
extern const unsigned char ascii_2412[][48];
extern const unsigned char ascii_3216[][64];
extern const typFNT_GB12 tfont12[];
extern const typFNT_GB16 tfont16[];
extern const typFNT_GB24 tfont24[];
extern const typFNT_GB32 tfont32[];
extern const unsigned char gImage_1[3200];

#endif //STM32F103C8TX_PROJECT_LCD_DATA_H
