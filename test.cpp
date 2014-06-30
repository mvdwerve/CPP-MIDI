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
 * This program will first write a simple test.mid with a chromatic scale. After this, the
 * file is put back in the object from the file and rewritten to testrw.mid. testrw should be
 * equal to test.mid.
 *
 * @author Michael van der Werve
 */

#include <cppmidi/file.h>
#include <cppmidi/events/message.h>
#include <cppmidi/events/meta.h>
#include <cppmidi/event.h>
#include <cppmidi/track.h>
#include <vector>
#include <fstream>

using Midi::File;
using Midi::Track;
using Midi::Event;
using Midi::Events::Message;
using Midi::Events::MessageType;
using Midi::Events::MetaType;
using Midi::Events::Meta;

void writeTest() {
    /* Loading the basic midi object with a filename of test.mid */
    File midi;
    Track *t = midi.getTrack();

    uint8_t baseNote = 48;

    /* Creating the program change event, note event, off event and the EOT event. */
    Message program(MessageType::PROGRAM_CHANGE, 0, 1, 0);
    Message note(MessageType::NOTE_ON, 0, baseNote, 100);
    Message off(MessageType::NOTE_OFF, 0, baseNote, 0);
    Meta EOT(MetaType::EOT);

    /* The off event will fire 0x80 ticks after the note event. */
    program.deltaTime = 0;
    note.deltaTime = 0;
    off.deltaTime = 0x80;

    /* This is needed, because otherwise there will be no voice on the channel. */
    t->addEvent(program);

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

    /* The EOT event always needs to be written to the end of the track. If this is forgotten,
     * the resulting MIDI will not be playable.
     */
    t->addEvent(EOT);

    /* Opening a file to store the midi in. */
    std::ofstream file("test.mid", std::ios::trunc | std::ios::binary);

    /* Writing everything to the file, flushing the file and closing it. */
    file << midi;
    file.flush();
    file.close();
}

void readTest() {
    /* Creating an empty Midi::File object. */
    File midi;

    /* This is the old file which will be loaded from the folder. */
    std::ifstream oldFile("test.mid", std::ios::binary);

    /* This might throw, if the MIDI is invalid. In that case, the midi will be in an invalid state and unfinished. */
    try {
        oldFile >> midi;
    } catch (std::ios_base::failure &f) {
        std::cout << "Something went wrong... " << f.what() << std::endl;
    }

    /* We do not need the old file any more, everything is in memory. */
    oldFile.close();

    /* Opening a new file to write to. */
    std::ofstream newFile("testrw.mid", std::ios::trunc | std::ios::binary);

    /* Writing the midi object to a file. */
    newFile << midi;
    newFile.flush();
    newFile.close();
}

int main(__attribute__ ((unused)) int argc, __attribute__ ((unused)) char* argv[]) {
    /* First we will perform the writing test, which will create a simple MIDI. */
    writeTest();

    /* Then we will perform a reading test, which will open the created midi and rewrite it to a new file. */
    readTest();
}
