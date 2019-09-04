#include <stdlib.h>
#include <stdint.h>
#include <stdio.h>

#define BYTE_TO_BINARY_PATTERN "%c%c%c%c%c%c%c%c"
#define BYTE_TO_BINARY(byte)  \
  (byte & 0x80 ? '1' : '0'), \
  (byte & 0x40 ? '1' : '0'), \
  (byte & 0x20 ? '1' : '0'), \
  (byte & 0x10 ? '1' : '0'), \
  (byte & 0x08 ? '1' : '0'), \
  (byte & 0x04 ? '1' : '0'), \
  (byte & 0x02 ? '1' : '0'), \
  (byte & 0x01 ? '1' : '0') 

void SRAM_test(void)
{
    volatile char *ext_ram = (char *)0x1800; // Start address for the SRAM
    uint16_t ext_ram_size = 0x800;
    uint16_t write_errors = 0;
    uint16_t retrieval_errors = 0;
    printf("Starting SRAM test...\n");
    // rand() stores some internal state, so calling this function in a loop will
    // yield different seeds each time (unless srand() is called before this function)
    uint16_t seed = rand();

    // Write phase: Immediately check that the correct value was stored
    srand(seed);
    printf("Starting write phase...\n");
    uint8_t d = 0;
    for (uint16_t i = 0; i < ext_ram_size; i++)
    {
        uint8_t some_value = d; //rand();
        ++d;
        ext_ram[i] = some_value;
        uint8_t retreived_value = ext_ram[i];
        if (retreived_value != some_value)
        {

            printf("Write phase error: ext_ram[%4d] = "BYTE_TO_BINARY_PATTERN" = %02X (should be "BYTE_TO_BINARY_PATTERN" = %02X)\n", 
            i, BYTE_TO_BINARY(retreived_value), retreived_value, BYTE_TO_BINARY(some_value), some_value);
            write_errors++;
        }
    }
    printf("End of write phase...\n\n");
    
    printf("Starting reading phase...\n");

    // Retrieval phase: Check that no values were changed during or after the write phase
    srand(seed); // reset the PRNG to the state it had before the write phase
    d = 0;
    for (uint16_t i = 0; i < ext_ram_size; i++)
    {
        uint8_t some_value = d;  // rand();
        ++d;
        uint8_t retreived_value = ext_ram[i];
        if (retreived_value != some_value)
        {
            printf("Retrieval phase error: ext_ram[%4d] = "BYTE_TO_BINARY_PATTERN" = %02X (should be "BYTE_TO_BINARY_PATTERN" = %02X)\n",
                   i, BYTE_TO_BINARY(retreived_value), retreived_value, BYTE_TO_BINARY(some_value), some_value);
            retrieval_errors++;
        }
    }
    printf("SRAM test completed with \n%4d errors in write phase and \n%4d errors in retrieval phase\n\n", write_errors, retrieval_errors);
}