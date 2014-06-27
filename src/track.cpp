/**
 * track.cpp
 *
 * File with implementations for the Midi::Track class.
 *
 * @author Michael van der Werve
 */

#include <cppmidi/track.h>
#include <cppmidi/endianwriter.h>

/**
 * Setting up the basic midi namespace.
 */
namespace Midi {
    /**
     * Identifier for midi tracks, which is basically "MTrk".
     * @var const static char*
     */
    const char* Track::IDENTIFIER = "MTrk";

    /**
     * Stream operator so the track info can be written to any output.
     * @param output Output stream
     * @param t      Track to be written to the output
     * @return std::ostream& Original output stream.
     */
    std::ostream& operator <<(std::ostream& output, const Track& t) {
        output.write(Track::IDENTIFIER, 4);
        EndianWriter::writeIntBig(output, t._length + 4 + 3);

        /* XXX:2014-05-26:mvdwerve: This is simply a program change, now manually added. */
        EndianWriter::writeByte(output, 0x00);
        EndianWriter::writeByte(output, 0xC0);
        EndianWriter::writeByte(output, 0x01);

        for (auto event : t._events)
            output << *event;

        /* XXX:2014-05-26:mvdwerve: Make this code better and with a define, because
         * this is a set-in-stone sequence. This will be part of a metaevent eot.
         */
        EndianWriter::writeByte(output, 0x00);
        EndianWriter::writeByte(output, 0xFF);
        EndianWriter::writeByte(output, 0x2F);
        EndianWriter::writeByte(output, 0x00);

        return output;
    }
}
