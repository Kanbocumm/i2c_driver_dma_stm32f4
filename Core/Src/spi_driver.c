#include "spi_driver.h"
#include "main.h"

volatile uint8_t *data = 0;
uint8_t size = 6;


void spi_init(void)
{
	RCC->AHB1ENR |= (1<<0);  // Enable GPIO Clock

	GPIOA->MODER |= (2<<10)|(2<<12)|(2<<14)|(1<<18);  // Alternate functions for PA5, PA6, PA7 and Output for PA9

	GPIOA->OSPEEDR |= (3<<10)|(3<<12)|(3<<14)|(3<<18);  // HIGH Speed for PA5, PA6, PA7, PA9

	GPIOA->AFR[0] |= (5<<20)|(5<<24)|(5<<28);   // AF5(SPI1) for PA5, PA6, PA7


	RCC->APB2ENR |= (1 << 12);

	SPI1->CR1 |= (1 << 0)| (1 << 1);

	SPI1->CR1 |= (1 << 2); // MASTER Mode

	SPI1->CR1 |= (3<<3);  // BR[2:0] = 011: fPCLK/16, PCLK2 = 80MHz, SPI clk = 5MHz

	SPI1->CR1 |= (1 << 6); // MASTER Mode

	SPI1->CR1 &= ~(1<<7);  // LSBFIRST = 0, MSB first

	SPI1->CR1 |= (1<<8) | (1<<9);  // SSM=1, SSi=1 -> Software Slave Management

	SPI1->CR1 &= ~(1<<10);  // RXONLY = 0, full-duplex

	SPI1->CR1 &= ~(1<<11);  // DFF=0, 8 bit data

	SPI1->CR2 = 0;
}


void spi_receive(void)
{
	while (size)
	{
		while (((SPI1->SR)&(1<<7))) {};  // wait for BSY bit to Reset -> This will indicate that SPI is not busy in communication
		SPI1->DR = 0;  // send dummy data
		while (!((SPI1->SR) &(1<<0))){};
		GPIOD->ODR ^= (1 << 12);// Wait for RXNE to set -> This will indicate that the Rx buffer is not empty
	  *data++ = (SPI1->DR);
		size--;
	}

}
