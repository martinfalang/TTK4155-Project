#ifndef DAC_H
#define DAC_H

#define DAC_SLAVE_ADDR      0x50
#define DAC_RESET_bm        0x10
#define DAC_POWER_DOWM_bm   0x08
#define DAC_OUT0_bm         0x00
#define DAC_OUT1_bm         0x01
#define DAC_OUT2_bm         0x02
#define DAC_OUT3_bm         0x03




void dac_init(void);
void dac_write(unsigned char level, int outn);


#endif  // DAC_H