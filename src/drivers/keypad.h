/**
 * @file keypad.h
 * @brief 4x4 Matrix keypad driver header
 */

#ifndef __KEYPAD_H
#define __KEYPAD_H

#include "stm32h7xx_hal.h"

#define KEYPAD_ROWS     4
#define KEYPAD_COLS     4
#define KEYPAD_NO_KEY   0xFF

void Keypad_Init(void);
void Keypad_Scan(void);
uint8_t Keypad_Get_Key(void);

#endif /* __KEYPAD_H */
