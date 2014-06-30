/**
 * header.cpp
 *
 * File with implementations for the Midi::Header class.
 *
 * @author Michael van der Werve
 */

#include <string>
#include <cstring>
#include <arpa/inet.h>
#include <cppmidi/header.h>
#include <cppmidi/endian.h>

/**
 * Setting up the midi namespace.
 */
namespace Midi {
    const char* Header::IDENTIFIER = "MThd";

    /**
     * Default constructor
     * @todo calculate delta ticks.
     */
    Header::Header() : _fileFormat(MidiMode::MULTITRACK_SYNC), _numTracks(0), _deltaTicks(64) {

    }

    /**
     * Method so the stream operator can be used and the header can be written
     * to any stream.
     * @param output The first stream
     * @param head   This header object
     * @return std::ostream& The original stream
     */
    std::ostream& operator <<(std::ostream& output, const Header &head) {
        /* Writes the identifier to the stream. */
        output.write(Header::IDENTIFIER, 4);

        /* Slightly verbose code but unfortunately there is no other way. Writing
         * the header info to the stream using the helper functions provided by the
         * Midi::File class.
         */
        Endian::writeIntBig(output, 6);
        Endian::writeShortBig(output, head._fileFormat);
        Endian::writeShortBig(output, head._numTracks);
        Endian::writeShortBig(output, head._deltaTicks);

        return output;
    }

    /**
     * Method to read the header object from an input stream. The stream should
     * be in binary mode.
     * @param input The input stream.
     * @param head The header object.
     * @return std::istream& THe original input stream.
     */
    std::istream& operator >>(std::istream& input, Header& head) {
        char *magic = new char[4];
        input.read(magic, 4);

        /* If the magic number MThd does not match, throw an exception. */
        if (strncmp(magic, Header::IDENTIFIER, 4))
            throw std::ios_base::failure("Bad header magic number");

        /* We don't store this since this is constant. */
        Endian::readIntBig(input);

        /* Store all the header info in the header object for processing of the tracks. */
        head._fileFormat = Endian::readShortBig(input);
        head._numTracks = Endian::readShortBig(input);
        head._deltaTicks = Endian::readShortBig(input);

        return input;
    }
}
