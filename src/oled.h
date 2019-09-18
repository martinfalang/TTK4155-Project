/*
    Drawing screen buffer towards SSD1780 OLED driver module
*/

// Lifecycle functions
void oled_init(void);

// Drawing functions
void oled_draw_screen(uint8_t *buffer);
