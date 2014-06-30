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
#include <cppmidi/endian.h>
#include <cppmidi/vlvalue.h>

/**
 * Setting up the basic namespace.
 */
namespace Midi {
    class Event {
        public:
            /**
             * Default constructor.
             */
            Event() : deltaTime(0), _gcount(0) {}

            /**
             * Destructor
             */
            virtual ~Event() {}

            /**
             * Abstract function, since the operator cannot be declared abstract an extra
             * indirection was needed. Since this function will be overridden by its childen,
             * everything will be alright.
             * @param output The output stream to print to.
             * @return std::ostream& The original output stream.
             */
            virtual std::ostream& print(std::ostream& output) const = 0;

            /**
             * Method to clone the event, should be implemented by derived classes.
             * @returns Event* the cloned event pointer, which is dynamically allocated.
             */
            virtual Event* clone() const = 0;

            virtual uint32_t gcount() const {
                return _gcount;
            }

            /**
             * Friend function to efficiently print any and all event to an output stream, since
             * the derived classes will have implemented the print method.
             * @param output The output stream to be written to.
             * @param t      The event.
             */
            friend std::ostream& operator <<(std::ostream& output, const Event& t) {
                output << t.deltaTime;
                return t.print(output);
            }

            /**
             * Method to return the length of this event, which can be very large.
             * @return uint32_t
             */
            virtual uint32_t getLength() const { return deltaTime.getLength(); }

            /**
             * Time difference since last event. Since this can be anything, the trivial accessor is
             * omitted.
             * @var VLValue
             */
            VLValue deltaTime;
        protected:
            /**
             * The variable which will hold the amount of last popped characters from an input stream.
             * @var uint32_t
             */
            uint32_t _gcount;
    };
}

#endif
