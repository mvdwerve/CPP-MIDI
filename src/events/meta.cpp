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
         * Function which prints this event.
         * @param output The output stream to print to.
         * @return std::ostream& The original output stream.
         */
        std::ostream& Meta::print(std::ostream& output) const {
            /* Writing the fixed 0xFF header and the type of the meta event. */
            Endian::writeByte(output, 0xFF);
            Endian::writeByte(output, _type);

            /* Writing the size to the stream. TODO: Horribly wrong, this should be a VLV,
             * FIXME!
             */
            Endian::writeByte(output, _data.size());

            /* Writing the data bytes to the stream. */
            for (auto byte : _data)
                Endian::writeByte(output, byte);

            return output;
        }
    }
}
