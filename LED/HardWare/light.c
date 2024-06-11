#include "stm32f10x.h"                  // Device header
#include "light.h"
// LED 接在PA0端口上，低电平亮
void light_init(void){
  // 使能 APB2总线的GPIOA时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	// 设置GPIO工作模式、速率、引脚编号
	GPIO_InitTypeDef GPIOInitStruct;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_IPU; // 推挽输出
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz; // 工作速度50MHz
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_13; // 0号引脚
	
	// 初始化PB
	GPIO_Init(GPIOB, &GPIOInitStruct);

	
}
