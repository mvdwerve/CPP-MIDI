CPP-MIDI
==========

Introduction
----
CPP-MIDI is a very incomplete library for handling MIDI files, and is _not_ released or even alpha yet.

Unimplemented:
- File reading
- Variable length values

Implemented:
- Header info, track info and data writing to a file.
- Files recognized by music players
- Events
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
    /* This is here because we have to clean up. */
    std::vector<Event*> events;

    /* Loading the basic midi object with a filename of test.mid */
    File midi("test.mid");
    Track *t = new Track();

    Message *note, *off;
    uint8_t baseNote = 48;

    /* Creating 16 messages to put in the midi. */
    for (int i = 0; i < 16; i++) {
        /* Creating the on and the off message */
        note = new Message(MessageType::NOTE_ON, 0, baseNote, 100);
        off = new Message(MessageType::NOTE_OFF, 0, baseNote, 0);

        /* The off event will fire 64 ticks after the note event. */
        note->deltaTime = 0;
        off->deltaTime = 64;

        /* Add the events to the track. */
        t->addEvent(note);
        t->addEvent(off);

        /* Notes can be reused, but note that since these are pointers, any change to the
         * note will change all reuses of the same note.
         */
        t->addEvent(note);
        t->addEvent(off);

        /* Adding the notes to a vector so we can clean everything up later. */
        events.push_back(note);
        events.push_back(off);

        /* Incrementing the base note. */
        baseNote++;
    }

    midi.addTrack(t);
    midi.writeToFile();

    /* Cleaning up all the notes, since we should not expect the library to do that. */
    for (auto event : events)
        delete event;
}
```
