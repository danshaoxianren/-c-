#include "stm32f10x.h"                  // Device header

/**   多行注释
	*@brief  Brief Description：简要描述：微秒级延时
	*@param		Parameter：参数：xus延时时长，范围：0~233015
	*@retval	Return Value：返回值：无
	*/
	//这是Doxygen 风格的文档注释
	//这样注释可以用Doxygen 是嵌入式软件行业（以及大量C/C++项目）最通用的自动化文档生成工具。
	//它能把代码里这种特殊格式的注释，自动提取出来，生成漂亮的HTML/PDF函数手册。

void Delay_us(uint32_t xus)		//编写微秒延迟
	//xus是x（未知数/变量）+us（微秒），这句是定义参数x微秒
{
	SysTick->LOAD = 72 * xus;		//SysTick找到load寄存器地址并将72xus存入
	//需要填入LOAD寄存器的计数值=每微秒计数值×希望延时的微秒数
	//72是系统定时器(SysTick)的计数频率，即每微秒计数的次数。
	//xus是期望延时的时间长度，单位是微秒(us)。
	//SysTick 的计数器每秒钟会滴答 72,000,000 次（72MHZ晶振）。72,000,000 次/秒÷1,000,000 微秒/秒=72 次/微秒
	//所以晶振72次就是一微秒
	//SysTick:System Tick Timer:系统滴答定时器
	//load：Load Register：重装载寄存器
	//->就是指针
	SysTick->VAL = 0x00;		//将当前计数值寄存器清零
	//VAL：Current Value Register：当前计数值寄存器（仅存计数值，不参与直接的逻辑运算）
	//0x：十六进制前缀
	SysTick->CTRL = 0x00000005;	//配置并启动系统定时器，5（二进制0101）
	//CTRL：Control and Status Register：控制及状态寄存器
	//特殊功能寄存器会通过特定的比特序列启动特定功能
	//Bit 0 (ENABLE)=1-> 启动倒数计数器
	// Bit 1 (TICKINT)= 0->禁止中断
	// Bit 2 (CLKSOURCE)= 1->时钟源选择内核时钟 (72MHz)
	// Bit 3-31=0->保留位，必须写0
	while(!(SysTick->CTRL & 0x00010000));		//轮询)，直到系统定时器的 COUNTFLAG 标志位(第16位)由硬件自动置1。该标志位为1表示：定时器已经倒数到了0，指定的延时时间已到。
	//bit 16：SysTick硬件模块的计数完成标志位COUNTFLAG，判断延时是否结束的唯一状态指示灯。
	SysTick->CTRL = 0x00000004;		//延时目的已达到，停止计数器工作以降低系统功耗。关闭后，COUNTFLAG 标志位会自动清零。
	//4的二进制0100
	//Bit 0 (ENABLE)	使能	0	关闭定时器，停止计数以节省功耗。
	//Bit 1 (TICKINT)	中断	0	保持关闭。
	//Bit 2 (CLKSOURCE)	时钟源	1	保持原配置不变。
}

/**
	*@brief	毫秒级延时
	*@param	xms延时时长，范围：0~4294967295
	*@retval	无
	*/

void Delay_ms(uint32_t xms)		//1000微秒等于一毫秒，调用微秒函数执行1000微秒
{
	while(xms--)		//只要xms不为0循环为真
	{
		Delay_us(1000);
	}
}

/**
	*@brief	秒级延时
	*@param	xs延时时长，范围：0~4294967295
	*@retval	无
	*/

void Delay_s(uint32_t xs)		//1000毫秒等于一秒，调用毫秒函数执行1000毫秒
{
	while(xs--)
	{
		Delay_ms(1000);
	}
}
