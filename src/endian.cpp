/**
 * endian.cpp
 *
 * File with implementations for the Midi::Endian class.
 *
 * @author Michael van der Werve
 */

#include <cppmidi/endian.h>
#include <arpa/inet.h>

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
    const bool Endian::modeBigEndian = (ntohl(1) == 1);
}

