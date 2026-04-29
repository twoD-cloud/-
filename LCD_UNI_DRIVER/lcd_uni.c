#include "lcd_uni.h"
#include "LCD_init/lcd_init.h"
#include "LCD_init/lcd.h"
#include "LCD_1315/driver_ssd1315_advance.h"
#include <string.h>

static uint8_t g_lcd_type = LCD_TYPE_ST7735;

void lcd_uni_set_type(uint8_t type)
{
    g_lcd_type = type;
}

uint8_t lcd_uni_init(void)
{
    if (g_lcd_type == LCD_TYPE_SSD1315)
    {
        return ssd1315_advance_init(SSD1315_INTERFACE_IIC, SSD1315_ADDR_SA0_0);
    }
    else
    {
        LCD_Init();
        return 0;
    }
}

void lcd_uni_clear(uint16_t color)
{
    if (g_lcd_type == LCD_TYPE_SSD1315)
    {
        ssd1315_advance_clear();
    }
    else
    {
        LCD_Fill(0, 0, LCD_W, LCD_H, color);
    }
}

void lcd_uni_show_string(uint16_t x, uint16_t y, const char *str, uint16_t color, uint8_t font_size)
{
    if (g_lcd_type == LCD_TYPE_SSD1315)
    {
        ssd1315_font_t font;

        switch (font_size)
        {
            case 12:
                font = SSD1315_FONT_12;
                break;
            case 16:
                font = SSD1315_FONT_16;
                break;
            case 24:
                font = SSD1315_FONT_24;
                break;
            default:
                font = SSD1315_FONT_16;
                break;
        }
        ssd1315_advance_string((uint8_t)x, (uint8_t)y, (char *)str,
                              (uint16_t)strlen(str), color ? 1 : 0, font);
    }
    else
    {
        LCD_ShowString(x, y, (const u8 *)str, color, 0x0000, (u8)font_size, 0);
    }
}

void lcd_uni_fill_rect(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom, uint16_t color)
{
    if (g_lcd_type == LCD_TYPE_SSD1315)
    {
        ssd1315_advance_rect((uint8_t)left, (uint8_t)top,
                            (uint8_t)right, (uint8_t)bottom,
                            color ? 1 : 0);
    }
    else
    {
        LCD_Fill(left, top, right + 1, bottom + 1, color);
    }
}

void lcd_uni_draw_point(uint16_t x, uint16_t y, uint16_t color)
{
    if (g_lcd_type == LCD_TYPE_SSD1315)
    {
        ssd1315_advance_write_point((uint8_t)x, (uint8_t)y, color ? 1 : 0);
    }
    else
    {
        LCD_DrawPoint(x, y, color);
    }
}

void lcd_uni_show_picture(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t *img)
{
    if (g_lcd_type == LCD_TYPE_SSD1315)
    {
        ssd1315_advance_picture((uint8_t)x, (uint8_t)y,
                               (uint8_t)(x + width - 1), (uint8_t)(y + height - 1),
                               (uint8_t *)img);
    }
    else
    {
        LCD_ShowPicture(x, y, width, height, img);
    }
}

void lcd_uni_display_on(void)
{
    if (g_lcd_type == LCD_TYPE_SSD1315)
    {
        ssd1315_advance_display_on();
    }
}

void lcd_uni_display_off(void)
{
    if (g_lcd_type == LCD_TYPE_SSD1315)
    {
        ssd1315_advance_display_off();
    }
}
