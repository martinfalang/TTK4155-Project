#include "can.h"
#include "defines.h"

#include <stdio.h>          // for printf()
#include <string.h>         // for memset
#include <util/delay.h>     // for _delay_ms()
#include <stdlib.h>         // for rand()
#include <avr/interrupt.h>  // for interrupts
#include <avr/io.h>         // for setting int1 to input

static can_msg_t received_msg;
static volatile bool new_msg;

void can_test() {

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

    printf("\n\nSend: \n");
    can_print_msg(&sendmsg);

    can_send(&sendmsg);

    uint8_t canif = mcp2515_read_byte(MCP_CANINTF);
    printf("CanIF: %x\n", canif & 0x01);

    // while (!new_msg);
    while (!(mcp2515_read_byte(MCP_CANINTF) & 0x01));

    can_receive();
    const can_msg_t *recvmsg = can_get_recv_msg();

    printf("\nRec: \n");
    can_print_msg(recvmsg);
    
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

    printf("CAN test lookup passed\n");   
}

bool can_new_msg(void) {
    return new_msg;
}

const can_msg_t *can_get_recv_msg(void) {
    return (const can_msg_t *)(&received_msg);
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
    unsigned char val = mcp2515_read_byte(MCP_CANSTAT);
    unsigned char cur_mode = (val & MODE_MASK);

    printf("Current mode: 0x%.2x\n", cur_mode);

    printf("Send msg:\n");
    can_print_msg(&sendmsg);
    printf("\n\n");
    can_send(&sendmsg);
}


void can_init(unsigned char state) {
    mcp2515_init(state);

    // Set received_msg to zero
    memset(&received_msg, 0, sizeof(received_msg));

    // Turn off filters
    mcp2515_bit_modify(MCP_RXB0CTRL, 0x60, 0x60); 

    // // set INT1 pin to input
    // DDRD &= ~(1 << PD3);

    // // enable interrupt on INT1
    // GICR |= (1 << INT1);

    // // Set interrupt type to falling edge
    // MCUCR |= (1 << ISC11);

    // // Enable global interrupts on atmega162
    // sei();
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


void can_receive(void) {
    
    uint8_t sidl = mcp2515_read_byte(MCP_RXB0SIDL);
    uint8_t sidh = mcp2515_read_byte(MCP_RXB0SIDH);

    received_msg.sid = sidh << 3 | sidl >> 5; 
    
    received_msg.length = mcp2515_read_byte(MCP_RXB0DLC) & 0xF;

    mcp2515_read_rx_buffer_data(received_msg.data, received_msg.length);

    new_msg = false;
    
    // for (int i = 0; i < received_msg.length; ++i) {
    //     received_msg.data[i] = mcp2515_read_byte(MCP_RXB0D0 + i);
    // }

    // Reset interrupt flag
    // mcp2515_bit_modify(MCP_CANINTF, MCP_RX0IF, 0);
    // uint8_t canif = mcp2515_read_byte(MCP_CANINTF);
    // printf("CanIF: %x\n", canif & 0x01);
}


void can_print_msg(const can_msg_t* msg) {
    // printf("MSG START\n");
    printf("ID: 0x%.4X\n", msg->sid);
    printf("Len: %d\n", msg->length);
    for (int i = 0; i < msg->length; ++i) {
        uint8_t d = msg->data[i];
        printf("Data%X: 0x%.2X\n", i, d);
    }
    // printf("MSG END\n");
}


// // ISR for received can message
// ISR(INT1_vect) {
//     cli();
//     new_msg = true;
//     printf("INTERRUPT\n");
//     // Clear int1 flag
//     // maybe
//     sei();
// }