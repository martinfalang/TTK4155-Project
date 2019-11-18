/**
 * @file uart.h
 * @author Kristian Brudeli
 *         Martin Falang
 *         Eirik Flemsæter Falck
 * @brief Implements functions for UART communication
 * @version 0.1
 * @date 2019-11-18
 * 
 * @copyright Copyright (c) 2019
 * 
 */

#ifndef UART_H
#define UART_H

#include <stdio.h>

/**
 * @brief Initialize the UART communication and sets up the possibility to use
 *        @c printf to send formatted text over UART.
 * 
 */
void uart_init(); // ubrr = uart baud rate register

/**
 * @brief Transmits a byte ove UART 
 * 
 * @param data Data byte to transmit 
 * @param f (This argument is only to not get compiler warning)
 * @return int Retuns the data byte sent
 */
int uart_transmit(char data, FILE *f);

/**
 * @brief Receive a byte over UART
 * 
 * @param f (This argument is only to not get compiler warning)
 * @return int Retuns the data byte received
 */
int uart_recieve(FILE *f);

extern FILE *uart;

#endif /* UART_H */
