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
             * This boolean will tell if the computer is using little endian or big
             * endian. This is important for writing to files, since many primitive
             * datatypes have to be swapped.
             * @var const static bool
             */
            const static bool modeBigEndian;

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
            bool addTrack(const Track& t);

            /**
             * Function to write this Midi::File to the actual internal file object.
             * @todo truncate the file?
             */
            void writeToFile() {
                _file << *this;
            }

            /**
             * Helper function for writing a cross platform big endian short.
             * @param s       The short which should be written in the endian.
             * @param stream  The stream to be written to.
             */
            static void writeShortBig(std::ostream &stream, uint16_t s);

            /**
             * Helper function for writing a cross platform little endian short.
             * @param s       The short which should be written in the endian.
             * @param stream  The stream to be written to.
             */
            static void writeShortLittle(std::ostream &stream, uint16_t s);

            /**
             * Helper function for writing a cross platform big endian int.
             * @param i       The int which should be written in the endian.
             * @param stream  The stream to be written to.
             */
            static void writeIntBig(std::ostream &stream, uint32_t i);

            /**
             * Helper function for writing a cross platform little endian int.
             * @param i       The short which should be written in the endian.
             * @param stream  The stream to be written to.
             */
            static void writeIntLittle(std::ostream &stream, uint32_t i);

            /**
             * Helper function for writing a cross platform byte.
             * @param c         The char (uint8_t) to be written.
             * @param stream    The stream to be written to.
             */
            static void writeByte(std::ostream &stream, uint8_t c);

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
             * @var std::vector<Track>
             */
            std::vector<Track> _tracks;

            /**
             * This will keep track of the header data.
             * @var Header
             */
            Header _head;
    };
}

#endif
