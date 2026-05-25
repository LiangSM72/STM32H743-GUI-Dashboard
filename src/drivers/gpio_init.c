/**
 * @file gpio_init.c
 * @brief GPIO initialization implementation
 */

#include "gpio_init.h"

/**
 * @brief Initialize all GPIO pins
 */
void GPIO_Init(void)
{
    GPIO_InitTypeDef GPIO_InitStruct = {0};
    
    /* Enable GPIO clocks */
    __HAL_RCC_GPIOA_CLK_ENABLE();
    __HAL_RCC_GPIOB_CLK_ENABLE();
    __HAL_RCC_GPIOC_CLK_ENABLE();
    __HAL_RCC_GPIOD_CLK_ENABLE();
    __HAL_RCC_GPIOE_CLK_ENABLE();
    __HAL_RCC_GPIOF_CLK_ENABLE();
    
    /* Configure UART pins (PA9=TX, PA10=RX) */
    GPIO_InitStruct.Pin = UART_TX_PIN | UART_RX_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF7_USART1;
    HAL_GPIO_Init(GPIOA, &GPIO_InitStruct);
    
    /* Configure Keypad Row pins (output) */
    GPIO_InitStruct.Pin = KEYPAD_ROW0_PIN | KEYPAD_ROW1_PIN | 
                         KEYPAD_ROW2_PIN | KEYPAD_ROW3_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_OUTPUT_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOB, &GPIO_InitStruct);
    
    /* Configure Keypad Column pins (input with pull-up) */
    GPIO_InitStruct.Pin = KEYPAD_COL0_PIN | KEYPAD_COL1_PIN | 
                         KEYPAD_COL2_PIN | KEYPAD_COL3_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_INPUT;
    GPIO_InitStruct.Pull = GPIO_PULLUP;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_LOW;
    HAL_GPIO_Init(GPIOC, &GPIO_InitStruct);
    
    /* Configure LCD control pins (LTDC alternate function) */
    GPIO_InitStruct.Pin = LCD_CLK_PIN | LCD_HSYNC_PIN | 
                         LCD_VSYNC_PIN | LCD_DE_PIN | LCD_D0_PIN | LCD_D1_PIN;
    GPIO_InitStruct.Mode = GPIO_MODE_AF_PP;
    GPIO_InitStruct.Pull = GPIO_NOPULL;
    GPIO_InitStruct.Speed = GPIO_SPEED_FREQ_VERY_HIGH;
    GPIO_InitStruct.Alternate = GPIO_AF14_LTDC;
    HAL_GPIO_Init(GPIOE, &GPIO_InitStruct);
    
    /* Initialize all keypad rows to high */
    HAL_GPIO_WritePin(KEYPAD_ROW0_PORT, KEYPAD_ROW0_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(KEYPAD_ROW1_PORT, KEYPAD_ROW1_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(KEYPAD_ROW2_PORT, KEYPAD_ROW2_PIN, GPIO_PIN_SET);
    HAL_GPIO_WritePin(KEYPAD_ROW3_PORT, KEYPAD_ROW3_PIN, GPIO_PIN_SET);
}
