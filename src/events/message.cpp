/**
 * message.cpp
 *
 * File with implementations for the Midi::Event::Message class.
 *
 * @author Michael van der Werve
 */

#include <cppmidi/endian.h>
#include <cppmidi/events/message.h>

/**
 * Setting up the midi and event namespace.
 */
namespace Midi {
    namespace Events {
        /**
         * Constructor
         * @param m The messagetype for this new message.
         */
        Message::Message(MessageType m) : Message(m, 0, 0, 0) { }

        /**
         * Constructor, which will directly construct a message with the specified values.
         * @warn This constructor will clamp all incorrect data to their min/max values.
         * @param m The type of this message.
         * @param channel The channel the message should be played on.
         * @param data1 The value of the first data byte.
         * @param data2 The value of the second data byte.
         */
        Message::Message(MessageType m, uint8_t channel, uint8_t data1, uint8_t data2) : Event() {
            setType(m);
            setChannel(channel);
            setData1(data1);
            setData2(data2);
        }

        /**
         * Method which tries to pop a Message from the input stream.
         * @param input The input stream.
         * @return Event* A dynamically allocated event.
         */
        Event* Message::popEvent(std::istream &input) {
            /* Allocating the new message. */
            Message *msg = new Message();

            /* Popping the VLValue from the stream, which can never go wrong (syntax). */
            input >> msg->deltaTime;

            uint8_t status = Endian::readByte(input);
            uint8_t type = status >> 4;

            ++(msg->_gcount);

            /* If we can successfully pass this if statement, we're safe. */
            if (type < MessageType::NOTE_OFF || type > MessageType::PITCH_BEND) {
                /* TODO:: RESTORE THE STREAM */

                delete msg;
                return NULL;
            }

            /* Setting up the object and setting the data */
            msg->_type = type;
            msg->_channel = status & 0xF;
            msg->_data1 = Endian::readByte(input);

            ++(msg->_gcount);

            /* If this isn't a program change or channel aftertouch, read one more byte of data. */
            if (type != MessageType::PROGRAM_CHANGE && type != MessageType::CHANNEL_AFTERTOUCH) {
                msg->_data2 = Endian::readByte(input);
                ++(msg->_gcount);
            }

            return msg;
        }

        /**
         * Function which prints this event.
         * @param output The output stream to print to.
         * @return std::ostream& The original output stream.
         */
        std::ostream& Message::print(std::ostream& output) const {
            Endian::writeByte(output, _type << 4 | _channel);
            Endian::writeByte(output, _data1);

            /* The last data byte should be omitted if we're writing a program change or
             * channel aftertouch event.
             */
            if (_type != MessageType::PROGRAM_CHANGE && _type != MessageType::CHANNEL_AFTERTOUCH)
                Endian::writeByte(output, _data2);

            return output;
        }
    }
}
