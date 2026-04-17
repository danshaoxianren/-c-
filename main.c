#include "stm32f10x.h"                  // Device header
#include "LED.h"
#include "Key_I.h"


int main(void)
{
	LED_Init();
	Key_I_Init();
	
	while (1)
	{
		
		
	}
}

