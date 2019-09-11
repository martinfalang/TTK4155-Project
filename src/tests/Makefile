# Makefile for tests that can be run on a computer, i.e. without the microcontroller
# List all source files to be compiled; separate with space
SOURCE_FILES := test_main.c oled_buffer_test.c oled_buffer_utils.c ../oled.c

BUILD_DIR := build
SRC_DIR := .

CC := gcc
CFLAGS := -O -std=c11

OBJECT_FILES = $(SOURCE_FILES:%.c=$(BUILD_DIR)/%.o)
SRC := $(SOURCE_FILES:%.c=$(SRC_DIR)/%.c)

.DEFAULT_GOAL := test_main

test_main : $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(OBJECT_FILES) -o $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BUILD_DIR)/%.o : $(SRC_DIR)/%.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@


.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)