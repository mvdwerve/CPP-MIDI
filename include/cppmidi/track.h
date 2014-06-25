#ifndef MIDI_TRACK_h
#define MIDI_TRACK_h

#include <iostream>

namespace Midi {
    class Track {
    public:
        const static char* IDENTIFIER;
        friend std::ostream& operator <<(std::ostream& output, const Track& t);

    private:
        uint32_t _length;
    };
}

#endif
