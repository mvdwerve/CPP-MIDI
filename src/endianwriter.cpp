/**
 * endianwriter.cpp
 *
 * File with implementations for the Midi::EndianWriter class.
 *
 * @author Michael van der Werve
 */

#include <cppmidi/endianwriter.h>

/**
 * Setting up the basic midi namespace.
 */
namespace Midi {
    /**
     * This boolean will tell if the computer is using little endian or big
     * endian. This is important for writing to files, since many primitive
     * datatypes have to be swapped.
     * @var const static bool
     */
    const bool EndianWriter::modeBigEndian = (ntohl(1) == 1);
}

