/////////////////////////////////////////////////////////////////////////////////////////////////////////
///////////////////              ���������ֿ��Ƽ����޹�˾                               //////////////////
///////////////////              0755-32882855                                        //////////////////
///////////////////              https://ourplaza.taobao.com/                         //////////////////
///////////////////              ��Ȩ����  ������ѧϰ�ο�                              //////////////////
///////////////////////////////////////////////////////////////////////////////////////////////////////
#include "mylcd.h"
#include "lcdfont.h"
#include "delay.h"
#include "stm32f10x_spi.h"
u16 myBACK_COLOR;   //����ɫ


/******************************************************************************
      ����˵����myLCD��������д�뺯��
      ������ݣ�dat  Ҫд��Ĵ�������
      ����ֵ��  ��
******************************************************************************/
void myLCD_Writ_Bus(u8 dat) 
{	
	u8 i;
	myLCD_CS_Clr();
	for(i=0;i<8;i++)
	{			  
		myLCD_SCLK_Clr();
		if(dat&0x80)
		   myLCD_SDIN_Set();
		else
		   myLCD_SDIN_Clr();
		myLCD_SCLK_Set();
		dat<<=1;
	}	
  myLCD_CS_Set();	
}

/******************************************************************************
      ����˵����Ӳ��SPI
      ������ݣ�dat  Ҫд��Ĵ�������
      ����ֵ��  ��
******************************************************************************/
void myLCD_SPIWrit_Bus(u8 dat) 
{	
	 //while(!SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE));
	SPI_I2S_SendData(SPI2,dat);
	while(!SPI_I2S_GetFlagStatus(SPI2,SPI_I2S_FLAG_TXE));

}

/******************************************************************************
      ����˵����myLCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void myLCD_WR_REG(u8 dat)
{
	myLCD_CS_Clr();
	myLCD_DC_Clr();//д����
	//myLCD_Writ_Bus(dat);
	myLCD_SPIWrit_Bus(dat);
	
	myLCD_CS_Set();
}

/******************************************************************************
      ����˵����myLCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void myLCD_WR_DATA8(u8 dat)
{
	myLCD_CS_Clr();
	myLCD_DC_Set();//д����
	//myLCD_Writ_Bus(dat);
	myLCD_SPIWrit_Bus(dat);
	//delay_ms(1);
	myLCD_CS_Set();
}


/******************************************************************************
      ����˵����myLCDд������
      ������ݣ�dat д�������
      ����ֵ��  ��
******************************************************************************/
void myLCD_WR_DATA(u16 dat)
{
	myLCD_CS_Clr();
	myLCD_DC_Set();//д����
	myLCD_SPIWrit_Bus(dat>>8);
	myLCD_SPIWrit_Bus(dat);
	myLCD_CS_Set();
}



/******************************************************************************
      ����˵����������ʼ�ͽ�����ַ
      ������ݣ�x1,x2 �����е���ʼ�ͽ�����ַ
                y1,y2 �����е���ʼ�ͽ�����ַ
      ����ֵ��  ��
******************************************************************************/
void myLCD_Address_Set(u16 x1,u16 y1,u16 x2,u16 y2)
{
	
	
	
	if(USE_HORIZONTAL==0)
	{
		myLCD_WR_REG(0x2a);//�е�ַ����
		myLCD_WR_DATA(x1);
		myLCD_WR_DATA(x2);
		myLCD_WR_REG(0x2b);//�е�ַ����
		myLCD_WR_DATA(y1);
		myLCD_WR_DATA(y2);
		myLCD_WR_REG(0x2c);//������д
	}
	else if(USE_HORIZONTAL==1)
	{
		y1=y1+40;
	y2=y2+40;
		
		myLCD_WR_REG(0x2a);//�е�ַ����
		myLCD_WR_DATA(x1);
		myLCD_WR_DATA(x2);
		myLCD_WR_REG(0x2b);//�е�ַ����
		myLCD_WR_DATA(y1);
		myLCD_WR_DATA(y2);
		myLCD_WR_REG(0x2c);//������д
	}
	else if(USE_HORIZONTAL==2)
	{
		myLCD_WR_REG(0x2a);//�е�ַ����
		myLCD_WR_DATA(x1);
		myLCD_WR_DATA(x2);
		myLCD_WR_REG(0x2b);//�е�ַ����
		myLCD_WR_DATA(y1);
		myLCD_WR_DATA(y2);
		myLCD_WR_REG(0x2c);//������д
	}
	else
	{
		myLCD_WR_REG(0x2a);//�е�ַ����
		myLCD_WR_DATA(x1);
		myLCD_WR_DATA(x2);
		myLCD_WR_REG(0x2b);//�е�ַ����
		myLCD_WR_DATA(y1);
		myLCD_WR_DATA(y2);
		myLCD_WR_REG(0x2c);//������д
	}
}


void Hardware_SPI_Init(void)
{
///////��ʼ��SPI�˿�////////////////
	SPI_InitTypeDef SPI_InitStructure;
	
	
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_SPI2,ENABLE);	 //ʹ��SPI2�˿�ʱ��
	
	
	SPI_InitStructure.SPI_NSS = SPI_NSS_Soft;
	SPI_InitStructure.SPI_CPHA = SPI_CPHA_1Edge;
	SPI_InitStructure.SPI_CPOL = SPI_CPOL_Low;
	SPI_InitStructure.SPI_Mode = SPI_Mode_Master;
	SPI_InitStructure.SPI_DataSize = SPI_DataSize_8b;
	SPI_InitStructure.SPI_FirstBit = SPI_FirstBit_MSB;
	//SPI_InitStructure.SPI_Direction = SPI_Direction_2Lines_FullDuplex;
	SPI_InitStructure.SPI_Direction = SPI_Direction_1Line_Tx;
	SPI_InitStructure.SPI_CRCPolynomial = 7;
	SPI_InitStructure.SPI_BaudRatePrescaler = SPI_BaudRatePrescaler_2;
	
	SPI_Init(SPI2,&SPI_InitStructure);
	//SPI_Init(SPI2,&amp;SPI_InitStructure);
	
	SPI_Cmd(SPI2,ENABLE);
}

void STM_Port_Init(void)
{
	GPIO_InitTypeDef  GPIO_InitStructure;

	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��B�˿�ʱ��
	
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_12|GPIO_Pin_11|GPIO_Pin_14;	 //PB13-SCK PB15-SDA PB11-RESET PB12-CS PB14-RS 
 	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);	 //ʹ��A�˿�ʱ��
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13|GPIO_Pin_15;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_AF_PP;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_14;
	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	//GPIO_Init(GPIOB,&GPIO_InitStructure);
	
  myLCD_CS_Set();
}
/******************************************************************************
      ����˵����myLCD��ʼ������
      ������ݣ���
      ����ֵ��  ��
******************************************************************************/
void Lcd_Init(void)
{
	

	STM_Port_Init();
	Hardware_SPI_Init();
	myLCD_CS_Set();
	myLCD_RST_Set();
	myLCD_DC_Set();
		
	//RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOD, ENABLE);	 //ʹ��D�˿�ʱ��
	//GPIO_InitStructure.GPIO_Pin = GPIO_Pin_2;	 
 	//GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP; 		 //�������
	//GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;//�ٶ�50MHz
 	//GPIO_Init(GPIOD, &GPIO_InitStructure);	 
 	//GPIO_SetBits(GPIOD,GPIO_Pin_2);

	myLCD_RST_Clr();
	delay_ms(20);
	myLCD_RST_Set();
	delay_ms(100);
	myLCD_BLK_Set();
	
myLCD_WR_REG(0x11);              
delay_ms(120); 

myLCD_WR_REG(0x36); //MX, MY, RGB mode 
if(USE_HORIZONTAL==0)myLCD_WR_DATA8(0x00);
else if(USE_HORIZONTAL==1)myLCD_WR_DATA8(0xC0);
else if(USE_HORIZONTAL==2)myLCD_WR_DATA8(0x70);
else myLCD_WR_DATA8(0xA0);

myLCD_WR_REG(0x3A);			
myLCD_WR_DATA8(0x55);   //   5 565  6 666

myLCD_WR_REG(0xB2);			
myLCD_WR_DATA8(0x0C);
myLCD_WR_DATA8(0x0C); 
myLCD_WR_DATA8(0x00); 
myLCD_WR_DATA8(0x33); 
myLCD_WR_DATA8(0x33); 			

myLCD_WR_REG(0xB7);			
myLCD_WR_DATA8(0x35);

myLCD_WR_REG(0xBB);			
myLCD_WR_DATA8(0x32); //Vcom=1.35V
												  	
myLCD_WR_REG(0xC2);			
myLCD_WR_DATA8(0x01);

myLCD_WR_REG(0xC3);			
myLCD_WR_DATA8(0x19); //GVDD=4.8V 
													  
myLCD_WR_REG(0xC4);			
myLCD_WR_DATA8(0x20); //VDV, 0x20:0v

myLCD_WR_REG(0xC6);			
myLCD_WR_DATA8(0x0F); //0x0F:60Hz        	

myLCD_WR_REG(0xD0);			
myLCD_WR_DATA8(0xA4);
myLCD_WR_DATA8(0xA1); 											  												  																								
	    
myLCD_WR_REG(0xE0);     
myLCD_WR_DATA8(0xD0);   
myLCD_WR_DATA8(0x08);   
myLCD_WR_DATA8(0x0E);   
myLCD_WR_DATA8(0x09);   
myLCD_WR_DATA8(0x09);   
myLCD_WR_DATA8(0x05);   
myLCD_WR_DATA8(0x31);   
myLCD_WR_DATA8(0x33);   
myLCD_WR_DATA8(0x48);   
myLCD_WR_DATA8(0x17);   
myLCD_WR_DATA8(0x14);   
myLCD_WR_DATA8(0x15);   
myLCD_WR_DATA8(0x31);   
myLCD_WR_DATA8(0x34);   

myLCD_WR_REG(0xE1);     
myLCD_WR_DATA8(0xD0);   
myLCD_WR_DATA8(0x08);   
myLCD_WR_DATA8(0x0E);   
myLCD_WR_DATA8(0x09);   
myLCD_WR_DATA8(0x09);   
myLCD_WR_DATA8(0x15);   
myLCD_WR_DATA8(0x31);   
myLCD_WR_DATA8(0x33);   
myLCD_WR_DATA8(0x48);   
myLCD_WR_DATA8(0x17);   
myLCD_WR_DATA8(0x14);   
myLCD_WR_DATA8(0x15);   
myLCD_WR_DATA8(0x31);   
myLCD_WR_DATA8(0x34);   


myLCD_WR_REG(0x21);

myLCD_WR_REG(0x2A); //Column Address Set
myLCD_WR_DATA8(0x00);
myLCD_WR_DATA8(0x00); //0
myLCD_WR_DATA8(0x00);
myLCD_WR_DATA8(0xEF); //239

myLCD_WR_REG(0x2B); //Row Address Set
myLCD_WR_DATA8(0x00);
myLCD_WR_DATA8(0x00); //0
myLCD_WR_DATA8(0x00);
myLCD_WR_DATA8(0xEF); //239

myLCD_WR_REG(0x29);


} 


/******************************************************************************
      ����˵����myLCD��������
      ������ݣ���
      ����ֵ��  ��
******************************************************************************/
void myLCD_Clear(u16 Color)
{
	u16 i,j;  	
	myLCD_Address_Set(0,0,myLCD_W-1,myLCD_H-1);
    for(i=0;i<myLCD_W;i++)
	  {
			for (j=0;j<myLCD_H;j++)
				{
					myLCD_WR_DATA(Color);
				}
	  }
}

/******************************************************************************
      ����˵����myLCD��ʾ��������
      ������ݣ���
      ����ֵ��  ��
******************************************************************************/
void myLCD_DispBand(void)
{
	u16 i,j,k;  	
	unsigned int color[8]={0x001f,0x07e0,0xf800,0x07ff,0xf81f,0xffe0,0x0000,0xffff};
	
	myLCD_Address_Set(0,0,myLCD_W-1,myLCD_H-1);
	
	for(i=0;i<8;i++)
	{
	   for(j=0;j<myLCD_H/8;j++)
		 {
		   for(k=0;k<myLCD_W;k++)
			 {
			  myLCD_WR_DATA(color[i]);
			 }
		 }
	}
	for(j=0;j<myLCD_H%8;j++)
	{
	 for(k=0;k<myLCD_W;k++)
		{myLCD_WR_DATA(color[7]);}
	}
	
    
}

/******************************************************************************
      ����˵����myLCD��ʾ�ҽ׺���
      ������ݣ���
      ����ֵ��  ��
******************************************************************************/
void myLCD_DispGrayHor16(void)
{
	u16 i,j,k;  	
	
	myLCD_Address_Set(0,0,myLCD_W-1,myLCD_H-1);
	
	for(i=0;i<myLCD_H;i++)
	{
	  for(j=0;j<myLCD_W%8;j++)
		{myLCD_WR_DATA(0);}
		
		for(j=0;j<16;j++)
		{
		  for(k=0;k<myLCD_W/16;k++)
			{
			  myLCD_WR_DATA8(((j*2)<<3)|((j*4)>>3));
				myLCD_WR_DATA8(((j*4)<<5)|(j*2));
			}
		}
	}
	
    
}

/******************************************************************************
      ����˵����myLCD��ʾѩ������
      ������ݣ���
      ����ֵ��  ��
******************************************************************************/
void myLCD_DispSnow(void)
{
	u16 i,j;  
  u16 dat;	
	
	myLCD_Address_Set(0,0,myLCD_W-1,myLCD_H-1);
	dat=0;
	
	for(i=0;i<myLCD_H;i++)
	{
	  for(j=0;j<myLCD_W/2;j++)
		{myLCD_WR_DATA(dat);
		 myLCD_WR_DATA(~dat);}
		dat=~dat;
	}  
}

/******************************************************************************
      ����˵����myLCD��ʾ���麯��
      ������ݣ���
      ����ֵ��  ��
******************************************************************************/
void myLCD_DispBlock(void)
{
	u16 i,j,k;  
  k=myLCD_H/4;
	
	myLCD_Address_Set(0,0,myLCD_W-1,myLCD_H-1);
	
	for(i=0;i<k;i++)
	{
	  for(j=0;j<myLCD_W;j++)
		{myLCD_WR_DATA(0x7bef);}
	}  
	for(i=0;i<k*2;i++)
	 {
	  for(j=0;j<myLCD_W/4;j++)
		 {myLCD_WR_DATA(0x7bef);}
		for(j=0;j<myLCD_W/2;j++)
		 {myLCD_WR_DATA(0);}
		for(j=0;j<myLCD_W/4;j++)
		 {myLCD_WR_DATA(0x7bef);}
	 }
	 for(i=0;i<k;i++)
	 {
	   for(j=0;j<myLCD_W;j++)
		{myLCD_WR_DATA(0x7bef);}
	 }
}


/******************************************************************************
      ����˵����myLCD��ʾ����
      ������ݣ�x,y   ��ʼ����
                index ���ֵ����
                size  �ֺ�
      ����ֵ��  ��
******************************************************************************/
void myLCD_ShowChinese(u16 x,u16 y,u8 index,u8 size,u16 color)	
{  
	u8 i,j;
	u8 *temp,size1;
	if(size==16){temp=Hzk16;}//ѡ���ֺ�
	if(size==32){temp=Hzk32;}
  myLCD_Address_Set(x,y,x+size-1,y+size-1); //����һ�����ֵ�����
  size1=size*size/8;//һ��������ռ���ֽ�
	temp+=index*size1;//д�����ʼλ��
	for(j=0;j<size1;j++)
	{
		for(i=0;i<8;i++)
		{
		 	if((*temp&(1<<i))!=0)//�����ݵĵ�λ��ʼ��
			{
				myLCD_WR_DATA(color);//����
			}
			else
			{
				myLCD_WR_DATA(myBACK_COLOR);//������
			}
		}
		temp++;
	 }
}
/******************************************************************************
      ����˵����myLCD��ʾ����
      ������ݣ�x,y   ��ʼ����
      ����ֵ��  ��
******************************************************************************/
void myLCD_DrawPoint(u16 x,u16 y,u16 color)
{
	myLCD_Address_Set(x,y,x,y);//���ù��λ�� 
	myLCD_WR_DATA(color);
} 
/******************************************************************************
      ����˵����myLCD��һ����ĵ�
      ������ݣ�x,y   ��ʼ����
      ����ֵ��  ��
******************************************************************************/
void myLCD_DrawPoint_big(u16 x,u16 y,u16 color)
{
	myLCD_Fill(x-1,y-1,x+1,y+1,color);
} 
/******************************************************************************
      ����˵������ָ�����������ɫ
      ������ݣ�xsta,ysta   ��ʼ����
                xend,yend   ��ֹ����
      ����ֵ��  ��
******************************************************************************/
void myLCD_Fill(u16 xsta,u16 ysta,u16 xend,u16 yend,u16 color)
{          
	u16 i,j; 
	myLCD_Address_Set(xsta,ysta,xend,yend);      //���ù��λ�� 
	for(i=ysta;i<=yend;i++)
	{													   	 	
		for(j=xsta;j<=xend;j++)myLCD_WR_DATA(color);//���ù��λ�� 	    
	} 					  	    
}
/******************************************************************************
      ����˵��������
      ������ݣ�x1,y1   ��ʼ����
                x2,y2   ��ֹ����
      ����ֵ��  ��
******************************************************************************/
void myLCD_DrawLine(u16 x1,u16 y1,u16 x2,u16 y2,u16 color)
{
	u16 t; 
	int xerr=0,yerr=0,delta_x,delta_y,distance;
	int incx,incy,uRow,uCol;
	delta_x=x2-x1; //������������ 
	delta_y=y2-y1;
	uRow=x1;//�����������
	uCol=y1;
	if(delta_x>0)incx=1; //���õ������� 
	else if (delta_x==0)incx=0;//��ֱ�� 
	else {incx=-1;delta_x=-delta_x;}
	if(delta_y>0)incy=1;
	else if (delta_y==0)incy=0;//ˮƽ�� 
	else {incy=-1;delta_y=-delta_x;}
	if(delta_x>delta_y)distance=delta_x; //ѡȡ�������������� 
	else distance=delta_y;
	for(t=0;t<distance+1;t++)
	{
		myLCD_DrawPoint(uRow,uCol,color);//����
		xerr+=delta_x;
		yerr+=delta_y;
		if(xerr>distance)
		{
			xerr-=distance;
			uRow+=incx;
		}
		if(yerr>distance)
		{
			yerr-=distance;
			uCol+=incy;
		}
	}
}
/******************************************************************************
      ����˵����������
      ������ݣ�x1,y1   ��ʼ����
                x2,y2   ��ֹ����
      ����ֵ��  ��
******************************************************************************/
void myLCD_DrawRectangle(u16 x1, u16 y1, u16 x2, u16 y2,u16 color)
{
	myLCD_DrawLine(x1,y1,x2,y1,color);
	myLCD_DrawLine(x1,y1,x1,y2,color);
	myLCD_DrawLine(x1,y2,x2,y2,color);
	myLCD_DrawLine(x2,y1,x2,y2,color);
}
/******************************************************************************
      ����˵������Բ
      ������ݣ�x0,y0   Բ������
                r       �뾶
      ����ֵ��  ��
******************************************************************************/
void Draw_Circle(u16 x0,u16 y0,u8 r,u16 color)
{
	int a,b;
	int di;
	a=0;b=r;	  
	while(a<=b)
	{
		myLCD_DrawPoint(x0-b,y0-a,color);             //3           
		myLCD_DrawPoint(x0+b,y0-a,color);             //0           
		myLCD_DrawPoint(x0-a,y0+b,color);             //1                
		myLCD_DrawPoint(x0-a,y0-b,color);             //2             
		myLCD_DrawPoint(x0+b,y0+a,color);             //4               
		myLCD_DrawPoint(x0+a,y0-b,color);             //5
		myLCD_DrawPoint(x0+a,y0+b,color);             //6 
		myLCD_DrawPoint(x0-b,y0+a,color);             //7
		a++;
		if((a*a+b*b)>(r*r))//�ж�Ҫ���ĵ��Ƿ��Զ
		{
			b--;
		}
	}
}

/******************************************************************************
      ����˵������ʾ�ַ�
      ������ݣ�x,y    �������
                num    Ҫ��ʾ���ַ�
                mode   1���ӷ�ʽ  0�ǵ��ӷ�ʽ
      ����ֵ��  ��
******************************************************************************/
void myLCD_ShowChar(u16 x,u16 y,u8 num,u8 mode,u16 color)
{
    u8 temp;
    u8 pos,t;
	  u16 x0=x;    
    if(x>myLCD_W-16||y>myLCD_H-16)return;	    //���ô���		   
	num=num-' ';//�õ�ƫ�ƺ��ֵ
	myLCD_Address_Set(x,y,x+8-1,y+16-1);      //���ù��λ�� 
	if(!mode) //�ǵ��ӷ�ʽ
	{
		for(pos=0;pos<16;pos++)
		{ 
			temp=myasc2_1608[(u16)num*16+pos];		 //����1608����
			for(t=0;t<8;t++)
		    {                 
		        if(temp&0x01)myLCD_WR_DATA(color);
				else myLCD_WR_DATA(myBACK_COLOR);
				temp>>=1;
				x++;
		    }
			x=x0;
			y++;
		}	
	}else//���ӷ�ʽ
	{
		for(pos=0;pos<16;pos++)
		{
		    temp=myasc2_1608[(u16)num*16+pos];		 //����1608����
			for(t=0;t<8;t++)
		    {                 
		        if(temp&0x01)myLCD_DrawPoint(x+t,y+pos,color);//��һ����     
		        temp>>=1; 
		    }
		}
	}   	   	 	  
}


/******************************************************************************
      ����˵������ʾ�ַ���
      ������ݣ�x,y    �������
                *p     �ַ�����ʼ��ַ
      ����ֵ��  ��
******************************************************************************/
void myLCD_ShowString(u16 x,u16 y,const u8 *p,u16 color)
{         
    while(*p!='\0')
    {       
        if(x>myLCD_W-16){x=0;y+=16;}
        if(y>myLCD_H-16){y=x=0;myLCD_Clear(RED);}
        myLCD_ShowChar(x,y,*p,0,color);
        x+=8;
        p++;
    }  
}


/******************************************************************************
      ����˵������ʾ����
      ������ݣ�m������nָ��
      ����ֵ��  ��
******************************************************************************/
u32 mypow(u8 m,u8 n)
{
	u32 result=1;	 
	while(n--)result*=m;    
	return result;
}


/******************************************************************************
      ����˵������ʾ����
      ������ݣ�x,y    �������
                num    Ҫ��ʾ������
                len    Ҫ��ʾ�����ָ���
      ����ֵ��  ��
******************************************************************************/
void myLCD_ShowNum(u16 x,u16 y,u16 num,u8 len,u16 color)
{         	
	u8 t,temp;
	u8 enshow=0;
	for(t=0;t<len;t++)
	{
		temp=(num/mypow(10,len-t-1))%10;
		if(enshow==0&&t<(len-1))
		{
			if(temp==0)
			{
				myLCD_ShowChar(x+8*t,y,' ',0,color);
				continue;
			}else enshow=1; 
		 	 
		}
	 	myLCD_ShowChar(x+8*t,y,temp+48,0,color); 
	}
} 


/******************************************************************************
      ����˵������ʾС��
      ������ݣ�x,y    �������
                num    Ҫ��ʾ��С��
                len    Ҫ��ʾ�����ָ���
      ����ֵ��  ��
******************************************************************************/
void myLCD_ShowNum1(u16 x,u16 y,float num,u8 len,u16 color)
{         	
	u8 t,temp;
	u8 enshow=0;
	u16 num1;
	num1=num*100;
	for(t=0;t<len;t++)
	{
		temp=(num1/mypow(10,len-t-1))%10;
		if(t==(len-2))
		{
			myLCD_ShowChar(x+8*(len-2),y,'.',0,color);
			t++;
			len+=1;
		}
	 	myLCD_ShowChar(x+8*t,y,temp+48,0,color);
	}
}







