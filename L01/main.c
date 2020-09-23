#include "stm32f4xx.h"                  // Device header
#include "FreeRTOS.h"                   // ARM.FreeRTOS::RTOS:Core
#include "task.h"                       // ARM.FreeRTOS::RTOS:Core
#include "FreeRTOSConfig.h"             // ARM.FreeRTOS::RTOS:Config

void vTask1Function(void* pvParameters)
{
	while(1) {
		//ODR = output data register
		GPIOA -> ODR |= GPIO_ODR_ODR_5;
		//otbitij sleep follows
		for(int i=0; i<100000; i++); 
		GPIOA -> ODR &= ~GPIO_ODR_ODR_5;
		for(int i=0; i<100000; i++); 
	}
}

//map range 0x40000000,0x4000FFFF
int main(void) {
	//Init
	//launch (taktirovanije) for global IO module, AHB = inner bus
	RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
	//A5 is a diode
	GPIOA->MODER |= GPIO_MODER_MODER5_0;
	
	xTaskCreate(vTask1Function, "task1", configMINIMAL_STACK_SIZE, NULL, 2, NULL);
	
	vTaskStartScheduler();
}
