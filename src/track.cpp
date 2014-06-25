#include <cppmidi/track.h>

namespace Midi {
    const char* Track::IDENTIFIER = "MTrk";

    std::ostream& operator <<(std::ostream& output, const Track& t) {
        output.write(Track::IDENTIFIER, 4);

        for (auto event : t._events)
            output << *event;

        return output;
    }
}
