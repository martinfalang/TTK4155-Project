/*
    Drawing screen buffer towards SSD1780 OLED driver module
*/
#ifndef OLED_H
#define OLED_H

// Lifecycle functions
void oled_init(void);

// Drawing functions
void oled_draw_screen(uint8_t *buffer);

#endif /* OLED_H */