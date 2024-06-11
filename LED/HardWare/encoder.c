#include "stm32f10x.h"                  // Device header

#include "encoder.h"

uint32_t count_left = 0;
uint32_t count_right = 0;

void encoder_init(void){
	// 使能GPIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	// 使能AFIO时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_AFIO, ENABLE);
	
	//初始化GPIO
	GPIO_InitTypeDef GPIO_InitStructure;
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_IN_FLOATING;
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_10;
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;
	GPIO_Init(GPIOB, &GPIO_InitStructure);
	

}

void encoder_exti_config(void){
	//PB11 信号进入EXTI 11号线路
	//PB12 信号进入EXTI 12号线路
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource0);
	GPIO_EXTILineConfig(GPIO_PortSourceGPIOB, GPIO_PinSource10);
	
	EXTI_InitTypeDef EXTI_InitStructure;
	EXTI_InitStructure.EXTI_Line = EXTI_Line0 | EXTI_Line10;
	EXTI_InitStructure.EXTI_LineCmd = ENABLE;
	EXTI_InitStructure.EXTI_Mode = EXTI_Mode_Interrupt;
	EXTI_InitStructure.EXTI_Trigger = EXTI_Trigger_Falling;
	EXTI_Init(&EXTI_InitStructure);
	

}

void encoder_nvic_config(void){
	// 优先级组必须在最开始设置，要么在main函数首行设置一次，要么在其他函数中设置的NVIC_PriorityGroup必须相同
	NVIC_PriorityGroupConfig(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = EXTI0_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	NVIC_InitStructure.NVIC_IRQChannel = EXTI15_10_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 1;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 2;
	NVIC_Init(&NVIC_InitStructure);
}

void EXTI15_10_IRQHandler(void){
	if(EXTI_GetITStatus(EXTI_Line10) == SET){
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_10) == 1){
			count_left++;
		}
		
		EXTI_ClearITPendingBit(EXTI_Line10);
                 	}
}

void EXTI0_IRQHandler(void){
		if(EXTI_GetITStatus(EXTI_Line0) == SET){
		if (GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_0) == 1){
			count_right++;
		}
		
		EXTI_ClearITPendingBit(EXTI_Line0);
	}
}

uint16_t encoder_Get_Left(void)
{
	return count_left;
}
uint16_t encoder_Get_Right(void)
{
	return count_right;
}
