/**
 * @file keypad.c
 * @brief 4x4 Matrix keypad driver implementation
 */

#include "keypad.h"
#include "gpio_init.h"

static uint8_t last_key = KEYPAD_NO_KEY;
static uint8_t current_key = KEYPAD_NO_KEY;
static uint16_t debounce_counter = 0;

/**
 * @brief Initialize keypad pins
 */
void Keypad_Init(void)
{
    /* GPIO initialization is done in GPIO_Init() */
    printf("[OK] Keypad initialized\r\n");
}

/**
 * @brief Scan the 4x4 keypad matrix
 */
void Keypad_Scan(void)
{
    uint8_t row, col;
    GPIO_PinState state;
    uint8_t key_pressed = KEYPAD_NO_KEY;
    
    for (row = 0; row < KEYPAD_ROWS; row++)
    {
        /* Set current row to LOW, others to HIGH */
        HAL_GPIO_WritePin(KEYPAD_ROW0_PORT, KEYPAD_ROW0_PIN, (row == 0) ? GPIO_PIN_RESET : GPIO_PIN_SET);
        HAL_GPIO_WritePin(KEYPAD_ROW1_PORT, KEYPAD_ROW1_PIN, (row == 1) ? GPIO_PIN_RESET : GPIO_PIN_SET);
        HAL_GPIO_WritePin(KEYPAD_ROW2_PORT, KEYPAD_ROW2_PIN, (row == 2) ? GPIO_PIN_RESET : GPIO_PIN_SET);
        HAL_GPIO_WritePin(KEYPAD_ROW3_PORT, KEYPAD_ROW3_PIN, (row == 3) ? GPIO_PIN_RESET : GPIO_PIN_SET);
        
        /* Small delay for signal settling */
        HAL_Delay(2);
        
        /* Read columns */
        for (col = 0; col < KEYPAD_COLS; col++)
        {
            if (col == 0)
                state = HAL_GPIO_ReadPin(KEYPAD_COL0_PORT, KEYPAD_COL0_PIN);
            else if (col == 1)
                state = HAL_GPIO_ReadPin(KEYPAD_COL1_PORT, KEYPAD_COL1_PIN);
            else if (col == 2)
                state = HAL_GPIO_ReadPin(KEYPAD_COL2_PORT, KEYPAD_COL2_PIN);
            else
                state = HAL_GPIO_ReadPin(KEYPAD_COL3_PORT, KEYPAD_COL3_PIN);
            
            /* If column is LOW, key is pressed */
            if (state == GPIO_PIN_RESET)
            {
                key_pressed = row * 4 + col;
                break;
            }
        }
        
        if (key_pressed != KEYPAD_NO_KEY)
            break;
    }
    
    /* Debounce logic */
    if (key_pressed == current_key)
    {
        debounce_counter++;
        if (debounce_counter > 20)  /* Debounce threshold */
        {
            if (key_pressed != last_key)
            {
                last_key = key_pressed;
            }
        }
    }
    else
    {
        current_key = key_pressed;
        debounce_counter = 0;
    }
}

/**
 * @brief Get pressed key (non-blocking)
 * @return Key number (0-15) or 0xFF if no key pressed
 */
uint8_t Keypad_Get_Key(void)
{
    uint8_t key = last_key;
    last_key = KEYPAD_NO_KEY;
    return key;
}
