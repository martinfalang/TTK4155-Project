
// Situations to consider:
// The application tries to send a new character while the UART is busy transmitting the previous one
//   Solution: Wait until the UART is finished transmitting the previous one by reading the flag
// The application wants to be notified when a new character is received
//   Solution: Provide a callback function that is called each time a character is recieved

void uart_init() {
    // Initialize the uart module on the chip
}


void send_char(char c) {

}

char read_char() {

}