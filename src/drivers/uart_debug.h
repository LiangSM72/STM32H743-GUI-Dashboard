/**
 * @file uart_debug.h
 * @brief UART debug and printf redirection header
 */

#ifndef __UART_DEBUG_H
#define __UART_DEBUG_H

#include "stm32h7xx_hal.h"
#include <stdio.h>

void UART_Debug_Init(void);

#endif /* __UART_DEBUG_H */
