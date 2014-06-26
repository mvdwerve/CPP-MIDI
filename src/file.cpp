/**
 * file.cpp
 *
 * File with implementations for the Midi::File class.
 *
 * @author Michael van der Werve
 */

#include <cppmidi/file.h>

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
    bool File::addTrack(Track* t) {
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
            output << *track;

        return output;
    }

}
