
#include "spi.h"

#include <avr/io.h>
#include <avr/interrupt.h>

#include <stdio.h> // Remove after testing

void spi_master_init(void) {
    
    // Set MOSI and SCK output
    DDR_SPI |= (1 << DD_MOSI) | (1 << DD_SCK);
    // Set MISO and SS input
    DDR_SPI &= ~((1 << DD_MISO) | (1 << DD_SS));

    // Enable SPI, set ATmega162 to master, //enable SPI interrupt
    SPCR |= (1 << SPE) | (1 << MSTR);// | (1 << SPIE);

    // Enable global interrupts
    //sei();

    // Set clock speed to f_osc/16
    SPCR |= (1 << SPR0);

    // Set SS pin high
    SPI_PORT |= (1 << DD_SS);
}

void spi_master_transmit(char data) {
    // Start transmission
    SPDR = data;

    // Wait for transmission to complete
    while(!(SPSR & (1 << SPIF)));
}

unsigned char spi_read(void) {
    SPDR = 0x00;
    
    while(!(SPSR & (1 << SPIF)));
    
    unsigned char data = SPDR;

    return data;
}
