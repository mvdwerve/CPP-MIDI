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
                 * Constructor from the ID. The type is standard 0xF0 (unsure what other types
                 * do and are for exactly) and the new length becomes 3.
                 * @param id The id of the manufacturer.
                 */
                SysEx(uint8_t id) : Event(), manufacturerID(id), _type(0xF0) { }

                /**
                 * Function which prints this event.
                 * @param output The output stream to print to.
                 * @return std::ostream& The original output stream.
                 */
                virtual std::ostream& print(std::ostream& output) const;


                /**
                 * Method which adds the current data length plus the usual length of
                 * this event.
                 * @return uint64_t The total length in bytes of this sysex event.
                 */
                virtual uint32_t getLength() const { return Event::getLength() + 2 + data.size(); }

                /**
                 * Method to clone the event, should be implemented by derived classes.
                 * @returns Event* the cloned event pointer, which is dynamically allocated.
                 */
                virtual Event* clone() const {
                    return new SysEx(*this);
                }

                /**
                 * Variable with the manufacturer id, which could be anything.
                 * @var uint8_t
                 */
                uint8_t manufacturerID;

                /**
                 * This variable will hold the data - unfortunately we cannot do much
                 * with the data because it varies so much from thing manufacturer to
                 * manufacturer. However this should/could be set in the case of a
                 * system exclusive event.
                 * @var uint8_t
                 */
                std::vector<uint8_t> data;
            private:
                /**
                 * The type of this sysex event.
                 */
                uint8_t _type;
        };
    }
}

#endif
