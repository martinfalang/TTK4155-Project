# Makefile for tests that can be run on a computer, i.e. without the microcontroller

# Define the paths in order of where make should look for them
# This means that source files can be both in the tests folder and the src folder
# See https://www.gnu.org/software/make/manual/html_node/General-Search.html#General-Search
# for more info
VPATH := . ../src

# List all source files to be compiled; separate with space
SOURCE_FILES := oled.c test_main.c oled_buffer_test.c oled_buffer_utils.c

BUILD_DIR := build

CC := gcc
CFLAGS := -O -std=c11 -D COMPILE_FOR_TESTS

OBJECT_FILES = $(SOURCE_FILES:%.c=$(BUILD_DIR)/%.o)
# TEST_SRC := $(TEST_SOURCE_FILES:%.c=$(TEST_SRC_DIR)/%.c)

.DEFAULT_GOAL := test_main

test_main : $(OBJECT_FILES)
	$(CC) $(CFLAGS) $(OBJECT_FILES) -o $@

$(BUILD_DIR):
	mkdir $(BUILD_DIR)

$(BUILD_DIR)/%.o : %.c | $(BUILD_DIR)
	$(CC) $(CFLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -rf $(BUILD_DIR)