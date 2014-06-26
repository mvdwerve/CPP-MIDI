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
            _velocity = 0x64;
            _status = 0x90;
        }

         /**
         * Function which prints this event.
         * @param output The output stream to print to.
         * @return std::ostream& The original output stream.
         */
        std::ostream& Message::print(std::ostream& output) const {
            EndianWriter::writeByte(output, _status);
            EndianWriter::writeByte(output, _note);
            EndianWriter::writeByte(output, _velocity);

            return output;
        }
    }
}
