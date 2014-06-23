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

#include <vector>
#include <string>
#include "MidiHeader.h"
#include "MidiTrack.h"

namespace Midi {
class File {
public:
    File() {}
    File(std::string name);

private:
    std::string _name;
    Header _head;
    std::vector<Track> _tracks;
};
}

#endif
