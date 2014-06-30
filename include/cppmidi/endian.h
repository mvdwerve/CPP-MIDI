/**
 * endian.h
 *
 * Class should only be used statically and used for writing endian sensitive data such
 * as ints and shorts. Will correctly write it to a stream cross-machine, in spite of endians.
 *
 * @author Michael van der Werve
 */

#ifndef MIDI_endian_h
#define MIDI_endian_h

#include <iostream>

/**
 * Define to swap a short and switch the endianness. Please note that this will completely ignore
 * any bits higher than the first 16 bits. Smaller datatype behaviour is undefined.
 */
#define SWAP_SHORT(s) ((s & 0xFF) << 8 | (s & 0xFF00) >> 8)

/**
 * Define to swap an integer to a different endianness. Please note that this will completely
 * ignore any bits higher than the first 32 bits. Smaller datatype behaviour is undefined.
 */
#define SWAP_INT(i) ((i & 0xFF) << 24 | (i & 0xFF00) << 8 | (i & 0xFF0000) >> 8 | (i & 0xFF000000) >> 24)

/**
 * Define to convert any number to a char*, so the complete number can be written to an output
 * stream instead of converting it to a string.
 */
#define CHARPTR(i) (reinterpret_cast<const char*>(&i))

/**
 * Setting up the midi namespace
 */
namespace Midi {
    class Endian {
        public:
            /**
             * This boolean will tell if the computer is using little endian or big
             * endian. This is important for writing to files, since many primitive
             * datatypes have to be swapped.
             * @var const static bool
             */
            const static bool modeBigEndian;

            /**
             * Helper function for writing a cross platform big endian int.
             * @param i       The int which should be written in the endian.
             * @param stream  The stream to be written to.
             */
            inline static void writeIntBig(std::ostream &stream, uint32_t i) {
                uint32_t result = (Endian::modeBigEndian) ? i : SWAP_INT(i);

                stream.write(CHARPTR(result), sizeof(i));
            }

            /**
             * Helper function for writing a cross platform little endian int.
             * @param i       The short which should be written in the endian.
             * @param stream  The stream to be written to.
             */
            inline static void writeIntLittle(std::ostream &stream, uint32_t i) {
                uint32_t result = (Endian::modeBigEndian) ? SWAP_INT(i) : i;

                stream.write(CHARPTR(result), sizeof(i));
            }

            /**
             * Helper function for writing a cross platform big endian short.
             * @param s       The short which should be written in the endian.
             * @param stream  The stream to be written to.
             */
            inline static void writeShortBig(std::ostream &stream, uint16_t s) {
                uint16_t result = (Endian::modeBigEndian) ? s : SWAP_SHORT(s);

                stream.write(CHARPTR(result), sizeof(s));
            }

            /**
             * Helper function for writing a cross platform little endian short.
             * @param s       The short which should be written in the endian.
             * @param stream  The stream to be written to.
             */
            inline static void writeShortLittle(std::ostream &stream, uint16_t s) {
                uint16_t result = (Endian::modeBigEndian) ? SWAP_SHORT(s) : s;

                stream.write(CHARPTR(result), sizeof(s));
            }

            /**
             * Helper function for writing a cross platform byte.
             * @param c         The char (uint8_t) to be written.
             * @param stream    The stream to be written to.
             * @todo Maybe remove, because might be superfluous.
             */
            inline static void writeByte(std::ostream &stream, uint8_t a) {
                stream << (char) a;
            }


            /**
             * Helper function for reading a cross platform big endian int.
             * @param input  The stream to be read from.
             */
            inline static uint32_t readIntBig(std::istream &input) {
                char *bytes = new char[4];
                input.read(bytes, 4);

                uint32_t tmp = *(reinterpret_cast<uint32_t*>(bytes));
                delete bytes;

                return (Endian::modeBigEndian) ? tmp : SWAP_INT(tmp);
            }

            /**
             * Helper function for reading a cross platform little endian int.
             * @param input  The stream to be read from.
             */
            inline static uint32_t readIntLittle(std::istream &input) {
                return SWAP_INT(readIntBig(input));
            }

            /**
             * Helper function for reading a cross platform big endian short.
             * @param input  The stream to be read from.
             */
            inline static uint16_t readShortBig(std::istream &input) {
                char *bytes = new char[2];
                input.read(bytes, 2);

                uint16_t tmp = *(reinterpret_cast<uint16_t*>(bytes));
                delete bytes;

                return (Endian::modeBigEndian) ? tmp : SWAP_SHORT(tmp);
            }


            /**
             * Helper function for reading a cross platform little endian int.
             * @param input  The stream to be read from.
             */
            inline static uint16_t readShortLittle(std::istream &input) {
                return SWAP_SHORT(readShortBig(input));
            }

            /**
             * Helper function for reading a cross platform byte.
             * @param input    The stream to be read from.
             * @todo Maybe remove, because might be superfluous.
             */
            inline static uint8_t readByte(std::istream &input) {
                char byte;
                input.read(&byte, 1);

                return byte;
            }
    };
}

#endif
