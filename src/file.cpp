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
    File::File(const std::string str) : _tracks() {
        /* XXX:2014-6-24:mvdwerve: fstream is now used for writing only and truncated on read. */
        _file.open(str, std::ios::trunc | std::ios::binary | std::ios::out);
    }

    /**
     * Destructor
     */
    File::~File() {
        /* Tracks are dynamically allocated by us, and should thus be freed. */
        for (auto track : _tracks)
            delete track;

        /* Flush and close the file. */
        _file.flush();
        _file.close();
    }

    /**
     * Method to get an new, empty track from the file. Might return NULL.
     * @return Track* Pointer to a Track from the file. NULL if there was no new track.
     */
    Track* File::getTrack() {
        /* If we can set the header, we can be sure there is an available track somewhere. */
        if (!_head.setNumTracks(_head.getNumTracks() + 1))
            return NULL;

        for (int i = 0; i < 16; i++) {

            /* If an empty spot was found, create a new track at that spot and
             * return the resulting pointer.
             */
            if (_tracks[i] == NULL)
                return (_tracks[i] = new Track());
        }

        /* Fallback, for whatever case there might be no track available. */
        return NULL;
    }

    /**
     * Method to get an arbitrary track from the file. Might return NULL, if index is too large.
     * @return Track* Pointer to a Track from the file. NULL if there was no new track.
     */
    Track* File::getTrack(int index) {
        /* We cannot create nor get a track from indexes higher than 15. */
        if (index > 15 || index < 0)
            return NULL;

        /* Create a new track if it does not already exist. */
        if (_tracks[index] == NULL) {
            _tracks[index] = new Track();
            _head.setNumTracks(_head.getNumTracks() + 1);
        }

        return _tracks[index];
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

        for (auto track : f._tracks) {
            if (track != NULL)
                output << *track;
        }

        return output;
    }

}
