#include "LCD.h"
#include "LCD_Tools.h"


#if __LCD_ST7735S__

//重构函数，将定义进行数字化，出于代码一致性考虑，名称不做变换
//例如LCD_SCLK_Clr()=LCD_W_SCLK(0)
//LCD_SCLK_Set()=LCD_W_SCLK(1)
//-----------------LCD端口定义----------------

//#define LCD_SCLK_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_12)//SCL=SCLK
//#define LCD_SCLK_Set() GPIO_SetBits(GPIOB,GPIO_Pin_12)
//
//#define LCD_MOSI_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_13)//SDA=MOSI
//#define LCD_MOSI_Set() GPIO_SetBits(GPIOB,GPIO_Pin_13)
//
//#define LCD_RES_Clr()  GPIO_ResetBits(GPIOB,GPIO_Pin_14)//RES
//#define LCD_RES_Set()  GPIO_SetBits(GPIOB,GPIO_Pin_14)
//
//#define LCD_DC_Clr()   GPIO_ResetBits(GPIOB,GPIO_Pin_15)//DC
//#define LCD_DC_Set()   GPIO_SetBits(GPIOB,GPIO_Pin_15)
//
//#define LCD_CS_Clr()   GPIO_ResetBits(GPIOA,GPIO_Pin_8)//CS
//#define LCD_CS_Set()   GPIO_SetBits(GPIOA,GPIO_Pin_8)
//
//#define LCD_BLK_Clr()  GPIO_ResetBits(GPIOA,GPIO_Pin_9)//BLK
//#define LCD_BLK_Set()  GPIO_SetBits(GPIOA,GPIO_Pin_9)


//以下为软件模拟SPI的引脚配置及基础函数
/**
  * @brief  软件模拟SPI-拉低或者释放`SCL`
  * @param  None
  * @retval  None
  */
void LCD_SCLK_Clr(void)
{
    GPIO_ResetBits(GPIOB,GPIO_Pin_12);
}
void LCD_SCLK_Set(void)
{
    GPIO_SetBits(GPIOB,GPIO_Pin_12);
}

/**
  * @brief  软件模拟SPI-拉低或者释放`MOSI`
  * @param  None
  * @retval  None
  */
void LCD_MOSI_Clr(void)
{
    GPIO_ResetBits(GPIOB,GPIO_Pin_13);
}
void LCD_MOSI_Set(void)
{
    GPIO_SetBits(GPIOB,GPIO_Pin_13);
}

/**
  * @brief  软件模拟SPI-拉低或者释放`RES`
  * @param  None
  * @retval  None
  */
void LCD_RES_Clr(void)
{
    GPIO_ResetBits(GPIOB,GPIO_Pin_14);
}
void LCD_RES_Set(void)
{
    GPIO_SetBits(GPIOB,GPIO_Pin_14);
}

/**
  * @brief  软件模拟SPI-拉低或者释放`DC`
  * @param  None
  * @retval  None
  */
void LCD_DC_Clr(void)
{
    GPIO_ResetBits(GPIOB,GPIO_Pin_15);
}
void LCD_DC_Set(void)
{
    GPIO_SetBits(GPIOB,GPIO_Pin_15);
}

/**
  * @brief  软件模拟SPI-拉低或者释放`CS`
  * @param  None
  * @retval  None
  */
void LCD_CS_Clr(void)
{
    GPIO_ResetBits(GPIOA,GPIO_Pin_8);
}
void LCD_CS_Set(void)
{
    GPIO_SetBits(GPIOA,GPIO_Pin_8);
}

/**
  * @brief  软件模拟SPI-拉低或者释放`BLK`，即背光控制
  * @param  None
  * @retval  None
  */
void LCD_BLK_Clr(void)
{
    GPIO_ResetBits(GPIOA,GPIO_Pin_9);
}
void LCD_BLK_Set(void)
{
    GPIO_SetBits(GPIOA,GPIO_Pin_9);
}


/**
  * @brief  LCD引脚初始化函数
  * @param  None
  * @retval  None
  */
void LCD_GPIO_Init(void)
{
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);	 //使能A端口时钟
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //使能B端口时钟

    GPIO_InitTypeDef  GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //推挽输出
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//速度50MHz

    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;
    GPIO_Init(GPIOB, &GPIO_InitStructure);	  //初始化SCL
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;
    GPIO_Init(GPIOB, &GPIO_InitStructure);	  //初始化SDA
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
    GPIO_Init(GPIOB, &GPIO_InitStructure);	  //初始化RES
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_15;
    GPIO_Init(GPIOB, &GPIO_InitStructure);	  //初始化DC
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;
    GPIO_Init(GPIOA, &GPIO_InitStructure);	  //初始化CS
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_9;
    GPIO_Init(GPIOA, &GPIO_InitStructure);	  //初始化BLK

    LCD_SCLK_Set();
    LCD_MOSI_Set();
    LCD_RES_Set();
    LCD_DC_Set();
    LCD_CS_Set();
    LCD_BLK_Set();

}


/******************************************************************************
      函数说明：LCD串行数据写入函数
      入口数据：dat  要写入的串行数据
      返回值：  无
******************************************************************************/
void LCD_Writ_Bus(u8 dat)
{
    u8 i;
    LCD_CS_Clr();
    for(i=0;i<8;i++)
    {
        LCD_SCLK_Clr();
        if(dat&0x80)
        {
            LCD_MOSI_Set();
        }
        else
        {
            LCD_MOSI_Clr();
        }
        LCD_SCLK_Set();
        dat<<=1;
    }
    LCD_CS_Set();
}


/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA8(u8 dat)
{
    LCD_Writ_Bus(dat);
}


/******************************************************************************
      函数说明：LCD写入数据
      入口数据：dat 写入的数据
      返回值：  无
******************************************************************************/
void LCD_WR_DATA(u16 dat)
{
    LCD_Writ_Bus(dat>>8);
    LCD_Writ_Bus(dat);
}


/******************************************************************************
      函数说明：LCD写入命令
      入口数据：dat 写入的命令
      返回值：  无
******************************************************************************/
void LCD_WR_REG(u8 dat)
{
    LCD_DC_Clr();//写命令
    LCD_Writ_Bus(dat);
    LCD_DC_Set();//写数据
}


void LCD_Init(void)
{
    LCD_GPIO_Init();//初始化GPIO

    LCD_RES_Clr();//复位
    Delay_ms(100);
    LCD_RES_Set();
    Delay_ms(100);

    LCD_BLK_Set();//打开背光
    Delay_ms(100);

    LCD_WR_REG(0x11);     //Sleep out
    Delay_ms(120);                //Delay 120ms
    LCD_WR_REG(0xB1);     //Normal mode
    LCD_WR_DATA8(0x05);
    LCD_WR_DATA8(0x3C);
    LCD_WR_DATA8(0x3C);
    LCD_WR_REG(0xB2);     //Idle mode
    LCD_WR_DATA8(0x05);
    LCD_WR_DATA8(0x3C);
    LCD_WR_DATA8(0x3C);
    LCD_WR_REG(0xB3);     //Partial mode
    LCD_WR_DATA8(0x05);
    LCD_WR_DATA8(0x3C);
    LCD_WR_DATA8(0x3C);
    LCD_WR_DATA8(0x05);
    LCD_WR_DATA8(0x3C);
    LCD_WR_DATA8(0x3C);
    LCD_WR_REG(0xB4);     //Dot inversion
    LCD_WR_DATA8(0x03);
    LCD_WR_REG(0xC0);     //AVDD GVDD
    LCD_WR_DATA8(0xAB);
    LCD_WR_DATA8(0x0B);
    LCD_WR_DATA8(0x04);
    LCD_WR_REG(0xC1);     //VGH VGL
    LCD_WR_DATA8(0xC5);   //C0
    LCD_WR_REG(0xC2);     //Normal Mode
    LCD_WR_DATA8(0x0D);
    LCD_WR_DATA8(0x00);
    LCD_WR_REG(0xC3);     //Idle
    LCD_WR_DATA8(0x8D);
    LCD_WR_DATA8(0x6A);
    LCD_WR_REG(0xC4);     //Partial+Full
    LCD_WR_DATA8(0x8D);
    LCD_WR_DATA8(0xEE);
    LCD_WR_REG(0xC5);     //VCOM
    LCD_WR_DATA8(0x0F);
    LCD_WR_REG(0xE0);     //positive gamma
    LCD_WR_DATA8(0x07);
    LCD_WR_DATA8(0x0E);
    LCD_WR_DATA8(0x08);
    LCD_WR_DATA8(0x07);
    LCD_WR_DATA8(0x10);
    LCD_WR_DATA8(0x07);
    LCD_WR_DATA8(0x02);
    LCD_WR_DATA8(0x07);
    LCD_WR_DATA8(0x09);
    LCD_WR_DATA8(0x0F);
    LCD_WR_DATA8(0x25);
    LCD_WR_DATA8(0x36);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x08);
    LCD_WR_DATA8(0x04);
    LCD_WR_DATA8(0x10);
    LCD_WR_REG(0xE1);     //negative gamma
    LCD_WR_DATA8(0x0A);
    LCD_WR_DATA8(0x0D);
    LCD_WR_DATA8(0x08);
    LCD_WR_DATA8(0x07);
    LCD_WR_DATA8(0x0F);
    LCD_WR_DATA8(0x07);
    LCD_WR_DATA8(0x02);
    LCD_WR_DATA8(0x07);
    LCD_WR_DATA8(0x09);
    LCD_WR_DATA8(0x0F);
    LCD_WR_DATA8(0x25);
    LCD_WR_DATA8(0x35);
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x09);
    LCD_WR_DATA8(0x04);
    LCD_WR_DATA8(0x10);

    LCD_WR_REG(0xFC);
    LCD_WR_DATA8(0x80);

    LCD_WR_REG(0x3A);
    LCD_WR_DATA8(0x05);
    LCD_WR_REG(0x36);
    if(USE_HORIZONTAL==0)LCD_WR_DATA8(0x08);
    else if(USE_HORIZONTAL==1)LCD_WR_DATA8(0xC8);
    else if(USE_HORIZONTAL==2)LCD_WR_DATA8(0x78);
    else LCD_WR_DATA8(0xA8);
    LCD_WR_REG(0x21);     //Display inversion
    LCD_WR_REG(0x29);     //Display on
    LCD_WR_REG(0x2A);     //Set Column Address
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x1A);  //26
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x69);   //105
    LCD_WR_REG(0x2B);     //Set Page Address
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0x01);    //1
    LCD_WR_DATA8(0x00);
    LCD_WR_DATA8(0xA0);    //160
    LCD_WR_REG(0x2C);

    LCD_Clear(LCD_ColorHEX("#000000"));//将屏幕刷黑 todo
    //更进一步的，可以把屏幕刷黑再打开背光
}

//基础函数区
/******************************************************************************
      函数说明：设置起始和结束地址
      入口数据：x1,x2 设置列的起始和结束地址
                y1,y2 设置行的起始和结束地址
      返回值：  无
******************************************************************************/
void LCD_SetZone(uint16_t x1, uint16_t y1, uint16_t x2, uint16_t y2)
{
    if(USE_HORIZONTAL==0)
    {
        LCD_WR_REG(0x2a);//列地址设置
        LCD_WR_DATA(x1+26);
        LCD_WR_DATA(x2+26);
        LCD_WR_REG(0x2b);//行地址设置
        LCD_WR_DATA(y1+1);
        LCD_WR_DATA(y2+1);
        LCD_WR_REG(0x2c);//储存器写
    }
    else if(USE_HORIZONTAL==1)
    {
        LCD_WR_REG(0x2a);//列地址设置
        LCD_WR_DATA(x1+26);
        LCD_WR_DATA(x2+26);
        LCD_WR_REG(0x2b);//行地址设置
        LCD_WR_DATA(y1+1);
        LCD_WR_DATA(y2+1);
        LCD_WR_REG(0x2c);//储存器写
    }
    else if(USE_HORIZONTAL==2)
    {
        LCD_WR_REG(0x2a);//列地址设置
        LCD_WR_DATA(x1+1);
        LCD_WR_DATA(x2+1);
        LCD_WR_REG(0x2b);//行地址设置
        LCD_WR_DATA(y1+26);
        LCD_WR_DATA(y2+26);
        LCD_WR_REG(0x2c);//储存器写
    }
    else
    {
        LCD_WR_REG(0x2a);//列地址设置
        LCD_WR_DATA(x1+1);
        LCD_WR_DATA(x2+1);
        LCD_WR_REG(0x2b);//行地址设置
        LCD_WR_DATA(y1+26);
        LCD_WR_DATA(y2+26);
        LCD_WR_REG(0x2c);//储存器写
    }
}

/**
  * @brief  LCD全屏幕清除（指定颜色）
  * @param TFT_Color:用于TFT上显示的颜色（RGB565）
  * @retval None
  * @note   全屏幕清除
  */
void LCD_Clear(uint16_t TFT_Color)
{
    uint16_t i,j;
    LCD_SetZone(0, 0, LCD_W - 1, LCD_H - 1);
    for(i=0;i<LCD_W;i++)
    {
        for (j=0;j<LCD_H;j++)
        {
            LCD_WR_DATA(TFT_Color);
        }
    }
}

/**
  * @brief  LCD区域填充
  * @param  x1:列的起始地址
  * @param  y1:列的结束地址
  * @param  x2:行的起始地址
  * @param  y2:行的结束地址
  * @retval None
  * @note   这里的光标是一个区域，并口屏设置的是一个起始点
  */
void LCD_Fill(uint16_t xsta,uint16_t ysta,uint16_t xend,uint16_t yend,uint16_t color)
{
    uint16_t i,j;
    LCD_SetZone(xsta, ysta, xend - 1, yend - 1);//设置显示范围
    for(i=ysta;i<yend;i++)
    {
        for(j=xsta;j<xend;j++)
        {
            LCD_WR_DATA(color);
        }
    }
}

/**
  * @brief  在指定位置画点
  * @param  X 指定区域左上角的横坐标
  * @param  Y 指定区域左上角的纵坐标
  * @param  Color:16位TFT_Color
  * @retval None
  */
void LCD_DrawPoint(uint16_t x,uint16_t y,uint16_t color)
{
    LCD_SetZone(x, y, x, y);//设置光标位置
    LCD_WR_DATA(color);
}

#endif
