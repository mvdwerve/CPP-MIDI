/**
 * File: MidiFile.cpp
 *
 * This object will only very generally handle MIDI files.
 *
 * Author: Michael van der Werve
 * Date: 22-06-2014
 */

#ifndef MIDI_FILE_h
#define MIDI_FILE_h

#include <vector>
#include <string>
#include <fstream>

#include <cppmidi/track.h>
#include <cppmidi/header.h>

namespace Midi {
    class File {
        public:
            const static bool modeBigEndian;

            File() {}
            File(const std::string name);

            virtual ~File();

            bool addTrack(const Track t) {
                if (!_head.setNumTracks(_head.getNumTracks() + 1))
                    return false;

                _tracks.push_back(t);
                return true;
            }

            void writeToFile() {
                _file << *this;
            }

            /**
             * Helper functions to write shorts and ints with a specified endianness.
             */
            static void writeShortBig(std::ostream &stream, uint16_t s);
            static void writeShortLittle(std::ostream &stream, uint16_t s);
            static void writeIntBig(std::ostream &stream, uint32_t s);
            static void writeIntLittle(std::ostream &stream, uint32_t s);
            static void writeByte(std::ostream &stream, uint8_t c);

            friend std::ostream& operator <<(std::ostream& output, const File& f);
        private:
            std::fstream _file;
            std::vector<Track> _tracks;
            Header _head;
    };
}

#endif
