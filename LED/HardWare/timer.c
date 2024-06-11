#include "stm32f10x.h"                  // Device header
#include "stm32f10x_tim.h"
#include "misc.h"
#include "timer.h"

uint16_t current_time = 0;
void timer_init(void){
	// 1. 开启TIM2外设时钟
	RCC_APB1PeriphClockCmd(RCC_APB1Periph_TIM2, ENABLE);
	
	// 2. 确定时基单元的时钟
	// 此处设置为内部时钟（不写此句默认也是内部时钟）
	TIM_InternalClockConfig(TIM2);
	
	// 3. 配置时基单元
	TIM_TimeBaseInitTypeDef TimeBase_InitStructure;
	TimeBase_InitStructure.TIM_ClockDivision = TIM_CKD_DIV1;
	TimeBase_InitStructure.TIM_CounterMode = TIM_CounterMode_Up;
	TimeBase_InitStructure.TIM_Period = 10000 - 1;
	TimeBase_InitStructure.TIM_Prescaler = 7200 - 1;
	TimeBase_InitStructure.TIM_RepetitionCounter = 0;
	TIM_TimeBaseInit(TIM2, &TimeBase_InitStructure);
	
	TIM_ClearFlag(TIM2, TIM_FLAG_Update);
	// 4. 使能更新中断
	TIM_ITConfig(TIM2, TIM_IT_Update, ENABLE);
	
	NVIC_SetPriorityGrouping(NVIC_PriorityGroup_2);
	
	NVIC_InitTypeDef NVIC_InitStructure;
	NVIC_InitStructure.NVIC_IRQChannel = TIM2_IRQn;
	NVIC_InitStructure.NVIC_IRQChannelCmd = ENABLE;
	NVIC_InitStructure.NVIC_IRQChannelPreemptionPriority = 2;
	NVIC_InitStructure.NVIC_IRQChannelSubPriority = 1;
	NVIC_Init(&NVIC_InitStructure);
	
	
	TIM_Cmd(TIM2, ENABLE);
	
	
}

void TIM2_IRQHandler(void){
	if (TIM_GetITStatus(TIM2, TIM_IT_Update) == SET){
		current_time++;
		TIM_ClearITPendingBit(TIM2, TIM_FLAG_Update);
	}		
}

uint16_t get_current_time(void){
	return current_time;
}
