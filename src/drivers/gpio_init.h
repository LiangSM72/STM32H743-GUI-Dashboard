/**
 * @file gpio_init.h
 * @brief GPIO initialization for LCD, keypad, and other peripherals
 */

#ifndef __GPIO_INIT_H
#define __GPIO_INIT_H

#include "stm32h7xx_hal.h"

/* LCD GPIO Pins */
#define LCD_CLK_PORT         GPIOE
#define LCD_CLK_PIN          GPIO_PIN_2

#define LCD_HSYNC_PORT       GPIOE
#define LCD_HSYNC_PIN        GPIO_PIN_3

#define LCD_VSYNC_PORT       GPIOE
#define LCD_VSYNC_PIN        GPIO_PIN_4

#define LCD_DE_PORT          GPIOE
#define LCD_DE_PIN           GPIO_PIN_5

/* LCD Data Pins (8-bit parallel interface) */
#define LCD_D0_PORT          GPIOE
#define LCD_D0_PIN           GPIO_PIN_6

#define LCD_D1_PORT          GPIOE
#define LCD_D1_PIN           GPIO_PIN_7

/* Backlight PWM Pin */
#define BACKLIGHT_PORT       GPIOE
#define BACKLIGHT_PIN        GPIO_PIN_8

/* UART Debug Pins */
#define UART_TX_PORT         GPIOA
#define UART_TX_PIN          GPIO_PIN_9

#define UART_RX_PORT         GPIOA
#define UART_RX_PIN          GPIO_PIN_10

/* Keypad Row/Column Pins */
#define KEYPAD_ROW0_PORT     GPIOB
#define KEYPAD_ROW0_PIN      GPIO_PIN_0

#define KEYPAD_ROW1_PORT     GPIOB
#define KEYPAD_ROW1_PIN      GPIO_PIN_1

#define KEYPAD_ROW2_PORT     GPIOB
#define KEYPAD_ROW2_PIN      GPIO_PIN_2

#define KEYPAD_ROW3_PORT     GPIOB
#define KEYPAD_ROW3_PIN      GPIO_PIN_3

#define KEYPAD_COL0_PORT     GPIOC
#define KEYPAD_COL0_PIN      GPIO_PIN_4

#define KEYPAD_COL1_PORT     GPIOC
#define KEYPAD_COL1_PIN      GPIO_PIN_5

#define KEYPAD_COL2_PORT     GPIOC
#define KEYPAD_COL2_PIN      GPIO_PIN_6

#define KEYPAD_COL3_PORT     GPIOC
#define KEYPAD_COL3_PIN      GPIO_PIN_7

void GPIO_Init(void);

#endif /* __GPIO_INIT_H */
