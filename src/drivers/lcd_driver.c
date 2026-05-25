/**
 * @file lcd_driver.c
 * @brief LCD LTDC driver implementation
 */

#include "lcd_driver.h"

static LTDC_HandleTypeDef hltdc;

/**
 * @brief Initialize LCD display via LTDC
 */
void LCD_Init(void)
{
    /* LTDC configuration */
    hltdc.Instance = LTDC;
    hltdc.Init.HSPolarity = LTDC_HSYNC_ACTIVE_LOW;
    hltdc.Init.VSPolarity = LTDC_VSYNC_ACTIVE_LOW;
    hltdc.Init.DEPolarity = LTDC_DE_ACTIVE_HIGH;
    hltdc.Init.PCPolarity = LTDC_PC_RISING;
    hltdc.Init.HorizontalSync = LCD_HSPW - 1;
    hltdc.Init.VerticalSync = LCD_VSPW - 1;
    hltdc.Init.AccumulatedHBP = LCD_HSPW + LCD_HBP - 1;
    hltdc.Init.AccumulatedVBP = LCD_VSPW + LCD_VBP - 1;
    hltdc.Init.AccumulatedActiveW = LCD_HSPW + LCD_HBP + LCD_WIDTH - 1;
    hltdc.Init.AccumulatedActiveH = LCD_VSPW + LCD_VBP + LCD_HEIGHT - 1;
    hltdc.Init.TotalWidth = LCD_HSPW + LCD_HBP + LCD_WIDTH + LCD_HFP - 1;
    hltdc.Init.TotalHeigh = LCD_VSPW + LCD_VBP + LCD_HEIGHT + LCD_VFP - 1;
    hltdc.Init.Backcolor.Blue = 0;
    hltdc.Init.Backcolor.Green = 0;
    hltdc.Init.Backcolor.Red = 0;
    
    if (HAL_LTDC_Init(&hltdc) != HAL_OK)
    {
        printf("[ERROR] LTDC initialization failed!\r\n");
        return;
    }
    
    /* Configure layer 1 */
    LTDC_LayerCfgTypeDef layer_cfg = {0};
    layer_cfg.WindowX0 = 0;
    layer_cfg.WindowX1 = LCD_WIDTH;
    layer_cfg.WindowY0 = 0;
    layer_cfg.WindowY1 = LCD_HEIGHT;
    layer_cfg.PixelFormat = LTDC_PIXEL_FORMAT_RGB565;
    layer_cfg.FBStartAdress = FRAMEBUFFER_ADDR;
    layer_cfg.Alpha = 255;
    layer_cfg.Alpha0 = 0;
    layer_cfg.Backcolor.Blue = 0;
    layer_cfg.Backcolor.Green = 0;
    layer_cfg.Backcolor.Red = 0;
    layer_cfg.BlendingFactor1 = LTDC_BLENDING_FACTOR1_PAxCA;
    layer_cfg.BlendingFactor2 = LTDC_BLENDING_FACTOR2_PAxCA;
    layer_cfg.ImageWidth = LCD_WIDTH;
    layer_cfg.ImageHeight = LCD_HEIGHT;
    
    if (HAL_LTDC_ConfigLayer(&hltdc, &layer_cfg, 0) != HAL_OK)
    {
        printf("[ERROR] LTDC layer configuration failed!\r\n");
        return;
    }
    
    HAL_LTDC_ProgramLineEvent(&hltdc, 0);
    
    LCD_INFO.buffer = (uint16_t *)FRAMEBUFFER_ADDR;
    LCD_INFO.width = LCD_WIDTH;
    LCD_INFO.height = LCD_HEIGHT;
    LCD_INFO.size = LCD_WIDTH * LCD_HEIGHT * 2;  /* 2 bytes per pixel (RGB565) */
    
    printf("[OK] LCD LTDC initialized (800x480)\r\n");
}

/**
 * @brief Fill entire LCD with a single color
 * @param color: RGB565 color value
 */
void LCD_Fill_Color(uint16_t color)
{
    uint32_t i;
    for (i = 0; i < LCD_WIDTH * LCD_HEIGHT; i++)
    {
        LCD_INFO.buffer[i] = color;
    }
}

/**
 * @brief Draw a single pixel
 * @param x: X coordinate
 * @param y: Y coordinate
 * @param color: RGB565 color value
 */
void LCD_Draw_Pixel(uint16_t x, uint16_t y, uint16_t color)
{
    if (x < LCD_WIDTH && y < LCD_HEIGHT)
    {
        LCD_INFO.buffer[y * LCD_WIDTH + x] = color;
    }
}

/**
 * @brief Draw a line using Bresenham's algorithm
 * @param x0: Starting X coordinate
 * @param y0: Starting Y coordinate
 * @param x1: Ending X coordinate
 * @param y1: Ending Y coordinate
 * @param color: RGB565 color value
 */
void LCD_Draw_Line(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
    int16_t dx = (x1 > x0) ? (x1 - x0) : (x0 - x1);
    int16_t dy = (y1 > y0) ? (y1 - y0) : (y0 - y1);
    int16_t sx = (x0 < x1) ? 1 : -1;
    int16_t sy = (y0 < y1) ? 1 : -1;
    int16_t err = dx - dy;
    int16_t e2;
    
    while (1)
    {
        LCD_Draw_Pixel(x0, y0, color);
        
        if (x0 == x1 && y0 == y1) break;
        
        e2 = 2 * err;
        if (e2 > -dy)
        {
            err -= dy;
            x0 += sx;
        }
        if (e2 < dx)
        {
            err += dx;
            y0 += sy;
        }
    }
}

/**
 * @brief Draw rectangle outline
 * @param x0: Top-left X coordinate
 * @param y0: Top-left Y coordinate
 * @param x1: Bottom-right X coordinate
 * @param y1: Bottom-right Y coordinate
 * @param color: RGB565 color value
 */
void LCD_Draw_Rectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
    LCD_Draw_Line(x0, y0, x1, y0, color);  /* Top line */
    LCD_Draw_Line(x0, y1, x1, y1, color);  /* Bottom line */
    LCD_Draw_Line(x0, y0, x0, y1, color);  /* Left line */
    LCD_Draw_Line(x1, y0, x1, y1, color);  /* Right line */
}

/**
 * @brief Draw filled rectangle
 * @param x0: Top-left X coordinate
 * @param y0: Top-left Y coordinate
 * @param x1: Bottom-right X coordinate
 * @param y1: Bottom-right Y coordinate
 * @param color: RGB565 color value
 */
void LCD_Draw_Filled_Rectangle(uint16_t x0, uint16_t y0, uint16_t x1, uint16_t y1, uint16_t color)
{
    uint16_t x, y;
    for (y = y0; y <= y1; y++)
    {
        for (x = x0; x <= x1; x++)
        {
            LCD_Draw_Pixel(x, y, color);
        }
    }
}
