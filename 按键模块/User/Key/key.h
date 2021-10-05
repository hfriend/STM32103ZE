/*
		P30~P37 “¿¥Œ∂‘”¶ PF0~PF7
*/
#ifndef __BSP_KEY_H
#define __BSP_KEY_H

#include "stm32f10x.h"
#include "sys.h"
#include "stdio.h"

#define KEY_IN_1					PFin(4)
#define KEY_IN_2					PFin(5)
#define KEY_IN_3					PFin(6)
#define KEY_IN_4					PFin(7)

#define KEY_OUT_1					PFout(0)
#define KEY_OUT_2					PFout(1)
#define KEY_OUT_3					PFout(2)
#define KEY_OUT_4					PFout(3)



void Key_GPIOF_Init(void);
void KeyScan(void);
void KeyDriver(void);
void KeyAction(uint8_t Key_Value);


#endif // __BSP_KEY_H

