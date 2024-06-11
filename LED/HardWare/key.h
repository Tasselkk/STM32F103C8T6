#ifndef _KEY_H__
#define _KEY_H__
#define KEY_SCAN(GPIOx, GPIO_Pinx) GPIO_ReadInputDataBit(GPIOx, GPIO_Pinx)
void key_init(void);
#endif // _KEY_H__
