#ifndef SPI_H
#define SPI_H

#define DD_SS       DDB4
#define DD_MOSI     DDB5
#define DD_MISO     DDB6
#define DD_SCK      DDB7

#define DDR_SPI     DDRB
#define SPI_PORT    PORTB 

void spi_master_init(void);
void spi_master_transmit(char data);
unsigned char spi_read(void);

// For testing
unsigned char spi_trancieve(unsigned char data);

#endif // SPI_H