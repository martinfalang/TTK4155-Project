# BUZZER SONG PROTOCOL

The computer runs the buzzer song server that feeds the microcontroller
with a new note after the previous one was finished playing. All communication
goes through the serial port. All lines are terminated by newline (`\n`). 

---
## Terminology

Server = computer

Client = microcontroller (Arduino)

---
## Requesting song

The client sends a song request to the server by sending the string `song` 
followed by the song name as a string to the server. A list of possible songs 
are found in the songs directory. The song name sent from the client must 
correspond with the filename (excluding the .py) found in the song directory. 
The server responds with sending an `ok\n` if the song exists, `no\n` otherwise.

### Song request format

    song <song name>\n

### Response

    ok\n    -   if song exists
    no\n    -   if song doesn't exist

---
## Playing the song

The server will feed the client with one note and corresponding duration in 
*ms*. 

### Requesting the next note

The client requests the next note by sending a `n\n` to the server. 


### Note and duration format

The format of note and duration is the following: 

    note,duration\n

Both `note` and `duration` will be integers. Note range is [0, 5000] and the 
duration range is [0, 10 000]. That means the maximum duration is 10 seconds. 

---
## End of song

The end of the song is reached when the next note and duration is `0,0\n`. 
