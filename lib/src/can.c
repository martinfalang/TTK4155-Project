
////////////////////////////////////////////////////////////////////////////////
// Includes
////////////////////////////////////////////////////////////////////////////////

#include "../inc/can.h"
#include "../inc/mcp2515.h"    

#include <stdio.h>          // for printf()
#include <string.h>         // for memset
#include <util/delay.h>     // for _delay_ms()
#include <stdlib.h>         // for rand()
#include <avr/interrupt.h>  // for interrupts
#include <avr/io.h>         // for setting int1 to input


////////////////////////////////////////////////////////////////////////////////
// Private variables
////////////////////////////////////////////////////////////////////////////////

static can_msg_t received_msg;
static volatile bool new_msg;

////////////////////////////////////////////////////////////////////////////////
// Private function declarations
////////////////////////////////////////////////////////////////////////////////

void _can_receive();

////////////////////////////////////////////////////////////////////////////////
// Public functions
////////////////////////////////////////////////////////////////////////////////

void can_init(unsigned char state) {
    mcp2515_init(state);

    // Set received_msg to zero
    memset(&received_msg, 0, sizeof(received_msg));

    // Turn off filters
    mcp2515_bit_modify(MCP_RXB0CTRL, 0x60, 0x60); 

#if defined (__AVR_ATmega162__)
#define CAN_INTERRUPT_VEC INT1_vect
    // set INT1 pin to input
    DDRD &= ~(1 << PD3);

    // enable interrupt on INT1
    GICR |= (1 << INT1);

    // Set interrupt type to falling edge
    MCUCR |= (1 << ISC11);
#elif defined (__AVR_ATmega2560__)
#define CAN_INTERRUPT_VEC INT2_vect
    DDRD &= ~(1 << PD2);

    EIMSK |= (1 << INT2);

    EICRA |= (1 << ISC21);
#endif
    // Enable global interrupts on atmega162
    sei();
}

bool can_new_msg(void) {
    return new_msg;
}

const can_msg_t *can_get_recv_msg(void) {
    _can_receive();
    return (const can_msg_t *)(&received_msg);
}

void can_send(const can_msg_t* p_msg) {

    uint8_t sidl = p_msg->sid << 5;
    uint8_t sidh = p_msg->sid >> 3;

    mcp2515_write_byte(MCP_TXB0SIDL, sidl);
    mcp2515_write_byte(MCP_TXB0SIDH, sidh);

    mcp2515_write_byte(MCP_TXB0DLC, p_msg->length);

    for (int i = 0; i < p_msg->length; ++i) {
        mcp2515_write_byte(MCP_TXB0D0 + i, p_msg->data[i]);
    }

    mcp2515_request_to_send(MCP_RTS_TX0);
}

////////////////////////////////////////////////////////////////////////////////
// Private functions
////////////////////////////////////////////////////////////////////////////////

void _can_receive(void) {
    
    new_msg = false;
    
    uint8_t sidl = mcp2515_read_byte(MCP_RXB0SIDL);
    uint8_t sidh = mcp2515_read_byte(MCP_RXB0SIDH);

    received_msg.sid = sidh << 3 | sidl >> 5; 
    
    received_msg.length = mcp2515_read_byte(MCP_RXB0DLC) & 0xF;

    mcp2515_read_rx_buffer_data(received_msg.data, received_msg.length);

    // Manually clear the interrupt flag
    // This had to be done in order to have reliable operations, possibly due 
    // to race conditions
    mcp2515_bit_modify(MCP_CANINTF, 0b1, 0);   
}

////////////////////////////////////////////////////////////////////////////////
// Interrupt service routine
////////////////////////////////////////////////////////////////////////////////

ISR(CAN_INTERRUPT_VEC) {
    new_msg = true;
}


////////////////////////////////////////////////////////////////////////////////
// Test functions
////////////////////////////////////////////////////////////////////////////////

// These functions are used for testing
#if COMPILE_CAN_TEST

void can_print_msg(const can_msg_t* msg) {
    printf("ID: 0x%.4X\n", msg->sid);
    printf("Len: %d\n", msg->length);
    for (int i = 0; i < msg->length; ++i) {
        uint8_t d = msg->data[i];
        printf("D%X: 0x%.2X\n", i, d);
    }
}

void can_loopback_test() {

    can_msg_t sendmsg = {
        .sid = 0x321,
        .length = 8,
        .data[0] = 9,
        .data[1] = 8,
        .data[2] = 7,
        .data[3] = 6,
        .data[4] = 5,
        .data[5] = 4,
        .data[6] = 3,
        .data[7] = 2,
    };

    sendmsg.sid = rand() % 256;
    sendmsg.length = rand() % 8;
    
    for (int i = 0; i  < 8; ++i) {
        sendmsg.data[i] = rand() % 256;
    }

    can_send(&sendmsg);
    
    // Wait for message to be sent
    while (!can_new_msg());
    
    const can_msg_t *recvmsg = can_get_recv_msg();
    
    if (sendmsg.sid != recvmsg->sid) {
        printf("CAN loopback test failed\n");
        return;
    }
    if (sendmsg.length != recvmsg->length) {
        printf("CAN loopback test failed\n");
        return;
    }

    for (int i = 0; i < sendmsg.length; ++i) {
        if (sendmsg.data[i] != recvmsg->data[i]) {
            printf("CAN loopback test failed\n");
            return;
        }
    }

    printf("CAN loopback test passed\n");   
}

void can_test_node_transmission(void) {
    can_msg_t sendmsg = {
        .sid = 0,
        .length = 8,
        .data[0] = 3,
        .data[1] = 6,
        .data[2] = 3,
        .data[3] = 4,
        .data[4] = 3,
        .data[5] = 2,
        .data[6] = 1,
        .data[7] = 0
    };

    sendmsg.sid = rand() % 256;
    sendmsg.length = rand() % 8;
    
    for (int i = 0; i  < 8; ++i) {
        sendmsg.data[i] = rand() % 256;
    }

    // unsigned char val = mcp2515_read_byte(MCP_CANSTAT);
    // unsigned char cur_mode = (val & MODE_MASK);
    // printf("Current mode: 0x%.2x\n", cur_mode);

    printf("Send msg:\n");
    can_print_msg(&sendmsg);
    printf("\n\n");
    can_send(&sendmsg);
}

#endif // COMPILE_CAN_TEST