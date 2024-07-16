#ifndef __MAIN_H
#define __MAIN_H

#include "stm32f407xx.h"
#include "system_stm32f4xx.h"
#include <stdio.h>
#include "hw16_driver.h"
#include "gpio_driver.h"
#include "nvic_irq_driver.h"
#include "FreeRTOS.h"
#include "task.h"
#include "queue.h"
#include "semphr.h"
#include "uart_driver.h"
#include "spi_driver.h"


#define HWREG(x) (*((volatile unsigned long *)(x)))

#define RCC_BASE_ADDR    0x40023800
#define RCC_AHB1ENR      (RCC_BASE_ADDR + 0x30)
#define GPIOD_EN_BIT     0x8  // Bit 3 (0x08)


#ifdef __cplusplus
extern "C" {
#endif


void Error_Handler(void);

#ifdef __cplusplus
}
#endif

#endif /* __MAIN_H */
