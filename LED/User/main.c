#include "stm32f10x.h"                  // Device header
#include "myconfig.h"
#include "Delay.h"
#include "OLED.h"


void default_init(void){
		/*开启时钟*/
	RCC_APB2PeriphClockCmd(RCC_APB2Periph_GPIOC, ENABLE);	//开启GPIOC的时钟
															//使用各个外设前必须开启时钟，否则对外设的操作无效
	
	/*GPIO初始化*/
	GPIO_InitTypeDef GPIO_InitStructure;					//定义结构体变量
	
	GPIO_InitStructure.GPIO_Mode = GPIO_Mode_Out_PP;		//GPIO模式，赋值为推挽输出模式
	GPIO_InitStructure.GPIO_Pin = GPIO_Pin_13;				//GPIO引脚，赋值为第13号引脚
	GPIO_InitStructure.GPIO_Speed = GPIO_Speed_50MHz;		//GPIO速度，赋值为50MHz
	
	GPIO_Init(GPIOC, &GPIO_InitStructure);					//将赋值后的构体变量传递给GPIO_Init函数
															//函数内部会自动根据结构体的参数配置相应寄存器
															//实现GPIOC的初始化
	
	/*设置GPIO引脚的高低电平*/
	/*若不设置GPIO引脚的电平，则在GPIO初始化为推挽输出后，指定引脚默认输出低电平*/
//	GPIO_SetBits(GPIOC, GPIO_Pin_13);						//将PC13引脚设置为高电平
	GPIO_ResetBits(GPIOC, GPIO_Pin_13);						//将PC13引脚设置为低电平
	
	
}
void trail_init(void){
#if LED_TRAIL
	led_init();
#endif // LED_TRAIL
	
#if BEEP_TRAIL
	beep_init();
#endif // BEEP_TRAIL
	
#if KEY_TRAIL
	led_init();
	key_init();
#endif // KEY_TRAIL
	
#if LIGHT_TRAIL
	beep_init();
	light_init();
#endif // LIGHT_TRAIL
	
#if OLED_TRAIL
	OLED_Init();
#endif // OLED_TRAIL

#if COUNT_SENSOR_TRAIL
	
  infrared_sensor_init();
	// 要先设置使能GPIO、APIO总线，才能进行下两个函数，否则无法触发中断
	sensor_nvic_config();
	
	sensor_exti_config();
	
	OLED_Init();
  
#endif // COUNT_SENSOR_TRAIL

#if ENCODER_TRAIL
	
  encoder_init();
	// 要先设置使能GPIO、APIO总线，才能进行下两个函数，否则无法触发中断
	encoder_nvic_config();
	
	encoder_exti_config();
	
	OLED_Init();
  
#endif // ENCODER_TRAIL

#if TIMER_TRAIL
	OLED_Init();
#endif // TIMER_TRAIL
}
int main(void)
{
	default_init();
	trail_init();
	
	while (1)
	{

#if LED_TRAIL
		Delay_ms(1000);
		GPIO_SetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);
		Delay_ms(1000);
		GPIO_ResetBits(GPIOA, GPIO_Pin_0 | GPIO_Pin_2 | GPIO_Pin_3 | GPIO_Pin_4);
#endif // LED_TRAIL		
		
#if BEEP_TRAIL
		Delay_ms(500);
		GPIO_SetBits(GPIOB, GPIO_Pin_12);
		Delay_ms(500);
		GPIO_ResetBits(GPIOB, GPIO_Pin_12);
#endif // BEEP_TRAIL
		
#if KEY_TRAIL
		if(KEY_SCAN(GPIOB, GPIO_Pin_1) == 0){
			Delay_us(10);
			GPIO_SetBits(GPIOA, GPIO_Pin_0);
		}
		Delay_s(1);
		GPIO_ResetBits(GPIOA, GPIO_Pin_0);
#endif // KEY_TRAIL

#if LIGHT_TRAIL
		if(GPIO_ReadInputDataBit(GPIOB, GPIO_Pin_13) == 1){
//			Delay_s(1);
//			GPIO_SetBits(GPIOB, GPIO_Pin_12);
			Delay_ms(100);
			GPIO_ResetBits(GPIOB, GPIO_Pin_12);
			Delay_ms(100);
		} else{
			GPIO_SetBits(GPIOB, GPIO_Pin_12);
		}
#endif // LIGHT_TRAIL

#if OLED_TRAIL
  OLED_ShowChar(1, 1, 'A');
	OLED_ShowString(2, 1, "KKKWWW");
	OLED_ShowNum(3, 1, 1024, 4);
	OLED_ShowHexNum(4, 1, 1024, 4);
//	OLED_ShowBinNum(5, 1, 1024, 11);
//	OLED_ShowSignedNum(6, 1, -1024, 4);
	
#endif // OLED_TRAIL

#if COUNT_SENSOR_TRAIL
  OLED_ShowNum(1, 1, CountSensor_Get(), 4);
#endif // COUNT_SENSOR_TRAIL

#if ENCODER_TRAIL
  OLED_ShowNum(1, 1, encoder_Get_Right(), 4);
	OLED_ShowNum(2, 1, encoder_Get_Left(), 4);
#endif // ENCODER_TRAIL

#if TIMER_TRAIL
OLED_ShowNum(1, 1, 121212, 4);
	
#endif // TIMER_TRAIL
	}
}
