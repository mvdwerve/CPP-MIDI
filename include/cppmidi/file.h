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
            File();

            /**
             * Constructor
             * @param name  Name of the file to be opened
             */
            File(const std::string name);

            /**
             * Destructor
             */
            virtual ~File();


            /**
             * Function to add a Midi::Track to this midi file by reference.
             * @param  t     Track to be added by reference.
             * @return bool  True if track was added, false otherwise (too much tracks).
             */
            bool addTrack(Track* t);

            /**
             * Function to write this Midi::File to the actual internal file object.
             * @todo truncate the file?
             */
            void writeToFile() {
                _file << *this;
                _file.flush();
            }

            /**
             * Friend function to overload the operator to write to streams, used for
             * file writing. This makes it that the midi can be written to virtually
             * everything as long as it is an outputstream.
             * @param output            The output stream
             * @param f                 The file with which the operator was used.
             * @returns std::ostream    Original stream.
             */
            friend std::ostream& operator <<(std::ostream& output, const File& f);
        private:
            /**
             * The internal filestream to be read from and written to.
             * @var std::fstream
             */
            std::fstream _file;

            /**
             * Internally a vector is used to keep reference of all the tracks. Please
             * note that this will append the track by reference
             * @var std::vector<Track*>
             */
            std::vector<Track*> _tracks;

            /**
             * This will keep track of the header data.
             * @var Header
             */
            Header _head;
    };
}

#endif
