#include "MidiTrack.h"

namespace Midi {
    std::ostream& operator <<(std::ostream& output, const Track t) {
        output.write(TRACK_IDENTIFIER, 4);

        return output;
    }
}
