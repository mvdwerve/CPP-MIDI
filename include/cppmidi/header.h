/**
 * header.h
 *
 * Class for maintaining and easily writing the MIDI header.
 *
 * @author Michael van der Werve
 */

#ifndef MIDI_HEADER_h
#define MIDI_HEADER_h

/**
 * Setting up the midi namespace
 */
namespace Midi {
    /**
     * Enum for the current midi mode, since it should only be constrained
     * to either 0 for singletrack, 1 for multitrack synchronious and 2 for
     * multitrack asynchronious. See MIDI specification online for explaination.
     */
    enum MidiMode {
        SINGLETRACK = 0,
        MULTITRACK_SYNC = 1,
        MULTITRACK_ASYNC = 2
    };

    class Header {
        public:
            /**
             * This is the header identifier, literally "MThd".
             * @var const static char*
             */
            const static char* IDENTIFIER;

            /**
             * Default constructor
             */
            Header();

            /**
             * Destructor
             */
            virtual ~Header() {}

            /**
             * Method to get the currently used fileformat in the MidiMode style.
             * @return MidiMode  The currently used MidiMode.
             */
            MidiMode getFileFormat() { return _fileFormat; }

            /**
             * Method to get the number of tracks. Is always 2 bytes but has a
             * maximum of 16.
             * @return uint16_t Amount of tracks
             */
            uint16_t getNumTracks() { return _numTracks; }

            /**
             * Method to get the delta tick time, which is the amount of ticks per
             * quarter note.
             * @return uint16_t Amount of ticks
             */
            uint16_t getDeltaTicks() { return _deltaTicks; }

            /**
             * Method to set the current file format, constrained to the MidiMode.
             * @param mode The mode to be set.
             */
            void setFileFormat(MidiMode mode) { _fileFormat = mode; }

            /**
             * Method to set the number of tracks currently used in the Midi file.
             * @param num   The number of tracks to be set.
             */
            bool setNumTracks(int num) {
                if (num >= 16)
                    return false;

                _numTracks = num;

                return true;
            }

            /**
             * Method so the stream operator can be used and the header can be written
             * to any stream.
             * @param output The first stream
             * @param head   This header object
             * @return std::ostream& The original stream
             */
            friend std::ostream& operator <<(std::ostream& output, const Header& head);

            /**
             * Method to read the header object from an input stream. The stream should
             * be in binary mode.
             * @param input The input stream.
             * @param head The header object.
             * @return std::istream& THe original input stream.
             */
            friend std::istream& operator >>(std::istream& input, Header& head);

        private:
            /**
             * The currently used fileformat.
             * @var MidiMode
             */
            MidiMode _fileFormat;

            /**
             * The current amount of tracks in the midi file.
             * @var uint16_t
             */
            uint16_t _numTracks;

            /**
             * The current amount of deltaticks used in the midi file.
             * @var uint16_t
             */
            uint16_t _deltaTicks;
    };
}

#endif
