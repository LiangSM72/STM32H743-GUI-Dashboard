/**
 * @file backlight.h
 * @brief Backlight PWM control header
 */

#ifndef __BACKLIGHT_H
#define __BACKLIGHT_H

#include "stm32h7xx_hal.h"

void Backlight_Init(void);
void Backlight_Set_Brightness(uint8_t brightness);  /* 0-100% */
uint8_t Backlight_Get_Brightness(void);

#endif /* __BACKLIGHT_H */
