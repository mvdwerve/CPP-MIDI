/**
 * vlvalue.cpp
 *
 * File with implementations for the Midi::VLValue class.
 *
 * @author Michael van der Werve
 */

#include <cppmidi/vlvalue.h>
#include <cppmidi/endian.h>
#include <algorithm>
#include <cstdio>

/**
 * Setting up the basic midi namespace.
 */
namespace Midi {
    /**
     * Friend method which will set print this vlvalue correctly to the stream.
     * @param output The output to write to.
     * @param v      The VLValue to be written
     * @return std::ostream& The original stream.
     */
    std::ostream& operator <<(std::ostream& output, const VLValue& v) {
        /* Write all bytes to the ouput stream. */
        for (auto byte : v._bytes)
            Endian::writeByte(output, byte);

        return output;
    }

    /**
     * Friend function to read data from an input stream into a VLValue.
     * @param input The input stream.
     * @param v The VLValue object.
     * @return std::istream& The original stream.
     */
    std::istream& operator >>(std::istream& input, VLValue& v) {
        /* Initialize the values. */
        uint8_t byte = 0x00;
        uint32_t value = 0;
        uint8_t count = 1;

        /* If the read bytes have value on an & with 0x80 it means their highest
         * bit is set. This means there is more to come and the next value will also
         * belong to the VLValue, until this evaluates to false.
         */
        while ((byte = Endian::readByte(input)) & 0x80) {
            value |= (byte & 0x7F);
            value <<= 7;
            count++;
        }

        /* This will add the last byte too, since the value has its lowest 7 bits already
         * empty and the rest shifted.
         */
        value |= byte;

        /* Updating the amount of bytes popped. */
        v._gcount = count;

        /* Setting the value with the setValue function, which will handle the rest. */
        v.setValue(value);

        return input;
    }

    /**
     * Function to put this object BACK on a given input stream.
     * @param input The input stream.
     */
    void VLValue::putBack(std::istream& input) {
        /* Reversing the stream so we can put everything back in order. */
        std::reverse(_bytes.begin(), _bytes.end());

        /* Putting all the bytes back. */
        for (auto byte : _bytes)
            input.putback(byte);

        /* Resetting the object. You can't have your cake and eat it too. */
        _gcount = 0;
        _value = 0;
        _bytes.clear();
    }

    /**
     * Method to set the value of this VLValue.
     * @param value The value to set this VLValue to.
     */
    void VLValue::setValue(uint32_t value) {
        /* Setting the value and clearing the vector, because there might be old bytes in it. */
        _value = value;
        _bytes.clear();

        /* Loops as long as there are values when shifted by 7 to the right, because there fit only
         * 7 bits per byte because of the continuation bit (0x80). This is OR'ed into the value,
         * which will be removed later on for the first value.
         */
        do
            _bytes.push_back((value & 0x7F) | 0x80);
        while ((value >>= 7));

        /* The first byte (which will be the last in moments) should not have 0x80 set. */
        _bytes[0] &= 0x7F;

        /* Reversing the array, since everything is in the wrong order to be written to the stream. */
        std::reverse(_bytes.begin(), _bytes.end());
    }
}
