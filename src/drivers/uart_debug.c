/**
 * @file uart_debug.c
 * @brief UART debug implementation and printf redirection
 */

#include "uart_debug.h"

static UART_HandleTypeDef huart;

/**
 * @brief Initialize UART1 for debug output
 */
void UART_Debug_Init(void)
{
    /* Enable USART1 clock */
    __HAL_RCC_USART1_CLK_ENABLE();
    
    /* Configure UART parameters */
    huart.Instance = USART1;
    huart.Init.BaudRate = 115200;
    huart.Init.WordLength = UART_WORDLENGTH_8B;
    huart.Init.StopBits = UART_STOPBITS_1;
    huart.Init.Parity = UART_PARITY_NONE;
    huart.Init.Mode = UART_MODE_TX_RX;
    huart.Init.HwFlowCtl = UART_HWCONTROL_NONE;
    huart.Init.OverSampling = UART_OVERSAMPLING_16;
    
    if (HAL_UART_Init(&huart) != HAL_OK)
    {
        printf("[ERROR] UART initialization failed!\r\n");
    }
}

/**
 * @brief Retarget printf to UART
 */
int _write(int file, char *ptr, int len)
{
    (void)file;  /* Unused */
    HAL_UART_Transmit(&huart, (uint8_t *)ptr, len, HAL_MAX_DELAY);
    return len;
}
