/**
 * midi.h
 *
 * Class for a basic midi message. A midi message is anything with a status message
 * set from 0x80 to 0xEF.
 *
 * @author Michael van der Werve
 */

#ifndef MIDI_EVENT_MIDI_h
#define MIDI_EVENT_MIDI_h

#include <iostream>
#include <cppmidi/event.h>

/**
 * Setting up the basic namespace.
 */
namespace Midi {
    namespace Events {
        class Message : public Event {
            public:
                /**
                 * Constructor
                 * @todo Variable length, since 3 is for the stubs.
                 */
                Message();

                /**
                 * Destructor
                 */
                virtual ~Message() {}

                /**
                 * Function which prints this event.
                 * @param output The output stream to print to.
                 * @return std::ostream& The original output stream.
                 */
                virtual std::ostream& print(std::ostream& output) const;
        };
    }
}

#endif
