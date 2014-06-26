/**
 * file.cpp
 *
 * File with implementations for the Midi::Event::Message class.
 *
 * @author Michael van der Werve
 */

#include <cppmidi/endianwriter.h>
#include <cppmidi/events/message.h>

/**
 * Setting up the midi and event namespace.
 */
namespace Midi {
    namespace Events {
        /**
         * Constructor
         * @todo Variable length, since 4 is for the stubs and 64 also.
         */
        Message::Message() : Event() {
            _length = 4;
            _timeDiff = 64;
        }

         /**
         * Function which prints this event.
         * @param output The output stream to print to.
         * @return std::ostream& The original output stream.
         */
        std::ostream& Message::print(std::ostream& output) const {
            /* Stubs to perform middle C on on channel 0 with velocity of 0x40. */
            uint16_t status_stub = 0x90;
            uint16_t note_stub = 0x3C;
            uint16_t velocity_stub = 0x40;

            EndianWriter::writeByte(output, status_stub);
            EndianWriter::writeByte(output, note_stub);
            EndianWriter::writeByte(output, velocity_stub);

            return output;
        }
    }
}
