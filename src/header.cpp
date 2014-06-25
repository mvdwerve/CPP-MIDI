/**
 * header.cpp
 *
 * File with implementations for the Midi::Header class.
 *
 * @author Michael van der Werve
 */

#include <fstream>
#include <iostream>
#include <string>
#include <arpa/inet.h>
#include <cppmidi/header.h>
#include <cppmidi/file.h>

/**
 * Setting up the midi namespace.
 */
namespace Midi {
    const char* Header::IDENTIFIER = "MThd";

    /**
     * Default constructor
     * @todo calculate delta ticks.
     */
    Header::Header() : _fileFormat(MidiMode::MULTITRACK_SYNC), _deltaTicks(64) {

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
         * the header info to the stream using the helper fucntions provided by the
         * Midi::File class.
         */
        File::writeIntBig(output, 6);
        File::writeShortBig(output, head._fileFormat);
        File::writeShortBig(output, head._numTracks);
        File::writeShortBig(output, head._deltaTicks);

        return output;
    }
}
