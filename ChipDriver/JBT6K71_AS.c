// 本文件适用于8bit并口JBT6K71，现阶段为直接IO模拟8080而不是硬件FSMC模拟

#include "LCD.h"
#include "LCD_Tools.h"

#if  __LCD_JBT6K71_AS__

//注：PB3、PB4默认功能并不是PB3和PB4而是用作了JTAG的功能
//故将PB3、PB4改为PB12、PB13

/*
 * 本文件中的引脚连接参数
 * RD:PB12
 * WR:PB13
 * DC:PB5
 * CS:PB6
 * RST:PB7
 * BL:PB8
 * DataBus:A0-A7
 * */


/**
  * @brief  LCD写RD高低电平
  * @param  BitValue:要写入RD的电平值，范围：0/1
  * @retval None
  * @note   需要配置为推挽输出
  */
void LCD_W_RD(uint8_t BitValue)
{
    /*根据BitValue的值，将RD置高电平或者低电平*/
    GPIO_WriteBit(GPIOB, GPIO_Pin_12, (BitAction)BitValue);
}

/**
  * @brief  LCD写WR高低电平
  * @param  BitValue:要写入WR的电平值，范围：0/1
  * @retval None
  * @note   需要配置为推挽输出
  */
void LCD_W_WR(uint8_t BitValue)
{
    /*根据BitValue的值，将WR置高电平或者低电平*/
    GPIO_WriteBit(GPIOB, GPIO_Pin_13, (BitAction)BitValue);
}


/**
  * @brief  LCD写DC高低电平
  * @param  BitValue:要写入DC的电平值，范围：0/1
  * @retval None
  * @note   需要配置为推挽输出
  */
void LCD_W_DC(uint8_t BitValue)
{
    /*根据BitValue的值，将DC置高电平或者低电平*/
    GPIO_WriteBit(GPIOB, GPIO_Pin_5, (BitAction)BitValue);
}


/**
  * @brief  LCD写CS高低电平
  * @param  BitValue:要写入CS的电平值，范围：0/1
  * @retval None
  * @note   需要配置为推挽输出
  *         CS在一些板子上也被称为RS引脚
  */
void LCD_W_CS(uint8_t BitValue)
{
    /*根据BitValue的值，将CS置高电平或者低电平*/
    GPIO_WriteBit(GPIOB, GPIO_Pin_6, (BitAction)BitValue);
}


/**
  * @brief  LCD写RST高低电平
  * @param  BitValue:要写入RST的电平值，范围：0/1
  * @retval None
  * @note   需要配置为推挽输出
  */
void LCD_W_RST(uint8_t BitValue)
{
    /*根据BitValue的值，将RST置高电平或者低电平*/
    GPIO_WriteBit(GPIOB, GPIO_Pin_7, (BitAction)BitValue);
}


/**
  * @brief  LCD写BL高低电平
  * @param  BitValue:要写入BL的电平值，范围：0/1
  * @retval None
  * @note   需要配置为推挽输出
  */
void LCD_W_BL(uint8_t BitValue)
{
    /*根据BitValue的值，将BL置高电平或者低电平*/
    GPIO_WriteBit(GPIOB, GPIO_Pin_8, (BitAction)BitValue);
}



/**
  * @brief  LCD写DataBus的值
  * @param  Data:要写入并行数据，范围：uint8_t
  * @retval None
  * @note   所有引脚需要配置为推挽输出，且建议直接使用寄存器进行赋值
  *         Data在STM32中不是关键字，但在51单片机中为关键字，如果移植需要将变量名改为Dat
  *         用户需要根据参数传入的值，将DataBus转换为并行输出
  *         当参数传入0xFFh时，置DataBus为全高，当参数传入0x00h时，置DataBus为全低
  */
void LCD_W_DATA(uint16_t Data)
{
//使用寄存器操作一排GPIO，使用ODR 寄存器进行设置，只可以16位读写，即`GPIOA->ODR`
//初始地址GPIOA:0x40010800、GPIOB:0x40010C00、GPIOC:0x40011000
// &= ~ 用来清0（给某一位单独置0）
// |=   用来给某一位单独置1
//配置端口输出数据寄存器ODR，偏移地址0x0Ch
//[stm32寄存器操作IO](https://blog.csdn.net/weixin_66084944/article/details/133428477)
//[STM32寄存器操作IO](https://blog.csdn.net/ChenWenHaoHaoHao/article/details/126407370)
//注：GPIO_WriteBit只可对一个IO进行操作，GPIO_SetBits和GPIO_ResetBits可以对多个IO进行操作，GPIO_Write可以对整个端口进行操作
//[IO操作函数解析](https://blog.csdn.net/only_a_Heroic_car/article/details/130067196)

//这里使用A0-A7
//    GPIO_Write(GPIOA, Data);//方案1
    GPIO_Write(GPIOA, Data|0X0000);//方案1
//    GPIOA->ODR = Data|0X0000;//方案2
}


/**
  * @brief  lCD引脚初始化
  * @param  None
  * @retval None
  * @note   用户需要将RD、WR、DC、CS、RST、BL、DataBus引脚初始化为推挽输出模式
  */
void LCD_GPIO_Init(void)
{
    uint32_t i, j;

    /*在初始化前，加入适量延时，待LCD供电稳定*/
    for (i = 0; i < 1000; i ++)
    {
        for (j = 0; j < 1000; j ++);
    }

/*
 * RD:PB12
 * WR:PB13
 * DC:PB5
 * CS:PB6
 * RST:PB7
 * BL:PB8
 * DataBus:A0-A7
 * */

//尽量避开PB3、PB4

    /*将RD、WR、DC、CS、RST、BL、DataBus引脚初始化为推挽输出模式*/
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
    RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);

    GPIO_InitTypeDef GPIO_InitStructure;
    GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;
    GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;

    //初始化DataBus
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0|GPIO_Pin_1|GPIO_Pin_2|GPIO_Pin_3|GPIO_Pin_4|GPIO_Pin_5|GPIO_Pin_6|GPIO_Pin_7;
    GPIO_Init(GPIOA, &GPIO_InitStructure);

    //初始化RD、WR、DC、CS、RST、BL
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12;//RD
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;//WR
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_5;//DC
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_6;//CS
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_7;//RST
    GPIO_Init(GPIOB, &GPIO_InitStructure);
    GPIO_InitStructure.GPIO_Pin = GPIO_Pin_8;//BL
    GPIO_Init(GPIOB, &GPIO_InitStructure);

    /*置引脚默认电平*/
    LCD_W_WR(1);//低电平有效
    LCD_W_RD(1);//低电平有效，不需要读屏幕的话一直保持在高电平，或直接上拉到VCC
    LCD_W_DC(1);//0为命令，1为数据
    LCD_W_CS(1);//低电平有效
//    LCD_W_RST(1);//暂不明确？等待数据手册查询
    LCD_W_BL(0);//高电平为背光打开
//    LCD_W_DATA(0x00);//并口数据全为0

//    https://blog.csdn.net/Firefly_cjd/article/details/106568959
}

/**
  * @brief  lCD简单软件延时函数
  * @param  None
  * @retval None
  * @note   None
  */
void LCD_delay(uint16_t time)  //简单软件 延时函数
{
    uint16_t i,j;
    for(i=0;i<time;i++)
        for(j=0;j<1000;j++)	;
}

/*通信协议*********************/

/**
  * @brief  lCD复位
  * @param  None
  * @retval None
  * @note   低电平复位？等待确认 todo
  */
void LCD_Reset(void)
{
//    https://blog.csdn.net/weixin_54036711
//    https://blog.csdn.net/u011303443/article/details/76514537
//    BSRR 低 16 位用于设置 GPIO 口对应位输出高电平，高 16 位用于设置 GPIO 口对应位输出低电平。
//    BRR 低 16 位用于设置 GPIO 口对应位输出低电平。高 16 位为保留地址，读写无效。
//    特别的: F1和F4系列都有 ODR和BSRR，但F4 取消了BRR。所以为了代码通用，尽量不使用BRR，反正BSRR能完成。

//原方案：
    GPIOB->BRR  = GPIO_Pin_7;//置低电平
    LCD_delay(1000);
    GPIOB->BSRR = GPIO_Pin_7;//置高电平
    LCD_delay(1000);

//更改后的方案：
//    LCD_W_RST(0);
//    LCD_delay(1000);
//    LCD_W_RST(1);
//    LCD_delay(1000);
}



/**
  * @brief  LCD写命令（16位）
  * @param  Command:要写入的命令值，范围：uint16_t，即0x0000~0xFFFF
  * @retval None
  * @note   命令信息使用16位，一次发送完
  *         发送命令时，DC引脚为低电平（0）
  */
void LCD_WriteCommand16(uint16_t Command)
{
    LCD_W_CS(0);
    LCD_W_DC(0);//0表示写入命令
    LCD_W_DATA(Command>>8);//写入命令的高八位
    LCD_W_WR(0);//模拟WR上升沿
    LCD_W_WR(1);

    LCD_W_DATA(Command);//写入命令的低八位
    LCD_W_WR(0);//模拟WR上升沿
    LCD_W_WR(1);

    LCD_W_CS(1);
}


/**
  * @brief  LCD写数据
  * @param  Data:要写入的数据，范围：uint16_t，即0x0000~0xFFFF
  * @retval None
  * @note   数据信息使用16位，一次发送完
  *         发送命令时，DC引脚为高电平（1）
  */
void LCD_WriteData16(uint16_t Data)
{
    LCD_W_CS(0);
    LCD_W_DC(1);//1表示写入数据
    LCD_W_DATA(Data>>8);//写入数据的高八位
    LCD_W_WR(0);
    LCD_W_WR(1);

    LCD_W_DATA(Data);//写入数据的低八位
    LCD_W_WR(0);
    LCD_W_WR(1);

    LCD_W_CS(1);
}

/**
  * @brief  LCD写寄存器数据
  * @param  Index:所写寄存器的索引值，范围：uint16_t，即0x0000~0xFFFF
  * @param  CongfigTemp:所写寄存器的配置信息（写入数据），范围：uint16_t，即0x0000~0xFFFF
  * @retval None
  * @note   None
  */
void LCD_WriteReg(uint16_t Index,uint16_t CongfigTemp)
{
    LCD_WriteCommand16(Index);
    LCD_WriteData16(CongfigTemp);
}


/*********************通信协议*/

/*硬件配置*********************/

/**
  * @brief  LCD初始化
  * @param  None
  * @retval None
  * @note   初始化寄存器配置信息参考TK020F9168工程代码
  *         部分寄存器设置信息部分参考：https://steward-fu.github.io/website/mcu/stc15w4k56s4/jbt6k71-as.htm
  */
void LCD_Init(void)
{
    LCD_GPIO_Init();
    LCD_Reset();//复位液晶屏
    LCD_W_BL(1);//高电平打开背光
    LCD_W_CS(0);// CS = 0,使能LCD，必要性存疑

    LCD_WriteCommand16(0x0000);  //exiting from deep standby mode
    LCD_delay(10);    //spec 1ms
    LCD_WriteCommand16(0x0000);
    LCD_delay(10);    //spec 1ms
    LCD_WriteCommand16(0x0000);
    LCD_delay(10);    //spec 1ms


    LCD_WriteCommand16(0x05ff);
    LCD_WriteData16(0x0000);
    LCD_WriteCommand16(0x001d);  //mode setting
    LCD_WriteData16(0x0005);  //exit standby
    LCD_delay(100);    //spec 1ms

    LCD_WriteCommand16(0x0000);  //oscillation setting
    LCD_WriteData16(0x0001);  //set to on
    LCD_delay(100);
    //Display control
    LCD_WriteCommand16(0x0001);  //Driver output control
    LCD_WriteData16(0x0027);  //SS=0
    LCD_WriteCommand16(0x0002);  //LCD driver AC control
    LCD_WriteData16(0x0200);  //line inversion
    LCD_WriteCommand16(0x0003);  //Entry mode
//    LCD_WriteData(0x0038);//steward-fu（司徒）的代码
    LCD_WriteData16(0x0020);  //ID=10

    LCD_WriteCommand16(0x0007);  //Display mode
    LCD_WriteData16(0x4004);    //262K Colors, normal drive
    LCD_WriteCommand16(0x000d);  //FR period adjustment setting
    LCD_WriteData16(0x0011);  //Ffr=60Hz optimized
    LCD_delay(100);

    //LTPS control settings
    LCD_WriteCommand16(0x0012);  //LTPS control setting 1
    LCD_WriteData16(0x0303);
    LCD_WriteCommand16(0x0013);  //LTPS control setting 2
    LCD_WriteData16(0x0102);
    LCD_WriteCommand16(0x001c);  //Ampl
    LCD_WriteData16(0x0000);  //AMP

//Power settings
    LCD_WriteCommand16(0x0102);  //Powe
    LCD_WriteData16(0x00f6);    //VCOM
    LCD_delay(500);

    LCD_WriteCommand16(0x0103);  //Powe
    LCD_WriteData16(0x0007);    //XVDD
    LCD_delay(100);

    LCD_WriteCommand16(0x0105);  //Powe
    LCD_WriteData16(0x0111);
    LCD_delay(100);

//Gray scale settings (gamma c
    LCD_WriteCommand16(0x0300);
    LCD_WriteData16(0x0200);    //chan
    LCD_WriteCommand16(0x0301);
    LCD_WriteData16(0x0002);  //
    LCD_WriteCommand16(0x0302);
    LCD_WriteData16(0x0000);
    LCD_WriteCommand16(0x0303);
    LCD_WriteData16(0x0300);  //
    LCD_WriteCommand16(0x0304);
    LCD_WriteData16(0x0700);
    LCD_WriteCommand16(0x0305);
    LCD_WriteData16(0x0070);  //


    LCD_WriteCommand16(0x0402);  //First screen s
    LCD_WriteData16(0x0000);  //0
    LCD_WriteCommand16(0x0403);  //First screen e
    LCD_WriteData16(0x013f);  //319

//	WriteComm(0x0404);  //First screen s
//  WriteData(10);  //0
//  WriteComm(0x0405);  //First screen e
//  WriteData(2);  //319

    LCD_WriteCommand16(0x0406);  //Hor. window start
    LCD_WriteData16(0x0000);  //0
    LCD_WriteCommand16(0x0407);  //Hor. window end ad
    LCD_WriteData16(0x00ef);  //239
    LCD_WriteCommand16(0x0408);  //Ver. window start
    LCD_WriteData16(0x0000);  //0
    LCD_WriteCommand16(0x0409);  //Ver. window end ad
    LCD_WriteData16(0x013f);  //319

    LCD_WriteCommand16(0x0200);  //Y start address se
    LCD_WriteData16(0x0000);  //0，steward-fu（司徒）的代码
//    LCD_WriteData(0x00ef);  //239
    LCD_WriteCommand16(0x0201);  //X start address se
    LCD_WriteData16(0x0000);  //0

    LCD_WriteCommand16(0x0100);
    LCD_WriteData16(0xC010);
    LCD_delay(500);
    LCD_WriteCommand16(0x0101);
    LCD_WriteData16(0x0001);
    LCD_WriteCommand16(0x0100);
    LCD_WriteData16(0xF7FE);
    LCD_delay(800);

    LCD_WriteCommand16(0x0003);  //Entry mode
    LCD_WriteData16(0x0038);  //ID=10 切换到横屏显示

    //竖屏显示
//    Lcd_Light_ON;
//    LCD_WriteCommand16(0x0001);
//    LCD_WriteData16(0x005a);//旋转物理坐标
//    LCD_WriteCommand16(0x0003);//Transfer mode
//    LCD_WriteData16(0x000);//旋转方向

    //下方代码恒为注释
//WriteComm(0x3A); WriteData(0x55);//55是565，也就是16位；66是666，也就是18位，77则是888，即24位(注意：需要能支持24位的液晶屏才可设置77)
//WriteComm(0x36); WriteData(0xA0);// D3位取反，RGB中RB交换；D5位取反，是切换横竖屏；D6，D7位是x与y轴的镜像

//    LCD_Clear(LCD_ColorHEX("#000000"));//将屏幕刷黑 todo
    //更进一步的，可以把屏幕刷黑再打开背光
}
/*********************硬件配置*/

/*底层函数*********************/


/**
  * @brief  LCD设置光标起点定位
  * @param  x:0~239
  * @param  y:0~319
  * @retval None
  * @note   设置光标即为初始点
  */
void LCD_SetCursor(uint16_t x,uint16_t y)
{
    //坐标调转
    LCD_WriteReg(0x20,y);//水平坐标
    LCD_WriteReg(0x21,x);//垂直坐标
}


/**
  * @brief  LCD开窗
  * @param  Xstart:0~319
  * @param  Xend:0~319
  * @param  Ystart:0~239
  * @param  Yend:0~239
  * @retval None
  * @note   开一个矩形框，方便接下来往这个框填充数据
  */
void LCD_SetZone(uint16_t Xstart, uint16_t Ystart, uint16_t Xend, uint16_t Yend)
{
//下面注释掉以免有地方无法操作
//    Ystart+=16;//竖屏
//    Yend+=16;

    //x与y 坐标交换实现横屏而不增加运行时间
    LCD_WriteCommand16(0x0406);
    LCD_WriteData16(Ystart); // windows address
    LCD_WriteCommand16(0x0407);
    LCD_WriteData16(Yend);

    LCD_WriteCommand16(0x0408);
    LCD_WriteData16(Xstart);
    LCD_WriteCommand16(0x0409);
    LCD_WriteData16(Xend);

    LCD_WriteCommand16(0x0200); 	//HS
    LCD_WriteData16(Ystart);

    LCD_WriteCommand16(0x0201);  //VS
    LCD_WriteData16(Xstart);

    LCD_WriteCommand16(0x0202);  // write ram
}


/**
  * @brief  LCD填充一个矩形
  * @param  Xstart:0~319
  * @param  Ystart:0~239
  * @param  xLong:0~319
  * @param  yLong:0~239
  * @param  Color:16位TFT_Color
  * @retval None
  * @note   开一个矩形框，方便接下来往这个框填充数据
  */
void LCD_Fill(uint16_t Xstart,uint16_t Ystart,uint16_t Xend,uint16_t Yend,uint16_t TFT_Color)
{
//    方案1：全程模拟时序
//    uint32_t temp;
//    LCD_SetZone(Xstart,Ystart,Xend,Yend);
//    LCD_W_DC(1);//1表示写入数据
//    LCD_W_CS(0);//0表示片选选中
//    for (temp=0; temp<(Xend-Xstart)*(Yend-Ystart); temp++)
//    {
//        GPIOA->ODR = Color>>8;    //写入16位颜色高8位，51单片机写法：P1=Color;
//        LCD_W_WR(0);//模拟上升沿移入数据
//        LCD_W_WR(1);
//
//        GPIOA->ODR = Color;    //写入16位颜色低8位，51单片机写法：P1=Color;
//        LCD_W_WR(0);//模拟上升沿移入数据
//        LCD_W_WR(1);
//    }
//    LCD_W_CS(1);//片选结束


//    //方案2：基于现有函数构建
    uint16_t i,j;
    LCD_SetZone(Xstart,Ystart,Xend,Yend);
    for(i=0;i<(Yend-Ystart);i++)
    {
        for (j=0;j<(Xend-Xstart);j++)
        {
            LCD_WriteData16(TFT_Color);
        }
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
//    LCD_SetZone(0, 0, LCD_W - 1, LCD_H - 1);
    LCD_SetZone(0, 0, LCD_W - 1, LCD_H - 1);
    for(i=0;i<LCD_W;i++)
    {
        for (j=0;j<LCD_H;j++)
        {
            LCD_WriteData16(TFT_Color);
        }
    }

}


/**
  * @brief  LCD填充一个矩形
  * @param  Xstart:0~319
  * @param  Ystart:0~239
  * @param  xLong:0~319
  * @param  yLong:0~239
  * @param  Color:16位TFT_Color
  * @retval None
  * @note   开一个矩形框，方便接下来往这个框填充数据
  */
void Lcd_ColorBox(uint16_t xStart,uint16_t yStart,uint16_t xLong,uint16_t yLong,uint16_t Color)
{
    //方案1：全程模拟时序
//    uint32_t temp;
//    BlockWrite(xStart,xStart+xLong-1,yStart,yStart+yLong-1);
//    LCD_W_DC(1);//1表示写入数据
//    LCD_W_CS(0);//0表示片选选中
//    for (temp=0; temp<xLong*yLong; temp++)
//    {
//        GPIOA->ODR = Color>>8;    //写入16位颜色高8位，51单片机写法：P1=Color;
//        LCD_W_WR(0);//模拟上升沿移入数据
//        LCD_W_WR(1);
//
//        GPIOA->ODR = Color;    //写入16位颜色低8位，51单片机写法：P1=Color;
//        LCD_W_WR(0);//模拟上升沿移入数据
//        LCD_W_WR(1);
//    }
//    LCD_W_CS(1);//片选结束


    //方案2：基于现有函数构建
    uint32_t temp;
    LCD_SetZone(xStart, xStart + xLong - 1, yStart, yStart + yLong - 1);
    for (temp=0; temp<xLong*yLong; temp++)
    {
        LCD_WriteData16(Color);
    }

}

/**
  * @brief  LCD画点函数
  * @param  X 指定区域左上角的横坐标，范围：0~127
  * @param  Y 指定区域左上角的纵坐标，范围：0~63
  * @param  Color:16位TFT_Color
  * @retval None
  * @note   在x，y 坐标上打一个颜色为Color的点
  */
void LCD_DrawPoint(uint16_t X, uint16_t Y, uint16_t Color)
{
    LCD_WriteCommand16(0x0200); 	//HS
    LCD_WriteData16(Y);

    LCD_WriteCommand16(0x0201);  //VS
    LCD_WriteData16(X);

    LCD_WriteCommand16(0x0202);  // write ram
    LCD_W_CS(0);
    LCD_W_DC(1);//1表示写入数据
    GPIOA->ODR = Color>>8;    //写入16位颜色高8位，51单片机写法：P1=Color;
    LCD_W_WR(0);
    LCD_W_WR(1);
    GPIOA->ODR = Color;    //写入16位颜色低8位，51单片机写法：P1=Color;
    LCD_W_WR(0);
    LCD_W_WR(1);
    LCD_W_CS(1);
}

/*********************底层函数*/

#endif
