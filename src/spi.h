#ifndef SPI_H
#define SPI_H

#define DD_SS       DDB4
#define DD_MOSI     DDB5
#define DD_MISO     DDB6
#define DD_SCK      DDB7

#define DDR_SPI     DDRB
#define SPI_PORT    PORTB 

void spi_master_init(void);

void spi_select(void);
void spi_deselect(void);

void spi_write_byte(unsigned char data);
unsigned char spi_read_byte(void);


#endif // SPI_H