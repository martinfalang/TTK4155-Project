#ifndef SPI_H
#define SPI_H

////////////////////////////////////////////////////////////////////////////////
// Defines
////////////////////////////////////////////////////////////////////////////////

#if defined (__AVR_ATmega162__)
    #define DD_SS       DDB4
    #define DD_MOSI     DDB5
    #define DD_MISO     DDB6
    #define DD_SCK      DDB7
#elif defined (__AVR_ATmega2560__)
    #define DD_SS       DDB7
    #define DD_MOSI     DDB2
    #define DD_MISO     DDB3
    #define DD_SCK      DDB1
#endif

#define DDR_SPI     DDRB
#define SPI_PORT    PORTB 

////////////////////////////////////////////////////////////////////////////////
// Function declarations
////////////////////////////////////////////////////////////////////////////////

/**
 * @brief Initialize SPI bus in master mode
 * 
 */
void spi_init(void);

/**
 * @brief Pull the slave select (SS) pin low
 * 
 */
void spi_slave_select(void);

/**
 * @brief Pull the slave select (SS) pin high
 * 
 */
void spi_slave_deselect(void);

/**
 * @brief Write a byte to the SPI bus. This functions assumes a slave is 
 *        selected.
 * 
 * @param data 
 */
void spi_write_byte(unsigned char data);

/**
 * @brief Read a byte from the SPI bus. This functions assumes a slave is 
 *        selected.
 * 
 * @return unsigned char The byte read
 */
unsigned char spi_read_byte(void);

#endif // SPI_H