import serial

import notes
from songs import starwars
from songs import nyancat

SONGS = {
    "starwars":starwars, 
    "nyancat":nyancat
}
SONG_REQ_STR = "song"
SONG_NAME_MAX_LENGTH = 20
SONG_EXISTS_ACK = "ok"
SONG_DOESNT_EXISTS_ACK = "no"
SONG_NEXT_NOTE_REQ = "n"
SONG_NEXT_NOTE_FORMAT = "{note},{note_type}"


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
song = song.decode().strip()

melody = [0]
note_types = [0]
if song in SONGS.keys():
    melody = SONGS[song].melody
    note_types = SONGS[song].note_types
    ser.write(SONG_EXISTS_ACK + "\n")
else:
    ser.write(SONG_DOESNT_EXISTS_ACK + "\n")



for note, ntype in zip(melody, note_types):
    while ser.read(len(SONG_NEXT_NOTE_REQ)).decode() != SONG_NEXT_NOTE_REQ:
        # wait until client requests next note
        pass

    nxt = SONG_NEXT_NOTE_FORMAT.format(note=note, note_type=ntype)
    ser.write(nxt + "\n")

# send end of song
nxt = SONG_NEXT_NOTE_FORMAT.format(note=0, note_type=0)
ser.write(nxt + "\n")

