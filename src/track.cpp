/**
 * track.cpp
 *
 * File with implementations for the Midi::Track class.
 *
 * @author Michael van der Werve
 */

#include <cppmidi/track.h>
#include <cppmidi/endian.h>
#include <cppmidi/events/meta.h>
#include <cppmidi/events/message.h>

using Midi::Events::Meta;
using Midi::Events::MetaType;
using Midi::Events::Message;
using Midi::Events::MessageType;

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
        /* This will be the EOT event. */
        Meta EOT(MetaType::EOT);

        /* This is a program change message for channel 0 (maybe set all channels?) */
        Message initialProgram(MessageType::PROGRAM_CHANGE, 0, 1, 0);

        /* Writing the track identifier plus the length to the stream. */
        output.write(Track::IDENTIFIER, 4);
        Endian::writeIntBig(output, t._length /*+ EOT.getLength()*/ + initialProgram.getLength() + 4);

        /* Writing the initial program to channel 0, so there will be sound. */
        output << initialProgram;

        /* Writing every event to the output stream */
        for (auto event : t._events)
            output << *event;

        /* XXX:2014-05-27:mvdwerve: This is the EOT until the VLV is fixed.*/
        Endian::writeByte(output, 0x00);
        Endian::writeByte(output, 0xFF);
        Endian::writeByte(output, 0x2F);
        Endian::writeByte(output, 0x00);

        return output;
    }
}
