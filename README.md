CPP-MIDI
==========

Introduction
----
CPP-MIDI is a very incomplete library for handling MIDI files, and is _not_ released or even alpha yet. Please note that this library aims to be a very simple and light interface to MIDI only, and does so at quite a low level. Soon I will create a library which handles music more generally, also for C++ of course.

Since the core functionality has been implemented, this library will probably soon be ready for release.

Unimplemented:
- SysEx Reading
- Meta event creation from other source than file.

Implemented:
- File reading and writing
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

Firstly, the writing to a file is interesting to look at. When creating the object, one should take a couple of things into consideration.
- Messages are played on a channel, given in the constructor. If this channel has no program, there will be no sound. So create a program change message first!
- The notes can be statically initialized, and reused when adding to a track. They will be copied, so the changing of a note after adding has essentially no effect (unless the changed note is also added of course).
- The EOT needs to be written to the track if you're done with the track. No events should come after this EOT. If there are, the player will simply not play the file because it thinks the file is corrupt.

This code will illustrate how one could write notes to a MIDI file. In this code, a chromatic scale is written, from middle C to E an octave higher.
```C++
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
```

Below is the reading and then rewriting of a file illustrated.
```C++
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
```
