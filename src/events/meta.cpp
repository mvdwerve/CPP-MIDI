/**
 * meta.cpp
 *
 * File with implementations for the Midi::Event::Meta class.
 *
 * @author Michael van der Werve
 */

#include <cppmidi/endian.h>
#include <cppmidi/events/meta.h>

/**
 * Setting up the midi and event namespace.
 */
namespace Midi {
    namespace Events {
        /**
         * Method which tries to pop a Meta object from the input stream.
         * @param input The input stream.
         * @return Event* A dynamically allocated event.
         */
        Event* Meta::popEvent(std::istream &input) {
            return NULL;
        }

        /**
         * Function which prints this event.
         * @param output The output stream to print to.
         * @return std::ostream& The original output stream.
         */
        std::ostream& Meta::print(std::ostream& output) const {
            /* Writing the fixed 0xFF header and the type of the meta event. */
            Endian::writeByte(output, 0xFF);
            Endian::writeByte(output, _type);

            /* Writing the VLValue to the stream. */
            output << _dataSize;

            /* Writing the data bytes to the stream. */
            for (auto byte : _data)
                Endian::writeByte(output, byte);

            return output;
        }
    }
}
