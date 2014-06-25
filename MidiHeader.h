#ifndef MIDIHEADER_h
#define MIDIHEADER_h

#define HEADER_IDENTIFIER "MThd"
#define HEADER_LENGTH "\0\0\0\6"

namespace Midi {
    enum MidiMode {
        SINGLETRACK = 0,
        MULTITRACK_SYNC = 1,
        MULTITRACK_ASYNC = 2
    };

    class Header {
        public:
            Header();
            virtual ~Header();

            MidiMode getFileFormat() { return _fileFormat; }
            int getNumTracks() { return _numTracks; }
            int getDeltaTicks() { return _deltaTicks; }

            void setFileFormat(MidiMode mode) { _fileFormat = mode; }
            bool setNumTracks(int num) {
                if (num >= 16)
                    return false;

                _numTracks = num;
                return true;
            }

            friend std::ostream& operator <<(std::ostream& output, const Header& head);
        private:
            MidiMode _fileFormat;
            int _numTracks;
            int _deltaTicks;
    };
}

#endif
