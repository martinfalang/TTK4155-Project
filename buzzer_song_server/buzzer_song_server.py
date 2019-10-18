import serial

import notes
from songs import starwars


# initialize serial object
ser = serial.Serial()
ser.baudrate = 9600
ser.port = r"COM8"
ser.bytesize = serial.EIGHTBITS
ser.parity = serial.PARITY_NONE
ser.stopbits = serial.STOPBITS_TWO

try:
    ser.open()
except Exception as e:
    print(e)
    raise Exception(e)

print("done")