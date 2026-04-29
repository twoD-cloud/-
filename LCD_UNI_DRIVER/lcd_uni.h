#ifndef LCD_UNI_H
#define LCD_UNI_H

#include "board.h"

#ifdef __cplusplus
extern "C" {
#endif


#define LCD_TYPE_ST7735      0    /*ST7735*/
#define LCD_TYPE_SSD1315   1    /*SSD1315*/

// set type of lcd
void lcd_uni_set_type(uint8_t type);

// uni initial
uint8_t lcd_uni_init(void);

// cleardisplay
void lcd_uni_clear(uint16_t color);

// show str, for ssd1315 color is set to white and black
void lcd_uni_show_string(uint16_t x, uint16_t y, const char *str, uint16_t color, uint8_t font_size);

// fill rect at AABB area
void lcd_uni_fill_rect(uint16_t left, uint16_t top, uint16_t right, uint16_t bottom, uint16_t color);

// draw point at x y
void lcd_uni_draw_point(uint16_t x, uint16_t y, uint16_t color);

// show image
void lcd_uni_show_picture(uint16_t x, uint16_t y, uint16_t width, uint16_t height, const uint8_t *img);

// enable or disable display
void lcd_uni_display_on(void);
void lcd_uni_display_off(void);

#ifdef __cplusplus
}
#endif

#endif
