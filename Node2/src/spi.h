#ifndef SPI_H
#define SPI_H

#define DD_SS       DDB7
#define DD_MOSI     DDB2
#define DD_MISO     DDB3
#define DD_SCK      DDB1

#define DDR_SPI     DDRB
#define SPI_PORT    PORTB 

void spi_init(void);

void spi_slave_select(void);
void spi_slave_deselect(void);

void spi_write_byte(unsigned char data);
unsigned char spi_read_byte(void);

#endif // SPI_H