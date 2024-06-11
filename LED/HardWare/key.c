#include "stm32f10x.h"                  // Device header
#include "key.h"
// 按键插在B1 和 B11 端口上
void key_init(void){
  // 使能 APB2总线的GPIOB时钟
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOB, ENABLE);
	
	// 设置GPIO工作模式、速率、引脚编号
	GPIO_InitTypeDef GPIOInitStruct;
	GPIOInitStruct.GPIO_Mode = GPIO_Mode_IPU; // 上拉输出
	GPIOInitStruct.GPIO_Speed = GPIO_Speed_50MHz; // 工作速度50MHz
	GPIOInitStruct.GPIO_Pin = GPIO_Pin_1 | GPIO_Pin_11; // 1号引脚和11 号引脚
	
	// 初始化PB
	GPIO_Init(GPIOB, &GPIOInitStruct);
	
}
