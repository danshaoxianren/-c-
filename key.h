#ifndef _KEY_H_		//如果不包含LED_H
#define _KEY_H_		//那就定义LED_H

void Key_Init(void);
uint8_t Key_GetFlag(void);
uint8_t Key_GetFlag2(void);

#endif		//结束条件编译检查