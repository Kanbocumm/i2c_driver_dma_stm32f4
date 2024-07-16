#include "nvic_irq_driver.h"
#include "main.h"


void nvic_config(void)
{
	RCC->APB2ENR |= (1 << 14);

    // Configure EXTI line for PA1 (EXTI1)
    SYSCFG->EXTICR[0] &= ~(0xF << 4);  // Clear bits for EXTI1
    SYSCFG->EXTICR[0] |= (0 << 4);     // Set bits to 0000 to select PA1

	EXTI->IMR |= EXTI_IMR_IM1;

	EXTI->RTSR |= (1<<1);  // Enable Rising Edge Trigger for PA1

    EXTI->FTSR |= (1 << 1);

	NVIC_SetPriority (EXTI1_IRQn, 5);  // Set Priority

	NVIC_EnableIRQ (EXTI1_IRQn);  // Enable Interrupt

}


void HW16_IRQ_Handler(void)
{
	GPIOD->ODR ^= (1 << 14);
}


void EXTI1_IRQHandler(void)
{
    // Check if the interrupt was triggered by PA1
    if (EXTI->PR & (1 << 1))
    {
        // Clear the interrupt flag by writing 1
        EXTI->PR |= (1 << 1);

        // Call the user-defined IRQ handler function
        HW16_IRQ_Handler();
    }
}
