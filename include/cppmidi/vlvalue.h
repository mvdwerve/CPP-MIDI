/**
 * vlvalue.h
 *
 * This class will handle a variable length value(VLValue). Since these are
 * special entities in midi, everything is in the midi namespace.
 *
 * VLValues look as follows:
 * 1 bit of continue and 7 bits of the number. If the high 1 bit is set, it means
 * that the next value in the stream is part of this value, up to the point that the
 * high bit isn't set any more. This is so we are not constrained in duration for example, because
 * otherwise the largest note would be 255, after which it would turn off.
 *
 * @author Michael van der Werve
 */

#ifndef MIDI_VLVALUE_h
#define MIDI_VLVALUE_h

#include <iostream>
#include <vector>

/**
 * Setting up the basic namespace.
 */
namespace Midi {
    class VLValue {
        public:
            /**
             * Default constructor.
             */
            VLValue() : _gcount(0) { setValue(0); }

            /**
             * Default constructor.
             */
            VLValue(uint32_t number) : _gcount(0) { setValue(number); }

            /**
             * Destructor
             */
            virtual ~VLValue() {}

            /**
             * Friend method which will set print this vlvalue correctly to the stream.
             * @param output The output to write to.
             * @param v      The VLValue to be written
             * @return std::ostream& The original stream.
             */
            friend std::ostream& operator <<(std::ostream& output, const VLValue& v);

            /**
             * Friend function to read data from an input stream into a VLValue.
             * @param input The input stream.
             * @param v The VLValue object.
             * @return std::istream& The original stream.
             */
            friend std::istream& operator >>(std::istream& input, VLValue& v);

            /**
             * Function to put this object BACK on a given input stream.
             * @param input The input stream.
             */
            void putBack(std::istream& input);

            /**
             * Function to get the last amount of bytes popped from an input stream.
             * @return uint8_t The amount of bytes popped from input stream.
             */
            uint8_t gcount() const { return _gcount; }

            /**
             * Method to get the length of this VLValue.
             * @return uint8_t The length it would be when written to a stream.
             */
            uint8_t getLength() const { return _bytes.size(); }

            /**
             * Method to set the value of this VLValue.
             * @param value The value to set this VLValue to.
             */
            void setValue(uint32_t value);

            /**
             * Method to get the value of this VLValue.
             * @return uint32_t The value of this VLValue object as an integer.
             */
            uint32_t getValue() const { return _value; }
        private:

            /**
             * Amount of bytes popped from input stream.
             */
            uint8_t _gcount;

            /**
             * The actual value of the variable to be written. It is assumed this will never be larger than
             * 32 bits, but if it would be, using a larger datatype would not be a problem.
             * @var uint32_t
             */
            uint32_t _value;

            /**
             * The internal vector which makes writing the bytes much easier. Please note that they are in the
             * correct order to be written to the stream, with the MSB first.
             * @var std::vector<uint8_t>
             */
            std::vector<uint8_t> _bytes;
    };
}

#endif
