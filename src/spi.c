
#include "spi.h"

#include <avr/io.h>
#include <avr/interrupt.h>

void spi_init(void) {
    
    // Set MOSI, SCK and SS as output 
    DDR_SPI |= (1 << DD_MOSI) | (1 << DD_SCK) | (1 << DD_SS);
    
    // Set MISO (used SS as input earlier)
    DDR_SPI &= ~(1 << DD_MISO);// | (1 << DD_SS));

    // Enable SPI, set ATmega162 to master, set clock speed to f_osc/16
    SPCR |= (1 << SPE) | (1 << MSTR) | (1 << SPR0);

    // Set SS pin high
    spi_slave_deselect();
}

void spi_slave_select(void) {
    // Set SS low
    SPI_PORT &= ~(1 << DD_SS);
}

void spi_slave_deselect(void) {
    // Set SS high
    SPI_PORT |= (1 << DD_SS);
}

void spi_write_byte(unsigned char data) {

    // Start transmission
    SPDR = data;

    // Wait for transmission to complete
    while(!(SPSR & (1 << SPIF)));
}

unsigned char spi_read_byte(void) {

    // Write dummy byte to start reading process
    SPDR = 0x00;
    
    // Wait for transmission to complete
    while(!(SPSR & (1 << SPIF)));
    
    // Read the byte sent from slave
    unsigned char data = SPDR;

    return data;
}