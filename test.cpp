/*
 * test.cpp
 *
 * This file will illustrate and test the usage of the midi library. When "make run" is
 * executed in the shell, this file will be called and the hexdump from the resulting midi
 * will be displayed. Then the midi file can be played by any media player supporting
 * midi.
 *
 * Since this library is a very low level library, the code used might get quite verbose.
 * For example, to add a note you will need to first add a note_on event to the track and
 * afterwards a note_off.
 *
 * @author Michael van der Werve
 */

#include <cppmidi/file.h>
#include <cppmidi/events/message.h>
#include <cppmidi/event.h>
#include <cppmidi/track.h>
#include <vector>
#include <fstream>

using Midi::File;
using Midi::Track;
using Midi::Event;
using Midi::Events::Message;
using Midi::Events::MessageType;

void writeTest() {
    /* Loading the basic midi object with a filename of test.mid */
    File midi;
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

    std::ofstream file("test.mid", std::ios::trunc | std::ios::binary);

    file << midi;
    file.flush();
    file.close();
}

void readTest() {
    File midi;

    std::ifstream oldFile("old.mid", std::ios::binary);

    oldFile >> midi;
    oldFile.close();

    std::ofstream newFile("new.mid", std::ios::trunc | std::ios::binary);

    newFile << midi;
    newFile.flush();
    newFile.close();
}

int main(__attribute__ ((unused)) int argc, __attribute__ ((unused)) char* argv[]) {
    readTest();
    writeTest();
}
