/*
 * gpio_driver.h
 *
 *  Created on: Jun 30, 2024
 *      Author: Kanbocum
 */

#ifndef INC_GPIO_DRIVER_H_
#define INC_GPIO_DRIVER_H_


// GPIO yönü için tanımlar
#define GPIO_DIR_INPUT  0
#define GPIO_DIR_OUTPUT 1


#define 	GPIO_PIN_0   ((uint16_t)0x0001) /* Pin 0 selected */
#define 	GPIO_PIN_1   ((uint16_t)0x0002) /* Pin 1 selected */
#define 	GPIO_PIN_2   ((uint16_t)0x0004) /* Pin 2 selected */
#define 	GPIO_PIN_3   ((uint16_t)0x0008) /* Pin 3 selected */
#define 	GPIO_PIN_4   ((uint16_t)0x0010) /* Pin 4 selected */
#define 	GPIO_PIN_5   ((uint16_t)0x0020) /* Pin 5 selected */
#define 	GPIO_PIN_6   ((uint16_t)0x0040) /* Pin 6 selected */
#define 	GPIO_PIN_7   ((uint16_t)0x0080) /* Pin 7 selected */
#define 	GPIO_PIN_8   ((uint16_t)0x0100) /* Pin 8 selected */
#define 	GPIO_PIN_9   ((uint16_t)0x0200) /* Pin 9 selected */
#define 	GPIO_PIN_10   ((uint16_t)0x0400) /* Pin 10 selected */
#define 	GPIO_PIN_11   ((uint16_t)0x0800) /* Pin 11 selected */
#define 	GPIO_PIN_12   ((uint16_t)0x1000) /* Pin 12 selected */
#define 	GPIO_PIN_13   ((uint16_t)0x2000) /* Pin 13 selected */
#define 	GPIO_PIN_14   ((uint16_t)0x4000) /* Pin 14 selected */
#define 	GPIO_PIN_15   ((uint16_t)0x8000) /* Pin 15 selected */
#define 	GPIO_PIN_All   ((uint16_t)0xFFFF) /* All pins selected */
#define 	GPIO_PIN_MASK   0x0000FFFFU /* PIN mask for assert test */


void gpio_init(GPIO_TypeDef *gpio_port, uint32_t gpio_dir, uint32_t gpio_pin);
void gpio_all_init(void);




#endif /* INC_GPIO_DRIVER_H_ */
