#include "pico/stdlib.h"
#include "hardware/spi.h"
#include "lcd.h"


void lcd_send(uint8_t value, uint8_t mode) {
    gpio_put(LCD_CS_PIN, 0);
    gpio_put(LCD_DC_PIN, mode);
    spi_write_blocking(SPI_PORT, &value, 1);
    gpio_put(LCD_CS_PIN, 1);
}

void lcd_reset() {
    gpio_put(LCD_RST_PIN, 0);
    sleep_ms(100);
    gpio_put(LCD_RST_PIN, 1);
    sleep_ms(100);
}

void lcd_init() {
    // Initialize the GPIO pins
    gpio_init(LCD_RST_PIN);
    gpio_set_dir(LCD_RST_PIN, GPIO_OUT);

    gpio_init(LCD_DC_PIN);
    gpio_set_dir(LCD_DC_PIN, GPIO_OUT);

    gpio_init(LCD_CS_PIN);
    gpio_set_dir(LCD_CS_PIN, GPIO_OUT);

    gpio_init(LCD_BL_PIN);
    gpio_set_dir(LCD_BL_PIN, GPIO_OUT);
    gpio_put(LCD_BL_PIN, 1); // Turn on the backlight

    // Initialize SPI
    spi_init(SPI_PORT, 1000 * 1000);
    gpio_set_function(LCD_CLK_PIN, GPIO_FUNC_SPI);
    gpio_set_function(LCD_MOSI_PIN, GPIO_FUNC_SPI);

    lcd_reset();

    // Initialization sequence for ST7735
    lcd_send(0x01, LCD_CMD); // Software reset
    sleep_ms(150);
    lcd_send(0x11, LCD_CMD); // Exit sleep mode
    sleep_ms(255);

    // More initialization commands as needed...

    lcd_send(0x29, LCD_CMD); // Display ON
}

void lcd_set_address_window(uint8_t x0, uint8_t y0, uint8_t x1, uint8_t y1) {
    lcd_send(0x2A, LCD_CMD);
    lcd_send(0x00, LCD_DATA);
    lcd_send(x0, LCD_DATA);
    lcd_send(0x00, LCD_DATA);
    lcd_send(x1, LCD_DATA);

    lcd_send(0x2B, LCD_CMD);
    lcd_send(0x00, LCD_DATA);
    lcd_send(y0, LCD_DATA);
    lcd_send(0x00, LCD_DATA);
    lcd_send(y1, LCD_DATA);

    lcd_send(0x2C, LCD_CMD);
}

void lcd_draw_pixel(uint8_t x, uint8_t y, uint16_t color) {
    lcd_set_address_window(x, y, x + 1, y + 1);
    lcd_send(color >> 8, LCD_DATA);
    lcd_send(color & 0xFF, LCD_DATA);
}

void lcd_draw_char(uint8_t x, uint8_t y, char c, uint16_t color, uint16_t bg) {

    for (int i = 0; i < 5; i++) {
        uint8_t line = font[(c - ' ') * 5 + i];
        for (int j = 0; j < 8; j++, line >>= 1) {
            if (line & 1) {
                lcd_draw_pixel(x + i, y + j, color);
            } else {
                lcd_draw_pixel(x + i, y + j, bg);
            }
        }
    }
}

void lcd_draw_text(uint8_t x, uint8_t y, const char* text, uint16_t color, uint16_t bg) {
    while (*text) {
        lcd_draw_char(x, y, *text++, color, bg);
        x += 6; // Move to the next character position
    }
}
