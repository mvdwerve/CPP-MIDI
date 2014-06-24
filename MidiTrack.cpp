#include "MidiTrack.h"

namespace Midi {
    std::ostream& operator <<(std::ostream& output, const Track t) {
        output << Track::IDENTIFIER;

        return output;
    }
}
