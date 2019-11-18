# Node 2 

Node 2 handles the PID controller, interfacing with the motor, servo, buzzer and solenoid
 * `dac` Handles Digital/Analog conversion for use with the motor box
 * `encoder` Handles reading the encoder measuring horizontal position
 * `game_logic` Handles the game logic in Node 2
 * `ir` Reads the Infrared diode for checking if the ball has hit the ground
 * `motor` Handles interfacing with the motor for controlling horizontal position
 * `pid` Implements a PID-controller for the position
 * `servo` Handles controlling the servo motor for turning the solenoid
 * `solenoid` Handles interfacing with the solenoid
 * `TWI_Master` TWI Library implemented by Atmel Coorporation

