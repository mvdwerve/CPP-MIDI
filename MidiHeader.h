#ifndef MIDIHEADER_h
#define MIDIHEADER_h

namespace Midi {
    enum MidiMode {
        SINGLETRACK = 0,
        MULTITRACK_SYNC = 1,
        MULTITRACK_ASYNC = 2
    };

    class Header {
        public:
            /* This is "MThd" */
            const static int IDENTIFIER = 0x4D546864;
            const static int LENGTH = 6;

            Header() : _fileFormat(MidiMode::MULTITRACK_SYNC), _deltaTicks(1) {}

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

            friend std::ostream& operator <<(std::ostream& output, const Header head);
        private:
            MidiMode _fileFormat;
            int _numTracks;
            int _deltaTicks;
    };
}

#endif
