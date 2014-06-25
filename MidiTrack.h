#ifndef MIDITRACK_h
#define MIDITRACK_h

#include <iostream>
#define TRACK_IDENTIFIER "MTrk"

namespace Midi {
    class Track {
        public:
            Track() {}

            friend std::ostream& operator <<(std::ostream& output, const Track t);
    };
}

#endif
