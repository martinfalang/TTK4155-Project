#ifndef XMEM_H
#define XMEM_H

// Sizes are in number of bytes
// BASE addresses are uint8_t* because each memory
// location contains 1 byte of data.
#define OLED_CMD_BASE (uint8_t*)0x1000
#define OLED_CMD_SIZE 512
#define OLED_DATA_BASE (uint8_t*)0x1200
#define OLED_DATA_SIZE 512
#define ADC_BASE    (uint8_t*)0x1400
#define ADC_SIZE    1024
#define SRAM_BASE   (uint8_t*)0x1800
#define SRAM_SIZE   2048



void xmem_init(void);

#endif /* XMEM_H */