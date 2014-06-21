/**
 * File: MidiFile.cpp
 *
 * This object will only very generally handle MIDI files.
 *
 * Author: Michael van der Werve
 * Date: 22-06-2014
 */

#ifndef MIDIFILE_h
#define MIDIFILE_h

#include "MidiHeader.h"
#include "MidiTrack.h"

namespace Midi {
public class MidiFile {
public:
    MidiFile() {}
private:
    MidiHeader _head;
    Vector<MidiTrack> _tracks;
}
}

#endif
