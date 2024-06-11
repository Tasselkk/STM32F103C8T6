#ifndef _COUNT_SENSOR_H__
#define _COUNT_SENSOR_H__

#define SENSOR_GPIO_PORT_SOURCE GPIO_PortSourceGPIOB
#define SENSOR_PIN_PORT GPIOB
#define SENSOR_PIN GPIO_Pin_13
#define SENSOR_RCC_PORT RCC_APB2Periph_GPIOB
void infrared_sensor_init(void);
void sensor_exti_config(void);
void sensor_nvic_config(void);
unsigned short CountSensor_Get(void);

#endif // _COUNT_SENSOR_H__
