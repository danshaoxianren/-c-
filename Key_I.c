#include "stm32f10x.h"
#include "LED.h"


void Key_I_Init(void)
{
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA,ENABLE);		//打开GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB,ENABLE);
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO,ENABLE);			//打开AFIO时钟
	
	//配置GPIO
	GPIO_InitTypeDef GPIO_Initstructure;
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IPU;		//IPU上拉输入
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_0;	
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOA,&GPIO_Initstructure);
	
	
	GPIO_Initstructure.GPIO_Mode = GPIO_Mode_IPU;		//IPU上拉输入
	GPIO_Initstructure.GPIO_Pin = GPIO_Pin_1;	
	GPIO_Initstructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB,&GPIO_Initstructure);
	
	//配置AFIO
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB,GPIO_PinSource1);
	
	//配置EXTI
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line0;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;			////上升沿触发，抬手灯切换状态
	//EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;			//下降沿触发，按下灯就会切换状态
	EXTI_Init(&EXTI_InitStructure);
	
	
	EXTI_InitStructure.EXTI_Line = EXTI_Line1;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Rising;			////上升沿触发，抬手灯切换状态
	//EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;			//下降沿触发，按下灯就会切换状态
	EXTI_Init(&EXTI_InitStructure);
	
	//配置NVIC
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = 	EXTI0_IRQn;					//指定中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);

	NVIC_InitStructure.NVIC_IRQChannel = 	EXTI1_IRQn;					//指定中断通道
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStructure);
	
}

void EXTI0_IRQHandler(void)
{
	LED_Turn();
	//在此处加一下OLED程序可以实现计数
	
	EXTI_ClearITPendingBit(EXTI_Line0);
	
}

void EXTI1_IRQHandler(void)
{
	LED_Turn();
	//在此处加一下OLED程序可以实现计数
	
	EXTI_ClearITPendingBit(EXTI_Line1);
	
}
