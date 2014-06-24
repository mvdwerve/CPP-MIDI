#
# File: Makefile
#
# Takes care of the main compilation of the library. Everything is together at the moment but a nice
# structure will be created soon.
#
# Author: Michael van der Werve
# Date: 22-06-2014
#

CPP=g++
CFLAGS=-ggdb -std=c++11 -Wall -Wextra -pedantic
MIDI := $(patsubst %.cpp,%.o,$(wildcard Midi*.cpp))

.PHONY: clean

all: libCPP-MIDI.a

%.o: %.cpp
	$(CPP) $(CFLAGS) $< -c -o $@

libCPP-MIDI.a: $(MIDI)
	ar rcs $@ $^

test: test.cpp libCPP-MIDI.a
	$(CPP) $< -L. -lCPP-MIDI $(CFLAGS) -o $@

clean:
	rm -rf *.o *.a

