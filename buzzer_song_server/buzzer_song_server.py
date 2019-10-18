import serial

import notes
from songs import starwars
from songs import nyancat

SONGS = ("starwars", "nyancat")
SONG_REQ_STR = "song"
SONG_NAME_MAX_LENGTH = 20

# initialize serial object
ser = serial.Serial()
ser.baudrate = 9600
ser.port = r"COM8"
ser.bytesize = serial.EIGHTBITS
ser.parity = serial.PARITY_NONE
ser.stopbits = serial.STOPBITS_TWO

try:
    ser.open()
except serial.SerialException as se:
    print(f"Couldn't connect to device at {ser.port}. Exiting...")
    print(se)
    exit()
    
b = b""
while b.decode() != SONG_REQ_STR:
    b = ser.read(len(SONG_REQ_STR))

song = ser.read_until(size=SONG_NAME_MAX_LENGTH)

print(song.decode().strip())