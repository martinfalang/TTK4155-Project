# Must be run with sudo
# Opens byggern serial port with baudrate 9600, 2 stopbits
# and corrent line endings.
# 
# All flags with description can be found here: https://github.com/npat-efault/picocom/blob/master/picocom.1.md

picocom -b 9600 -p 2 --imap lfcrlf /dev/ttyS0
