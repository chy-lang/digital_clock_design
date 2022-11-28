#include "stm32f10x_exti.h"
#include "exti.h"
#include "led.h"
#include "key.h"
#include "delay.h"
#include "usart.h"
#include "mylcd.h"
#include "common.h"


//////////////////////////////////////////////////////////////////////////////////	 
//������ֻ��ѧϰʹ�ã�δ��������ɣ��������������κ���;
//ALIENTEKս��STM32������
//�ⲿ�ж� ��������	   
//����ԭ��@ALIENTEK
//������̳:www.openedv.com
//�޸�����:2012/9/3
//�汾��V1.0
//��Ȩ���У�����ؾ���
//Copyright(C) ������������ӿƼ����޹�˾ 2009-2019
//All rights reserved									  
//////////////////////////////////////////////////////////////////////////////////   
//�ⲿ�ж�0�������
	 u8 Temp[2], Humidity[2];
void EXTIX_Init(void)
{
 
 	EXTI_InitTypeDef EXTI_InitStructure;
 	NVIC_InitTypeDef NVIC_InitStructure;

    KEY_Init();	 //	�����˿ڳ�ʼ��

  	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);	//ʹ�ܸ��ù���ʱ��

   //GPIOA.0|1	  �ж����Լ��жϳ�ʼ������ �����ش��� PA0  WK_UP
 	 GPIO_EXTILineConfig(GPIO_PortSourceGPIOA,GPIO_PinSource0); 

  	EXTI_InitStructure.EXTI_Line=EXTI_Line0;
		EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;	
		EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
		EXTI_InitStructure.EXTI_LineCmd = ENABLE;
  	EXTI_Init(&EXTI_InitStructure);		//����EXTI_InitStruct��ָ���Ĳ�����ʼ������EXTI�Ĵ���


  	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;			//ʹ�ܰ���WK_UP���ڵ��ⲿ�ж�ͨ��
  	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 0x02;	//��ռ���ȼ�2�� 
  	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 0x03;					//�����ȼ�3
  	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;								//ʹ���ⲿ�ж�ͨ��
  	NVIC_Init(&NVIC_InitStructure);  
}

//�ⲿ�ж�0������� 
void EXTI0_IRQHandler(void)
{
	u16 sum1,sum2;
	u8 Temperature;
	u8 humidity;
	u8 week[4];
	u8 day[3];
	u8 month[4];
	u8 year[5];
	u8 i;
	u8 time[9];
	delay_ms(10);//����
	if(WK_UP==0)	 	 //WK_UP����
	{
		sum1 = Temp[0]*256+Temp[1];
		Temperature = -45+175*sum1/65535;
	  sum2 = Humidity[0]*256+Humidity[1];
		humidity = 100*sum2/65524;
		printf("%s\n",mystr);
		week[0] = mystr[6];
		week[1] = mystr[7];
		week[2] = mystr[8];
		week[3] = 0;
		day[0] = mystr[11];
		day[1] = mystr[12]; 
		day[2] = 0;
    month[0] = mystr[14];
    month[1] = mystr[15];
    month[2] = mystr[16];
    month[3] = 0;
    year[0] = mystr[18];
    year[1] = mystr[19];
    year[2] = mystr[20];
    year[3] = mystr[21];
    year[4] = 0;
    for(i=0;i<8;i++){
			time[i] = mystr[23+i];
		}
		time[i] = 0;
		myLCD_Clear(BLACK);
		myLCD_ShowString(42,30,"week:",WHITE);myLCD_ShowString(80,30,week,WHITE);
		myLCD_ShowString(42,50,"day:",WHITE);myLCD_ShowString(75,50,day,WHITE);
		myLCD_ShowString(42,70,"month:",WHITE);myLCD_ShowString(90,70,month,WHITE);
		myLCD_ShowString(42,90,"year:",WHITE);myLCD_ShowString(80,90,year,WHITE);
		myLCD_ShowString(42,110,"time:",WHITE);myLCD_ShowString(80,110,time,WHITE);
		myLCD_ShowString(42,130,"TEMP:",WHITE);myLCD_ShowNum(80,130,Temperature,2,WHITE);
		myLCD_ShowString(42,150,"HUM:",WHITE);myLCD_ShowNum(75,150,humidity,2,WHITE);
		for(i=0;i<8;i++){
	  delay_ms(1000);
    }			
		printf("%s\r\n",week);
		printf("%s\r\n",day);
		printf("%s\r\n",month);
		printf("%s\r\n",year);
		printf("%s\r\n",time);
//		printf("%s",mystr);
//		printf("TEMP %x %x \r\n",Temp[0],Temp[1]);
//		printf("HUMIDITY %x %x \r\n",Humidity[0],Humidity[1]);
	}
	myLCD_Clear(BLACK);
	myLCD_ShowString(22,60,"Waiting for command",WHITE);
	EXTI_ClearITPendingBit(EXTI_Line0); //���LINE0�ϵ��жϱ�־λ  
}
 

 
