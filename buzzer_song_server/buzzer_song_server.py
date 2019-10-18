import serial

import notes

# GLOBAL CONSTANTS
BAUDRATE = 9600
PORT = r"COM8"

print(notes.C4)
exit()


ser = serial.Serial()
ser.baudrate = BAUDRATE
ser.port = PORT
