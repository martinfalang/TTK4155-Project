# Node 1

Node 1 is responsable for handling user input through the USB multi-function 
board. This input is sent over CAN bus to Node 2. For details about Node 2, see
[Node 2 README](../Node2/README.md).


## Node specific libraries

* `adc`: Reads an analog voltage with an 8-bit ADC
    * `touch`: Handles touch buttons and sliders
    * `joystick`: Handles joystick axis and button

* `buzzer`: Plays notes and songs
    * `delay`: Variable millisecond delay function used for playing song
    * `pwm0`: Underlying PWM for tone generation
    * `notes.h`: Note frequencies for playable notes
    * `songs/`: Possible songs to play on the buzzer

* `oled`: Draws a buffer to the OLED screen on the USB multi-function board
    * `oled-buffer`: Functions for drawing to a buffer array
    * `oled-menu`: Framework for the menu 
    * `fonts.h`: Three different font sizes to use on the OLED
    * `pictures/`: Possible pictures to print on the OLED screen

* `game`: All game logic for Node 1
* `highscore`: Functions for handling highscore from Node 2
* `xmem`: Enables and defines external memory map
