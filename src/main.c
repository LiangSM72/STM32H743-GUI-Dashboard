/**
 * @file main.c
 * @brief STM32H743 GUI Dashboard - Main Program
 * 
 * This is the main entry point for the STM32H743 GUI Dashboard system.
 * It initializes all hardware components and runs the main application loop.
 */

#include "stm32h7xx_hal.h"
#include "drivers/clock.h"
#include "drivers/gpio_init.h"
#include "drivers/sdram_init.h"
#include "drivers/lcd_driver.h"
#include "drivers/backlight.h"
#include "drivers/keypad.h"
#include "drivers/uart_debug.h"

/**
 * @brief Main application entry point
 * @return Never returns
 */
int main(void)
{
    /* Initialize HAL library */
    HAL_Init();
    
    /* Configure system clock to 400MHz */
    SystemClock_Config();
    
    /* Initialize UART for debugging (printf redirection) */
    UART_Debug_Init();
    
    printf("\r\n========================================\r\n");
    printf("STM32H743 GUI Dashboard System\r\n");
    printf("Booting...\r\n");
    printf("========================================\r\n");
    
    /* Initialize GPIO pins for LCD, backlight, and other peripherals */
    GPIO_Init();
    printf("[OK] GPIO initialized\r\n");
    
    /* Initialize SDRAM for framebuffer storage */
    SDRAM_Init();
    printf("[OK] SDRAM initialized (256MB)\r\n");
    
    /* Initialize LCD LTDC controller */
    LCD_Init();
    printf("[OK] LCD initialized (800x480)\r\n");
    
    /* Initialize backlight PWM control */
    Backlight_Init();
    Backlight_Set_Brightness(100);  // Set to 100%
    printf("[OK] Backlight initialized (100%%)\r\n");
    
    /* Initialize keypad scanning */
    Keypad_Init();
    printf("[OK] Keypad initialized\r\n");
    
    printf("========================================\r\n");
    printf("System boot complete!\r\n");
    printf("========================================\r\n\r\n");
    
    /* Fill LCD with black color for initial display test */
    LCD_Fill_Color(0x0000);  // Black
    
    /* Main application loop */
    while (1)
    {
        /* Scan keypad for input */
        Keypad_Scan();
        
        /* Check if any key was pressed */
        uint8_t key = Keypad_Get_Key();
        if (key != 0xFF)
        {
            printf("Key pressed: %d (Row: %d, Col: %d)\r\n", 
                   key, key / 4, key % 4);
        }
        
        /* Add small delay to prevent CPU overload */
        HAL_Delay(50);
    }
    
    return 0;
}

/**
 * @brief System clock configuration function
 * 
 * Configures the STM32H743 to run at 400MHz:
 * - CPU: Cortex-M7 @ 400MHz
 * - AHB: 200MHz
 * - APB1/APB2: 100MHz
 * - APB3/APB4: 100MHz
 */
void SystemClock_Config(void)
{
    RCC_OscInitTypeDef RCC_OscInitStruct = {0};
    RCC_ClkInitTypeDef RCC_ClkInitStruct = {0};
    
    /* Enable HSE oscillator and configure the PLL */
    RCC_OscInitStruct.OscillatorType = RCC_OSCILLATORTYPE_HSE;
    RCC_OscInitStruct.HSEState = RCC_HSE_ON;
    RCC_OscInitStruct.PLL.PLLState = RCC_PLL_ON;
    RCC_OscInitStruct.PLL.PLLSource = RCC_PLLSOURCE_HSE;
    RCC_OscInitStruct.PLL.PLLM = 5;
    RCC_OscInitStruct.PLL.PLLN = 160;
    RCC_OscInitStruct.PLL.PLLP = 2;
    RCC_OscInitStruct.PLL.PLLQ = 4;
    RCC_OscInitStruct.PLL.PLLR = 2;
    RCC_OscInitStruct.PLL.PLLVCOSEL = RCC_PLL_VCORANGE_2;
    RCC_OscInitStruct.PLL.PLLRGE = RCC_PLL_RANGE_2;
    
    if (HAL_RCC_OscConfig(&RCC_OscInitStruct) != HAL_OK)
    {
        Error_Handler();
    }
    
    /* Configure clock dividers */
    RCC_ClkInitStruct.ClockType = RCC_CLOCKTYPE_HCLK | RCC_CLOCKTYPE_SYSCLK |
                                  RCC_CLOCKTYPE_PCLK1 | RCC_CLOCKTYPE_PCLK2 |
                                  RCC_CLOCKTYPE_D3PCLK1 | RCC_CLOCKTYPE_D1PCLK1;
    RCC_ClkInitStruct.SYSCLKSource = RCC_SYSCLKSOURCE_PLLCLK;
    RCC_ClkInitStruct.AHBCLKDivider = RCC_SYSCLK_DIV2;
    RCC_ClkInitStruct.APB1CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB2CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB3CLKDivider = RCC_HCLK_DIV2;
    RCC_ClkInitStruct.APB4CLKDivider = RCC_HCLK_DIV2;
    
    if (HAL_RCC_ClockConfig(&RCC_ClkInitStruct, FLASH_LATENCY_4) != HAL_OK)
    {
        Error_Handler();
    }
}

/**
 * @brief Error handler - called when any hardware initialization fails
 */
void Error_Handler(void)
{
    printf("[ERROR] System initialization failed!\r\n");
    while (1)
    {
        HAL_Delay(100);
    }
}

/**
 * @brief Override weak SysTick_Handler for HAL
 */
void SysTick_Handler(void)
{
    HAL_IncTick();
}
