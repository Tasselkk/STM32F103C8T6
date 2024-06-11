#ifndef _ENCODER_H__
#define _ENCODER_H__

void encoder_init(void);
void encoder_exti_config(void);
void encoder_nvic_config(void);
unsigned short encoder_Get_Right(void);
unsigned short encoder_Get_Left(void);
#endif // _ENCODER_H__
