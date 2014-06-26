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
                 * @todo Variable length, since 4 is for the stubs.
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

                /**
                 * Method to get the status byte from the current message.
                 * @return uint8_t The status in 8 bits.
                 */
                uint8_t getStatus() { return _status; }

                /**
                 * Method to get the note from this message.
                 * @return uint8_t The current notebyte of the message.
                 */
                uint8_t getNote() { return _note; }

                /**
                 * Method to get the velocity of the message.
                 * @return uint8_t The current velocity byte.
                 */
                uint8_t getVelocity() { return _velocity; }


                /**
                 * Method to set the status byte from the current message.
                 * @param status The status byte.
                 */
                void setStatus(uint8_t status) { _status = status; }

                /**
                 * Method to set the note from this message.
                 * @param note The velocity byte.
                 */
                void setNote(uint8_t note) { _note = note; }

                /**
                 * Method to set the velocity of the message.
                 * @param velocity The velocity byte.
                 */
                void setVelocity(uint8_t velocity) { _velocity = velocity; }
            private:
                /**
                 * Current status bit.
                 * @var uint8_t
                 */
                uint8_t _status;

                /**
                 * Note for this message.
                 * @var uint8_t
                 */
                uint8_t _note;

                /**
                 * Current velocity.
                 * @var uint8_t
                 */
                uint8_t _velocity;
        };
    }
}

#endif
