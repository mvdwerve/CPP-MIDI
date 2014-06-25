/**
 * file.cpp
 *
 * File with implementations for the Midi::File class.
 *
 * @author Michael van der Werve
 */

#include <cppmidi/file.h>
#include <arpa/inet.h>

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
 * Setting up the basic midi namespace
 */
namespace Midi {
    /**
     * Constructor
     * @param name  Name of the file to be opened
     */
    File::File(const std::string str) {
        /* XXX:2014-6-24:mvdwerve: fstream is now used for writing only and truncated on read. */
        _file.open(str, std::ios::trunc | std::ios::binary | std::ios::out);

    }

    /**
     * This boolean will tell if the computer is using little endian or big
     * endian. This is important for writing to files, since many primitive
     * datatypes have to be swapped.
     * @var const static bool
     */
    const bool File::modeBigEndian = (ntohl(1) == 1);

    /**
     * Destructor
     */
    File::~File() {
        _file.flush();
        _file.close();
    }

    /**
     * Function to add a Midi::Track to this midi file by reference.
     * @param  t     Track to be added by reference.
     * @return bool  True if track was added, false otherwise (too much tracks).
     */
    bool File::addTrack(const Track& t) {
        /* If the head returns false, we cannot add another track and a track should
         * be removed from the file first.
         */
        if (!_head.setNumTracks(_head.getNumTracks() + 1))
            return false;

        _tracks.push_back(t);

        return true;
    }

    /**
     * Friend function to overload the operator to write to streams, used for
     * file writing. This makes it that the midi can be written to virtually
     * everything as long as it is an outputstream.
     * @param output            The output stream
     * @param f                 The file with which the operator was used.
     * @returns std::ostream    Original stream.
     */
    std::ostream& operator <<(std::ostream& output, const File& f) {
        output << f._head;

        for (auto track : f._tracks)
            output << track;

        return output;
    }

    /**
     * Helper function for writing a cross platform big endian int.
     * @param i       The int which should be written in the endian.
     * @param stream  The stream to be written to.
     */
    void File::writeIntBig(std::ostream &stream, uint32_t i) {
        uint32_t result = (File::modeBigEndian) ? i : SWAP_INT(i);

        stream.write(CHARPTR(result), sizeof(i));
    }

    /**
     * Helper function for writing a cross platform little endian int.
     * @param i       The short which should be written in the endian.
     * @param stream  The stream to be written to.
     */
    void File::writeIntLittle(std::ostream &stream, uint32_t i) {
        uint32_t result = (File::modeBigEndian) ? SWAP_INT(i) : i;

        stream.write(CHARPTR(result), sizeof(i));
    }

    /**
     * Helper function for writing a cross platform big endian short.
     * @param s       The short which should be written in the endian.
     * @param stream  The stream to be written to.
     */
    void File::writeShortBig(std::ostream &stream, uint16_t s) {
        uint16_t result = (File::modeBigEndian) ? s : SWAP_SHORT(s);

        stream.write(CHARPTR(result), sizeof(s));
    }

    /**
     * Helper function for writing a cross platform little endian short.
     * @param s       The short which should be written in the endian.
     * @param stream  The stream to be written to.
     */
    void File::writeShortLittle(std::ostream &stream, uint16_t s) {
        uint16_t result = (File::modeBigEndian) ? SWAP_SHORT(s) : s;

        stream.write(CHARPTR(result), sizeof(s));
    }

    /**
     * Helper function for writing a cross platform byte.
     * @param c         The char (uint8_t) to be written.
     * @param stream    The stream to be written to.
     * @todo Maybe remove, because might be superfluous.
     */
    void File::writeByte(std::ostream &stream, uint8_t a) {
        stream << (char) a;
    }
}
