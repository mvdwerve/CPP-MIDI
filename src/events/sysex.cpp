/**
 * sysex.cpp
 *
 * File with implementations for the Midi::Event::SysEx class.
 *
 * @author Michael van der Werve
 */

#include <cppmidi/endian.h>
#include <cppmidi/events/sysex.h>

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
        std::ostream& SysEx::print(std::ostream& output) const {
            /* Writing the type and manufacturerID to the output stream. */
            Endian::writeByte(output, _type);
            Endian::writeByte(output, manufacturerID);

            /* Since we only know the data consists of bytes and apart from that nothing,
             * simply write them to the output stream.
             */
            for (auto byte : _data)
                Endian::writeByte(output, byte);

            /* Writing the end of the SysEx to the stream. */
            Endian::writeByte(output, 0xF7);

            return output;
        }

        /**
         * Method to set the data. Derived classes should also use this, since
         * the new length should be correctly saved.
         * @param data The data to be set.
         */
        void SysEx::setData(std::vector<uint8_t> data) {
            _data = data;
            _dataLength = data.size();
        }
    }
}
