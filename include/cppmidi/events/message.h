/**
 * midi.h
 *
 * Class for a basic midi message. A midi message is anything with a status message
 * set from 0x80 to 0xEF.
 *
 * @author Michael van der Werve
 */

#ifndef MIDI_EVENT_MESSAGE_h
#define MIDI_EVENT_MESSAGE_h

#include <iostream>
#include <cppmidi/event.h>

/**
 * Setting up the basic namespace.
 */
namespace Midi {
    namespace Events {
        /**
         * Enum to indicate the message type, since this message type is limited to very select
         * cases. Names are quite explanatory, otherwise see midi specification for details on the
         * different kind of events.
         */
        enum MessageType {
            NOTE_OFF = 0x8,
            NOTE_ON = 0x9,
            NOTE_AFTERTOUCH = 0xA,
            CONTROLLER = 0xB,
            PROGRAM_CHANGE = 0xC,
            CHANNEL_AFTERTOUCH = 0xD,
            PITCH_BEND = 0xE
        };

        class Message : public Event {
            public:
                /**
                 * Constructor
                 * @param m The type of message to be constructed,
                 */
                Message(MessageType m);

                /**
                 * Constructor, which will directly construct a message with the specified values.
                 * @warn This constructor will clamp all incorrect data to their min/max values.
                 * @param m The type of this message.
                 * @param channel The channel the message should be played on.
                 * @param data1 The value of the first data byte.
                 * @param data2 The value of the second data byte.
                 */
                Message(MessageType m, uint8_t channel, uint8_t data1, uint8_t data2);

                /**
                 * Copy constructor.
                 * @param m The message to be copied.
                 */
                //Message(const Message& m);

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
                 * Method to clone the event, should be implemented by derived classes.
                 * @returns Event* the cloned event pointer, which is dynamically allocated.
                 */
                virtual Event* clone() const {
                    /* The data is only primitive, so the normal copy constructor will suffice. */
                    return new Message(*this);
                }

                /**
                 * Method to get the type byte from the current message.
                 * @return uint8_t The type as 8 bits, but maximum value of 4 bits.
                 */
                uint8_t getType() const { return _type; }

                /**
                 * Method to get the channel byte from the current message.
                 * @return uint8_t The type as 8 bits, but maximum value of 4 bits.
                 */
                uint8_t getChannel() const { return _channel; }

                /**
                 * Method to get the length of this message in bytes. This will depend on the type
                 * of this message, since some messages ignore the 4th byte.
                 * @return uint32_t The length in bytes.
                 */
                virtual uint32_t getLength() const {
                    if (_type == MessageType::PROGRAM_CHANGE
                            || _type == MessageType::CHANNEL_AFTERTOUCH)
                        return 2 + Event::getLength();
                    else
                        return 3 + Event::getLength();
                }

                /**
                 * Method to set the type byte for the current message. This could alter the length if
                 * it is a program change or channel aftertouch event, in which case the last byte is not
                 * used.
                 * @param t Type as a MessageType.
                 */
                void setType(MessageType t) { _type = t; }

                /**
                 * Method to set the note from this message. The channel number cannot exceed 16 so
                 * the maximum channel is clamped to 15.
                 * @param note The velocity nibble.
                 */
                void setChannel(uint8_t channel) { _channel = (channel < 16) ? channel : 15; }

                /**
                 * Method to set the first data byte. This is always clamped between 0 and 127
                 * because otherwise it might collide with some other messages.
                 * @param data The first databyte.
                 */
                void setData1(uint8_t data) { _data1 = (data < 128) ? data : 127; }

                /**
                 * Method to set the second data byte. This is always clamped between 0 and 127
                 * because otherwise it might collide with some other messages.
                 * @param data The second databyte.
                 */
                void setData2(uint8_t data) { _data2 = (data < 128) ? data : 127; }
            private:
                /**
                 * Current type byte, with the high nibble set to the status. Ranges from 0x8 to 0xE.
                 * @var uint8_t
                 */
                uint8_t _type;

                /**
                 * Current note channel. Ranges from 0-15.
                 * @var uint8_t
                 */
                uint8_t _channel;

                /**
                 * Data byte one, used in all events. Ranges from 0-127.
                 * @var uint8_t
                 */
                uint8_t _data1;

                /**
                 * Data byte two, used in all events except for the program change and the
                 * channel aftertouch. Ranges from 0-127.
                 * @var uint8_t
                 */
                uint8_t _data2;
        };
    }
}

#endif
