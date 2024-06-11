#include "stm32f10x.h"                  // Device header
#include "led.h"
// LED 接在PA0端口上，低电平亮
void led_init(void){
  // 使能 APB2总线的GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOA, ENABLE);
	
	// 设置GPIO工作模式、速率、引脚编号
	GPIO_InitTypeDef GPIOInitStruct;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_Out_PP; // 推挽输出
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz; // 工作速度50MHz
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4; // 0号引脚
	
	// 初始化PA0
	GPIO_Init(GPIOA, &GPIOInitStruct);
	// 设置PA0为低电平
	GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);
	
}
