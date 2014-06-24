#ifndef MIDITRACK_h
#define MIDITRACK_h

#include <iostream>

namespace Midi {
    class Track {
        public:
            /* This is "MTrk" */
            const static int IDENTIFIER = 0x4D54726B;

            Track() {}

            friend std::ostream& operator <<(std::ostream& output, const Track t);
    };
}

#endif
