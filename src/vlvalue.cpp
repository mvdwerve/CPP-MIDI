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
        std::cout << v._value << std::endl;

        for (auto byte : v._bytes) {
            printf("%.2X ", byte);
            Endian::writeByte(output, byte);
        }

        std::cout << std::endl << std::endl;
        return output;
    }

    /**
     * Method to set the value of this VLValue.
     * @param value The value to set this VLValue to.
     */
    void VLValue::setValue(uint32_t value) {
        uint32_t newValue;

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
