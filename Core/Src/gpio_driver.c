#include "main.h"


void gpio_init(GPIO_TypeDef *gpio_port, uint32_t gpio_dir, uint32_t gpio_pin) {
    // 1. GPIO saatini etkinleştir
    if (gpio_port == GPIOA) {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOAEN;
    } else if (gpio_port == GPIOB) {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOBEN;
    } else if (gpio_port == GPIOC) {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOCEN;
    } else if (gpio_port == GPIOD) {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;
    } else if (gpio_port == GPIOE) {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOEEN;
    } else if (gpio_port == GPIOF) {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOFEN;
    } else if (gpio_port == GPIOG) {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOGEN;
    } else if (gpio_port == GPIOH) {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOHEN;
    } else if (gpio_port == GPIOI) {
        RCC->AHB1ENR |= RCC_AHB1ENR_GPIOIEN;
    }

    // 2. GPIO pinini yapılandır
    if (gpio_dir == GPIO_DIR_OUTPUT) {
        // Çıkış modu
        gpio_port->MODER &= ~(0x3 << (gpio_pin * 2));  // Önce temizle
        gpio_port->MODER |= (0x1 << (gpio_pin * 2));   // Sonra ayarla
    } else {
        // Giriş modu
        gpio_port->MODER &= ~(GPIO_MODER_MODER5 << (gpio_pin * 2));  // Giriş modunda (00)
    }
}


void gpio_all_init(void)
{
	gpio_init(GPIOA, GPIO_DIR_INPUT, 1);

    gpio_init(GPIOD, GPIO_DIR_OUTPUT, 12);
    gpio_init(GPIOD, GPIO_DIR_OUTPUT, 13);
    gpio_init(GPIOD, GPIO_DIR_OUTPUT, 14);
    gpio_init(GPIOD, GPIO_DIR_OUTPUT, 15);


}

