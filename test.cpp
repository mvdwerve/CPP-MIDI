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

    /* Please note, doing this before the file is written WILL cause segmentation faults. */
    delete t;
}
