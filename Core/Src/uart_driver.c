#include "main.h"
#include "uart_driver.h"


void UART_Init(void)
{
	RCC->AHB1ENR |= 1; //Enable GPIOA clock

	RCC->APB1ENR |= (1 << 17); //Enable USART2 clock

	GPIOA->MODER |= GPIO_MODER_MODER2_1 | GPIO_MODER_MODER3_1;

	GPIOA->AFR[0] |= (7 << GPIO_AFRL_AFSEL2_Pos) | (7 << GPIO_AFRL_AFSEL3_Pos);

	USART2->CR1  |= 0x0008 | 0x0004; //Enable Tx/Rx, 8-bit data

    USART2->BRR = 0x0683; //9600 baud @ 16 MHz

	 USART2->CR2 = 0x0000; //1 stop bit

	 USART2->CR3 = 0x0000; //no flow control

	//  USART2->CR1 |= 0x0080; // TXEIE (Transmit Interrupt)

	 USART2->CR1 |= 0x2000;

	 //ENABLE interrupt for USART2 on NVIC side
/*
	 NVIC_SetPriority(USART2_IRQn,0);

	 NVIC_EnableIRQ(USART2_IRQn);
	 */
}


void UART_Send(void)
{



    USART2->DR = 'a';   // LOad the Data

}
