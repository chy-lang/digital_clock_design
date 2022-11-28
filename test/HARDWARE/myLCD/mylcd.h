/////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////              深圳市沃乐康科技有限公司                               //////////////////
///////////////////              0755-32882855                                        //////////////////
///////////////////              https://ourplaza.taobao.com/                         //////////////////
///////////////////              版权所有  仅用于学习参考                              //////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////

#ifndef __myLCD_H
#define __myLCD_H		


#include "sys.h"
#include "stdlib.h"	  


#define USE_HORIZONTAL 0  //设置横屏或者竖屏显示 0或1为竖屏 2或3为横屏

#if USE_HORIZONTAL==0||USE_HORIZONTAL==1
#define myLCD_W 240
#define myLCD_H 240

#else
#define myLCD_W 240
#define myLCD_H 240
#endif


#define	u8 unsigned char
#define	u16 unsigned int
#define	u32 unsigned long

   			

//-----------------端口定义---------------- 

#define LED_ON GPIO_ResetBits(GPIOD,GPIO_Pin_2)
#define LED_OFF GPIO_SetBits(GPIOD,GPIO_Pin_2)

//-----------------OLED端口定义---------------- 

#define myLCD_SCLK_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_13)//SCL
#define myLCD_SCLK_Set() GPIO_SetBits(GPIOB,GPIO_Pin_13)

#define myLCD_SDIN_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_15)//DIN
#define myLCD_SDIN_Set() GPIO_SetBits(GPIOB,GPIO_Pin_15)

#define myLCD_RST_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_11)//RES
#define myLCD_RST_Set() GPIO_SetBits(GPIOB,GPIO_Pin_11)

#define myLCD_DC_Clr() GPIO_ResetBits(GPIOB,GPIO_Pin_14)//DC      pb14
#define myLCD_DC_Set() GPIO_SetBits(GPIOB,GPIO_Pin_14)
 		     
#define myLCD_CS_Clr()  GPIO_ResetBits(GPIOB,GPIO_Pin_12)//CS
#define myLCD_CS_Set()  GPIO_SetBits(GPIOB,GPIO_Pin_12)

#define myLCD_BLK_Clr()  GPIO_ResetBits(GPIOB,GPIO_Pin_10)//BLK    ///pb1
#define myLCD_BLK_Set()  GPIO_SetBits(GPIOB,GPIO_Pin_10)


#define myLCD_CMD  0	//写命令
#define myLCD_DATA 1	//写数据

extern  u16 BACK_COLOR;   //背景色

void myLCD_Writ_Bus(u8 dat);
void myLCD_WR_DATA8(u8 dat);
void myLCD_WR_DATA(u16 dat);
void myLCD_WR_REG(u8 dat);
void myLCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2);
void Lcd_Init(void);
void myLCD_Clear(u16 Color);
void myLCD_DispBand(void);
void myLCD_DispGrayHor16(void);
void myLCD_DispSnow(void);
void myLCD_DispBlock(void);
void myLCD_ShowChinese(u16 x,u16 y,u8 index,u8 size,u16 color);
void myLCD_DrawPoint(u16 x,u16 y,u16 color);
void myLCD_DrawPoint_big(u16 x,u16 y,u16 color);
void myLCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color);
void myLCD_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color);
void myLCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color);
void Draw_Circle(u16 x0,u16 y0,u8 r,u16 color);
//void myLCD_ShowChar(u16 x,u16 y,u8 num,u8 mode,u16 color);
void myLCD_ShowString(u16 x,u16 y,const u8 *p,u16 color);
u32 mypow(u8 m,u8 n);
void myLCD_ShowNum(u16 x,u16 y,u16 num,u8 len,u16 color);
void myLCD_ShowNum1(u16 x,u16 y,float num,u8 len,u16 color);
void myLCD_ShowPicture(u16 x1,u16 y1,u16 x2,u16 y2);


//画笔颜色
#define WHITE         	 0xFFFF
#define BLACK         	 0x0000	  
#define BLUE           	 0x001F  
#define BRED             0XF81F
#define GRED 			       0XFFE0
#define GBLUE			       0X07FF
#define RED           	 0xF800
#define MAGENTA       	 0xF81F
#define GREEN         	 0x07E0
#define CYAN          	 0x7FFF
#define YELLOW        	 0xFFE0
#define BROWN 			     0XBC40 //棕色
#define BRRED 			     0XFC07 //棕红色
#define GRAY  			     0X8430 //灰色
//GUI颜色

#define DARKBLUE      	 0X01CF	//深蓝色
#define LIGHTBLUE      	 0X7D7C	//浅蓝色  
#define GRAYBLUE       	 0X5458 //灰蓝色
//以上三色为PANEL的颜色 
 
#define LIGHTGREEN     	 0X841F //浅绿色
#define LGRAY 			     0XC618 //浅灰色(PANNEL),窗体背景色

#define LGRAYBLUE        0XA651 //浅灰蓝色(中间层颜色)
#define LBBLUE           0X2B12 //浅棕蓝色(选择条目的反色)


					  		 
#endif  
	 
	 



