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
#include <fstream>
#include "MidiHeader.h"
#include "MidiTrack.h"

namespace Midi {
    class File {
        public:
            File() {}
            File(const std::string name);

            virtual ~File();

            bool addTrack(const Track t) {
                if (!_head.setNumTracks(_head.getNumTracks() + 1))
                    return false;

                _tracks.push_back(t);
                return true;
            }

            void write() {
                _file << *this;
            }

            friend std::ostream& operator <<(std::ostream& output, const File& f);
        private:
            std::fstream _file;
            Header _head;
            std::vector<Track> _tracks;
    };
}

#endif
