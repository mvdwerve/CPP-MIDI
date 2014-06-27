/**
 * sysex.h
 *
 * Class for a sysex event.
 *
 * @author Michael van der Werve
 */

#ifndef MIDI_EVENT_SYSEX_h
#define MIDI_EVENT_SYSEX_h

#include <iostream>
#include <vector>
#include <cppmidi/event.h>

/**
 * Setting up the basic namespace.
 */
namespace Midi {
    namespace Events {
        class SysEx : public Event {
            public:
                /**
                 * Constructor.
                 * @param id The id of the manufacturer.
                 */
                SysEx(uint8_t id) { manufacturerID = id; }

                /**
                 * Function which prints this event.
                 * @param output The output stream to print to.
                 * @return std::ostream& The original output stream.
                 */
                virtual std::ostream& print(std::ostream& output) const;

                /**
                 * Method to set the data. Derived classes should also use this, since
                 * the new length should be correctly saved.
                 * @param data The data to be set.
                 */
                void setData(std::vector<uint8_t> data);

                /**
                 * Variable with the manufacturer id, which could be anything.
                 * @var uint8_t
                 */
                uint8_t manufacturerID;
            private:
                /**
                 * This variable holds the internal data length.
                 * @var uint64_t
                 */
                uint64_t _dataLength;

                /**
                 * The type of this sysex event.
                 */
                uint8_t _type;

                /**
                 * This variable will hold the data - unfortunately we cannot do much
                 * with the data because it varies so much from thing manufacturer to
                 * manufacturer. However this should/could be set in the case of a system exclusive event.
                 * @var uint8_t
                 */
                std::vector<uint8_t> _data;
        };
    }
}

#endif
