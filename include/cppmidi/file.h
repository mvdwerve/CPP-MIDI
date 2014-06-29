/**
 * file.h
 *
 * This object will only very generally handle MIDI files.
 *
 * @author Michael van der Werve
 */

#ifndef MIDI_FILE_h
#define MIDI_FILE_h

#include <vector>
#include <string>
#include <iostream>
#include <fstream>

#include <cppmidi/track.h>
#include <cppmidi/header.h>

/**
 * Setting up the Midi namespace.
 */
namespace Midi {
    class File {
        public:
            /**
             * Default constructor
             */
            File() : _tracks() { }

            /**
             * Destructor
             */
            virtual ~File() {
                /* Tracks are dynamically allocated by us, and should thus be freed. */
                for (auto track : _tracks)
                    delete track;
            }

            /**
             * Method to get an arbitrary track from the file. Might return NULL.
             * @return Track* Pointer to a Track from the file. NULL if there was no new track.
             */
            Track* getTrack();

            /**
             * Method to get an arbitrary track from the file. Might return NULL, if index is too large.
             * @return Track* Pointer to a Track from the file. NULL if there was no new track.
             */
            Track* getTrack(int index);

            /**
             * Friend function to overload the operator to write to streams, used for
             * file writing. This makes it that the midi can be written to virtually
             * everything as long as it is an outputstream.
             * @param output            The output stream
             * @param f                 The file with which the operator was used.
             * @returns std::ostream    Original stream.
             */
            friend std::ostream& operator <<(std::ostream& output, const File& f);

            /**
             * Method to input the file into the midi object. The stream should be in binary mode.
             * @param input The input stream.
             * @param f The midi file object.
             * @return std::istream& THe original input stream.
             */
            friend std::istream& operator >>(std::istream& input, File& f);

        private:
            /**
             * Since there is always a maximum of 16 tracks, create a primitive array.
             * @var *Track[]
             */
            Track *_tracks[16];

            /**
             * This will keep track of the header data.
             * @var Header
             */
            Header _head;
    };
}

#endif
