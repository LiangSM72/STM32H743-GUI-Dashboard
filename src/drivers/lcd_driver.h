/**
 * @file lcd_driver.h
 * @brief LCD LTDC driver for 800x480 display
 */

#ifndef __LCD_DRIVER_H
#define __LCD_DRIVER_H

#include "stm32h7xx_hal.h"

/* LCD parameters */
#define LCD_WIDTH           800
#define LCD_HEIGHT          480
#define LCD_HSPW            10   /* Horizontal sync pulse width */
#define LCD_HBP             46   /* Horizontal back porch */
#define LCD_HFP             16   /* Horizontal front porch */
#define LCD_VSPW            10   /* Vertical sync pulse width */
#define LCD_VBP             23   /* Vertical back porch */
#define LCD_VFP             7    /* Vertical front porch */

/* Color definitions (RGB565) */
#define LCD_COLOR_BLACK     0x0000
#define LCD_COLOR_RED       0xF800
#define LCD_COLOR_GREEN     0x07E0
#define LCD_COLOR_BLUE      0x001F
#define LCD_COLOR_WHITE     0xFFFF
#define LCD_COLOR_YELLOW    0xFFE0
#define LCD_COLOR_CYAN      0x07FF
#define LCD_COLOR_MAGENTA   0xF81F

/* Framebuffer address */
#define FRAMEBUFFER_ADDR    0xC0000000

struct {
    uint16_t *buffer;
    uint32_t width;
    uint32_t height;
    uint32_t size;
} LCD_INFO;

void LCD_Init(void);
void LCD_Fill_Color(uint16_t color);
void LCD_Draw_Pixel(uint16_t x, uint16_t y, uint16_t color);
void LCD_Draw_Line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
void LCD_Draw_Rectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);
void LCD_Draw_Filled_Rectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color);

#endif /* __LCD_DRIVER_H */
