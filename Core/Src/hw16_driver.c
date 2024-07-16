#include "main.h"


TaskHandle_t HW16TaskHandler;

void HW16Task(void *pvParameters)
{
	for(;;)
	{
		UART_Send();

		GPIOD->ODR ^= (1 << 15);

        vTaskDelay(pdMS_TO_TICKS(1000));
	}

}


void xTaskHW16_init(void)
{
	BaseType_t xTaskCreateStatus;

	xTaskCreateStatus = xTaskCreate(HW16Task, "HW-016 PIR Sensor Task", 512, NULL, 1, &HW16TaskHandler);

	configASSERT(xTaskCreateStatus);

}
