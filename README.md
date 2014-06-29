CPP-MIDI
==========

Introduction
----
CPP-MIDI is a very incomplete library for handling MIDI files, and is _not_ released or even alpha yet. Please note that this library aims to be a very simple and light interface to MIDI only, and does so at quite a low level. Soon I will create a library which handles music more generally, also for C++ of course.

Unimplemented:
- File reading

Implemented:
- Header info, track info and data writing to a file.
- Files recognized by music players
- Events
    - Variable Length Values
    - Message Event
        - Note off
        - Note on
        - Pressure change
        - Controller change
        - Program change
        - Channel pressure
        - Pitch Bend
    - SysEx Event
        - Unfortunately, there is not really a standard for SysEx events, so the data is made accessible. Should therefore work correctly.
    - Meta Event
        - Implemented with stubs, and data is not accesible yet.

Build
----
Building is very simple. The Makefile will create a static library in the lib/ directory.

Inspect
----
The best way to inspect the generated midi files is by using the linux hexdump utility.
Command:
```
hexdump -C test.mid
```
This will display nicely formatted hex. Another option is to run
```
make run
```
This will build everything and execute the command with the generated test file.

Example
----
The best example is the test file, which is displayed below. _Please note that the code below might be outdated, since this readme is not updated nearly as much as file itself ofcourse._
```C++
#include <cppmidi/file.h>
#include <cppmidi/events/message.h>
#include <cppmidi/event.h>
#include <cppmidi/track.h>
#include <vector>

using Midi::File;
using Midi::Track;
using Midi::Event;
using Midi::Events::Message;
using Midi::Events::MessageType;

int main(__attribute__ ((unused)) int argc, __attribute__ ((unused)) char* argv[]) {
    /* Loading the basic midi object with a filename of test.mid */
    File midi("test.mid");
    Track *t = midi.getTrack();

    uint8_t baseNote = 48;

    Message note(MessageType::NOTE_ON, 0, baseNote, 100);
    Message off(MessageType::NOTE_OFF, 0, baseNote, 0);

    /* The off event will fire 64 ticks after the note event. */
    note.deltaTime = 0;
    off.deltaTime = 0x80;

    /* Creating 16 messages to put in the midi. */
    for (int i = 0; i < 16; i++) {
        note.setData1(baseNote);
        off.setData1(baseNote);

        /* Add the events to the track. */
        t->addEvent(note);
        t->addEvent(off);

        /* Incrementing the base note. */
        baseNote++;
    }

    midi.writeToFile();
}
```
