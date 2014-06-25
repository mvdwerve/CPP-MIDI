#
# File: Makefile
#
# Takes care of the main compilation of the library. Everything is together at the moment but a nice
# structure will be created soon.
#
# Author: Michael van der Werve
# Date: 22-06-2014
#

# Basic g++ compiler
CPP := g++

# Universal removal of a lot
RM := rm -rf
MKDIR := mkdir -p

# We create a static library since the library is not very big.
CREATELIB := ar rcs

# Currently compiling with debug information and the c++11 standard.
CFLAGS=-ggdb -std=c++11 -Wall -Wextra -pedantic

# Finding all the cpp files, since they might be nested in the src/ directory.
SRCFILES := $(shell find src/ -type f -name '*.cpp')

# Finding all the h files, since they have the same directorystructure as the src/.
HFILES := $(shell find include/ -type f -name '*.h')

# The compiled object files are simply all the cpp files found earlier.
OBJECT_FILES := $(patsubst %.cpp, %.o, $(SRCFILES))

# The include directory must manually be set
INCLUDE_FLAG := -Iinclude/

# Simple variables for the directories used when building.
BUILD_DIR := build
LIB_DIR := lib

LIBRARY_NAME := CPP-MIDI

.PHONY: clean
.PHONY: all
.PHONY: dirs
.PHONY: run

all: test

%.o: %.cpp dirs
	$(CPP) $(INCLUDE_FLAG) $(CFLAGS) $< -c -o $@

lib$(LIBRARY_NAME).a: $(OBJECT_FILES)
	$(CREATELIB) $(LIB_DIR)/$@ $^

test: test.cpp lib$(LIBRARY_NAME).a
	$(CPP) $< -L$(LIB_DIR) -l$(LIBRARY_NAME) $(INCLUDE_FLAG) $(CFLAGS) -o $(BUILD_DIR)/$@

run: test
	$(BUILD_DIR)/test && hexdump -C test.mid

clean:
	$(RM) $(LIB_DIR) $(OBJECT_FILES) $(BUILD_DIR) test.mid

dirs:
	$(MKDIR) $(BUILD_DIR) $(LIB_DIR)
