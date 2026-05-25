/**
 * @file backlight.c
 * @brief Backlight PWM control implementation
 */

#include "backlight.h"

static TIM_HandleTypeDef htim;
static uint8_t current_brightness = 100;

/**
 * @brief Initialize PWM for backlight control
 */
void Backlight_Init(void)
{
    TIM_OC_InitTypeDef sConfigOC = {0};
    
    /* Enable TIM8 clock */
    __HAL_RCC_TIM8_CLK_ENABLE();
    
    /* Configure TIM8 */
    htim.Instance = TIM8;
    htim.Init.Prescaler = 0;
    htim.Init.CounterMode = TIM_COUNTERMODE_UP;
    htim.Init.Period = 1000;  /* 1000 for 0.1% resolution */
    htim.Init.ClockDivision = TIM_CLOCKDIVISION_DIV1;
    
    if (HAL_TIM_PWM_Init(&htim) != HAL_OK)
    {
        printf("[ERROR] Backlight PWM initialization failed!\r\n");
        return;
    }
    
    /* Configure PWM output on channel 1 (PE8) */
    sConfigOC.OCMode = TIM_OCMODE_PWM1;
    sConfigOC.Pulse = 1000;  /* 100% duty cycle */
    sConfigOC.OCPolarity = TIM_OCPOLARITY_HIGH;
    sConfigOC.OCFastMode = TIM_OCFAST_DISABLE;
    
    if (HAL_TIM_PWM_ConfigChannel(&htim, &sConfigOC, TIM_CHANNEL_1) != HAL_OK)
    {
        printf("[ERROR] Backlight PWM channel configuration failed!\r\n");
        return;
    }
    
    /* Start PWM generation */
    if (HAL_TIM_PWM_Start(&htim, TIM_CHANNEL_1) != HAL_OK)
    {
        printf("[ERROR] Backlight PWM start failed!\r\n");
        return;
    }
    
    printf("[OK] Backlight PWM initialized\r\n");
}

/**
 * @brief Set backlight brightness
 * @param brightness: 0-100 (percentage)
 */
void Backlight_Set_Brightness(uint8_t brightness)
{
    if (brightness > 100)
        brightness = 100;
    
    current_brightness = brightness;
    
    /* Set PWM duty cycle */
    uint32_t pulse = (brightness * 1000) / 100;
    __HAL_TIM_SET_COMPARE(&htim, TIM_CHANNEL_1, pulse);
    
    printf("[OK] Backlight brightness set to %d%%\r\n", brightness);
}

/**
 * @brief Get current backlight brightness
 * @return Brightness (0-100%)
 */
uint8_t Backlight_Get_Brightness(void)
{
    return current_brightness;
}
