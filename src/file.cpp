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

    /**
     * Method to input the file into the midi object. The stream should be in binary mode.
     * @param input The input stream.
     * @param f The midi file object.
     * @return std::istream& THe original input stream.
     */
    std::istream& operator >>(std::istream& input, File& f) {
        input >> f._head;

        /* The number of tracks previously read in the header. */
        uint16_t numTracks = f._head.getNumTracks();

        /* Only read as much tracks as the header says. */
        for (int i = 0; i < numTracks; i++) {
            /* Dynamically allocate the track and use the stream operator to put it in the track. */
            f._tracks[i] = new Track();
            input >> *(f._tracks[i]);
        }

        return input;
    }
}
