#include "led.h"
#include "delay.h"
#include "sys.h"
#include "usart.h"
#include "lcd.h"
#include "key.h"
#include "usmart.h" 
#include "malloc.h"  
#include "MMC_SD.h" 
#include "ff.h"  
#include "exfuns.h"
#include "fontupd.h"
#include "text.h"	
#include "common.h" 
#include "touch.h"	
#include "mylcd.h"
#include "usart2.h"
#include "exti.h"
#include "24cxx.h" 

//ALIENTEK Mini STM32开发板扩展实验15
//ATK-RM04 WIFI模块测试实验
//技术支持：www.openedv.com
//广州市星翼电子科技有限公司  
 
 
 int main(void)
 { 
	 u16 t,len;
	 u8* str[20];
	 delay_init();
   NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);	 
	 uart_init(115200);
	 USART2_Init(115200);
	 Lcd_Init();
	 KEY_Init();
	 EXTIX_Init();
	 IIC_Init();
	 myLCD_Clear(BLACK);
	 myLCD_ShowString(42,60,"Initializing...",WHITE);
	 my_atk_8266_wifista_config();
	 myLCD_ShowString(42,60,"Waiting for command",WHITE);

	 while(1){
		 SHT31_Getdata(Temp, Humidity);
		 get_time();
		 myLCD_ShowString(42,80,"time:",WHITE);myLCD_ShowString(80,80,Time,WHITE);
		 }
}
 
























