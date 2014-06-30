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
            /* Allocating the new message. */
            Meta *meta = new Meta();

            /* Popping the VLValue from the stream, which can never go wrong (syntax). */
            input >> meta->deltaTime;

            /* This should be 0xFF */
            uint8_t head = Endian::readByte(input);

            /* The header is fixed 0xFF, so if this is a mismatch this is not a Meta Event. */
            if (head != 0xFF) {
                /* Simply put the head and the vlv back on the stream. */
                input.putback(head);
                meta->deltaTime.putBack(input);

                delete meta;
                return NULL;
            }

            /* Reading the type and de vlv datasize from the stream. */
            meta->_type = Endian::readByte(input);
            input >> meta->_dataSize;

            uint32_t dataSize = meta->_dataSize.getValue();

            /* Updating the amount of bytes read on this metaevent. */
            meta->_gcount += dataSize + meta->_dataSize.gcount() + 2;

            /* Putting all the data in the array. Might be in wrong order? */
            while (dataSize--)
                meta->_data.push_back(Endian::readByte(input));

            return meta;
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
