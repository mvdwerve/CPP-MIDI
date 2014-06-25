/**
 * event.h
 *
 * Abstract class for the basic midi message, which can have a variable length
 * and can be played on different channels. This class will be extended by classes
 * in the events/ directory.
 *
 * @author Michael van der Werve
 */

#ifndef MIDI_EVENT_h
#define MIDI_EVENT_h

#include <iostream>
#include <vector>

/**
 * Setting up the basic namespace.
 */
namespace Midi {
    class Event {
    public:
        /**
         * Abstract function, since the operator cannot be declared abstract an extra
         * indirection was needed. Since this function will be overridden by its childen,
         * everything will be alright.
         * @param output The output stream to print to.
         * @return std::ostream& The original output stream.
         */
        virtual std::ostream& print(std::ostream& output) const = 0;

        /**
         * Friend function to efficiently print any and all event to an output stream, since
         * the derived classes will have implemented the print method.
         * @param output The output stream to be written to.
         * @param t      The event.
         */
        friend std::ostream& operator <<(std::ostream& output, const Event& t) {
            return t.print(output);
        }

        /**
         * Method to return the current channel which is played to.
         * @return uint8_t
         */
        uint8_t getChannel() { return _channel; }

        /**
         * Method to return the length of this event, which can be very large.
         * @return uint64_t
         */
        uint64_t getLength() { return _length;  }
    protected:
        /**
         * Variable to keep track of the current channel.
         * @var uint8_t
         */
        uint8_t _channel;

        /**
         * Length of this event. Since the SysEx event can be virtually limitless in data because
         * the midi file specification gives no limit, it has to be a 64 bit number to prevent any
         * overflows.
         */
        uint64_t _length;
    };
}

#endif
