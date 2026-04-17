#include "stm32f10x.h"                  // Device header


void Key_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);	
	
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IPU;		//IPU上拉输入
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_11 | GPIO_Pin_10;	
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstructure);
	GPIO_Init(GPIOB,&GPIO_Initstructure);
	
}

uint8_t Key_GetFlag(void)		//正常按键
{
	uint8_t Flag = 0;
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0)
	{
		Delay_ms(10);		//消去按下抖动
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11) == 0);		//按键按下延迟10ms之后如果没检测到高电平就是没有抬手
		Delay_ms(10);		//消去抬手抖动
		Flag = 1;		//将按键标志改成1，就是已经按下按键
				
	}
	return Flag;
	
}

uint8_t Key_GetFlag2(void)		//用条线模拟按键
{
	uint8_t Flag = 0;
	if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_11) == 0)
	{
		Delay_ms(10);		//消去按下抖动
		while(GPIO_ReadInputDataBit(GPIOA,GPIO_Pin_11) == 0);		//按键按下延迟10ms之后如果没检测到高电平就是没有抬手
		Delay_ms(10);		//消去抬手抖动
		Flag = 1;		//将按键标志改成1，就是已经按下按键
				
	}
	return Flag;
	
}
