SOURCE_FILES := main.c pong.c

CC := gcc
CFLAGS := -g3 -std=c11

.DEFAULT_GOAL := pong


pong:
	$(CC) $(CFLAGS) $(SOURCE_FILES) -o $@


clean:
	rm -rf pong