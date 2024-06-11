#include "stm32f10x.h"                  // Device header
#include "stm32f10x_exti.h"
#include "misc.h"

#include "count_sensor.h"
uint32_t count = 0;
void infrared_sensor_init(void){
	// 使能GPIO时钟
	RCC_APB2PeriphClockCmd(SENSOR_RCC_PORT, ENABLE);
	// 使能AFIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	//初始化GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = SENSOR_PIN;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(SENSOR_PIN_PORT, &GPIO_InitStructure);
	

}
void sensor_exti_config(void){
		//PB13 信号进入EXTI 14号线路
	GPIO_EXTILineConfig(SENSOR_GPIO_PORT_SOURCE, GPIO_PinSource13);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line13;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	

}

void sensor_nvic_config(void){
	// 优先级组必须在最开始设置，要么在main函数首行设置一次，要么在其他函数中设置的NVIC_PriorityGroup必须相同
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
}

//void EXTI15_10_IRQHandler(void){
//	if(EXTI_GetITStatus(EXTI_Line13) == SET){
//		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) == 0){
//			count++;
//		}
//		EXTI_ClearITPendingBit(EXTI_Line13);
//	}
//	
//}

uint16_t CountSensor_Get(void)
{
	return count;
}
