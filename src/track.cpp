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
#include <cppmidi/events/sysex.h>
#include <cstring>

using Midi::Events::Meta;
using Midi::Events::MetaType;
using Midi::Events::Message;
using Midi::Events::MessageType;
using Midi::Events::SysEx;

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
        /* Writing the track identifier plus the length to the stream. */
        output.write(Track::IDENTIFIER, 4);
        Endian::writeIntBig(output, t._length);

        /* Writing every event to the output stream */
        for (auto event : t._events)
            output << *event;

        return output;
    }

    /**
     * Method to read the Track object from an input stream. The stream should
     * be in binary mode.
     * @param input The input stream.
     * @param track The track object.
     * @return std::istream& THe original input stream.
     */
    std::istream& operator >>(std::istream& input, Track& track) {
        /* Reading the first 4 magic bytes from the stream, which should be the MTrk. */
        char *magic = new char[4];
        input.read(magic, 4);

        /* If the magic number MTrk does not match, throw an exception. */
        if (strncmp(magic, Track::IDENTIFIER, 4))
            throw std::ios_base::failure("Bad track magic");

        /* Store the length, because although we will not use it in the object, we will use it. */
        uint32_t length = Endian::readIntBig(input);

        Event* event = NULL;

        while (length) {
            /* There can really only be 3 cases, so an if-statement is a good choice here, although
             * this does certainly not feel like good form. After this if statement, event is guaranteed
             * to have a message in it. Since most of the cases will be the message, everything should be fine.
             * XXX:2014-06-30:mvdwerve: REVISE / IMPROVE THIS, this works but looks horrendous.
             */
            if (!(event = Message::popEvent(input))
                        && !(event = Meta::popEvent(input))
                        && !(event = SysEx::popEvent(input)))
                throw std::ios_base::failure("Cannot create event, unknown status byte.");

            /* Subtracting the read bytes from the length. */
            length -= event->gcount();

            /* Adding the event to the track and making sure the local pointer cannot be accessed again. */
            track.addEvent(event);
            event = NULL;
        }

        /* Was dynamically allocated, so is freed now. */
        delete magic;

        return input;
    }
}
