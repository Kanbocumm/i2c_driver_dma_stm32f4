#include "main.h"


TaskHandle_t LED1TaskHandler;


void LED1Task(void *pvParameters)
{
	/*
    TickType_t xLastWakeTime;
    const TickType_t xFrequency = pdMS_TO_TICKS(400);  // 1000ms (1 saniye)

    xLastWakeTime = xTaskGetTickCount();
     */

	for(;;)
	{
		// Set Pins 12-15 to 1 to turn on all LEDs
		GPIOD->ODR |= (1 << 12);

        vTaskDelay(pdMS_TO_TICKS(400));

        GPIOD->ODR &= ~(1 << 12);

        vTaskDelay(pdMS_TO_TICKS(400));
	}

}


void RFIDReadTask(void *pvParameters)
{

	for(;;)
	{
		spi_receive();

	    vTaskDelay(pdMS_TO_TICKS(400));

	}

}


void system_init(void)
{
	/* FPU settings, can be enabled from project makefile */
		#if (__FPU_PRESENT == 1) && (__FPU_USED == 1)
		SCB->CPACR |= ((3UL << 10*2)|(3UL << 11*2));  /* set CP10 and CP11 Full Access */
		#endif

		/* Reset the RCC clock configuration to the default reset state */
		/* Set HSION bit */
		RCC->CR |= (1U << 0);

		/* Reset CFGR register */
		RCC->CFGR = 0x00000000;

		/* Reset HSEON (16), CSSON (19) and PLLON (24) bits */
		RCC->CR &= ~((1U << 16) | (1U << 19) | (1U << 24));

		/* Reset PLLCFGR register to reset value */
		RCC->PLLCFGR = 0x24003010UL;

		/* Reset HSEBYP bit */
		RCC->CR &= ~(1U << 18);

		/* Disable all clock interrupts */
		RCC->CIR = 0x00000000UL;
}

void set_sysclk_to_hse(void)
{
	HWREG(RCC_AHB1ENR) |= GPIOD_EN_BIT;

    RCC->CR |= (1 << 16);

    while(!(RCC->CR & (1 << 17)));

    RCC->CFGR &= ~(3U << 0);
    RCC->CFGR |= (1 << 0);

}


void set_sysclk_to_84(void)
{
	 system_init();

	 #undef PLL_P
	 uint32_t PLL_P = 4;

	 /* Enable HSE (CR: bit 16) */
	 RCC->CR |= (1 << 16);
	    /* Wait till HSE is ready (CR: bit 17) */
	 while(!(RCC->CR & (1 << 17)));

	    /* set voltage scale to 1 for max frequency */
	    /* first enable power interface clock (APB1ENR:bit 28) */
	 RCC->APB1ENR |= (1 << 28);

	    /* then set voltage scale to 1 for max frequency (PWR_CR:bit 14)
	     * (0) scale 2 for fCLK <= 144 Mhz
	     * (1) scale 1 for 144 Mhz < fCLK <= 168 Mhz
	     */
	  PWR->CR |= (1 << 14);

	    /* set AHB prescaler to /1 (CFGR:bits 7:4) */
	  RCC->CFGR |= (0 << 4);
	    /* set ABP low speed prescaler to /4 (APB1) (CFGR:bits 12:10) */
	  RCC->CFGR |= (5 << 10);
	    /* set ABP high speed prescaper to /2 (ABP2) (CFGR:bits 15:13) */
	  RCC->CFGR |= (4 << 13);

	    /* Set M, N, P and Q PLL dividers
	     * PLLCFGR: bits 5:0 (M), 14:6 (N), 17:16 (P), 27:24 (Q)
	     * Set PLL source to HSE, PLLCFGR: bit 22, 1:HSE, 0:HSI
	     */
	  RCC->PLLCFGR = PLL_M | (PLL_N << 6) | (((PLL_P >> 1) -1) << 16) |
	                   (PLL_Q << 24) | (1 << 22);
	    /* Enable the main PLL (CR: bit 24) */
	  RCC->CR |= (1 << 24);
	    /* Wait till the main PLL is ready (CR: bit 25) */
	  while(!(RCC->CR & (1 << 25)));
	    /* Configure Flash
	     * prefetch enable (ACR:bit 8)
	     * instruction cache enable (ACR:bit 9)
	     * data cache enable (ACR:bit 10)
	     * set latency to 2 wait states (ARC:bits 2:0)
	     *   see Table 10 on page 80 in RM0090
	     */
	  FLASH->ACR = (1 << 8) | (1 << 9) | (1 << 10 ) | (2 << 0);

	    /* Select the main PLL as system clock source, (CFGR:bits 1:0)
	     * 0b00 - HSI
	     * 0b01 - HSE
	     * 0b10 - PLL
	     */
	  RCC->CFGR &= ~(3U << 0);
	  RCC->CFGR |=  (2  << 0);
	  /* Wait till the main PLL is used as system clock source (CFGR:bits 3:2) */
	  while (!(RCC->CFGR & (2 << 2))); // Flag control

	  SystemCoreClock = 84000000;
}


void SysTick_Handler(void)
{
#if (INCLUDE_xTaskGetSchedulerState == 1 )
  if (xTaskGetSchedulerState() != taskSCHEDULER_NOT_STARTED)
  {
#endif /* INCLUDE_xTaskGetSchedulerState */
  xPortSysTickHandler();
#if (INCLUDE_xTaskGetSchedulerState == 1 )
  }
#endif /* INCLUDE_xTaskGetSchedulerState */
}



int main(void)
{
	BaseType_t xTaskCreateStatus;

	//system_init();

	//set_sysclk_to_84();

    gpio_all_init();

    nvic_config();

    UART_Init();

    spi_init();


	xTaskCreateStatus = xTaskCreate(LED1Task, "LED Custom Task", 1000, NULL, 2, &LED1TaskHandler);
	configASSERT(xTaskCreateStatus);

	xTaskCreateStatus = xTaskCreate(RFIDReadTask, "RFID Custom Task", 1000, NULL, 2, &LED1TaskHandler);
	configASSERT(xTaskCreateStatus);


	xTaskHW16_init();


	vTaskStartScheduler();

	for(;;);
}


void vApplicationMallocFailedHook( void )
{
	/* vApplicationMallocFailedHook() will only be called if
	configUSE_MALLOC_FAILED_HOOK is set to 1 in FreeRTOSConfig.h.  It is a hook
	function that will get called if a call to pvPortMalloc() fails.
	pvPortMalloc() is called internally by the kernel whenever a task, queue,
	timer or semaphore is created.  It is also called by various parts of the
	demo application.  If heap_1.c or heap_2.c are used, then the size of the
	heap available to pvPortMalloc() is defined by configTOTAL_HEAP_SIZE in
	FreeRTOSConfig.h, and the xPortGetFreeHeapSize() API function can be used
	to query the size of free heap space that remains (although it does not
	provide information on how the remaining heap might be fragmented). */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}
/*-----------------------------------------------------------*/

void vApplicationIdleHook( void )
{
	/* vApplicationIdleHook() will only be called if configUSE_IDLE_HOOK is set
	to 1 in FreeRTOSConfig.h.  It will be called on each iteration of the idle
	task.  It is essential that code added to this hook function never attempts
	to block in any way (for example, call xQueueReceive() with a block time
	specified, or call vTaskDelay()).  If the application makes use of the
	vTaskDelete() API function (as this demo application does) then it is also
	important that vApplicationIdleHook() is permitted to return to its calling
	function, because it is the responsibility of the idle task to clean up
	memory allocated by the kernel to any task that has since been deleted. */
}
/*-----------------------------------------------------------*/

void vApplicationStackOverflowHook( TaskHandle_t pxTask, char *pcTaskName )
{
	( void ) pcTaskName;
	( void ) pxTask;

	/* Run time stack overflow checking is performed if
	configCHECK_FOR_STACK_OVERFLOW is defined to 1 or 2.  This hook
	function is called if a stack overflow is detected. */
	taskDISABLE_INTERRUPTS();
	for( ;; );
}


void Error_Handler(void)
{
  /* USER CODE BEGIN Error_Handler_Debug */
  /* User can add his own implementation to report the HAL error return state */
  __disable_irq();
  while (1)
  {
  }
  /* USER CODE END Error_Handler_Debug */
}

#ifdef  USE_FULL_ASSERT
/**
  * @brief  Reports the name of the source file and the source line number
  *         where the assert_param error has occurred.
  * @param  file: pointer to the source file name
  * @param  line: assert_param error line source number
  * @retval None
  */
void assert_failed(uint8_t *file, uint32_t line)
{
  /* USER CODE BEGIN 6 */
  /* User can add his own implementation to report the file name and line number,
     ex: printf("Wrong parameters value: file %s on line %d\r\n", file, line) */
  /* USER CODE END 6 */
}
#endif /* USE_FULL_ASSERT */
