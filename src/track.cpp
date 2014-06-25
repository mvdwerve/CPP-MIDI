/**
 * track.cpp
 *
 * File with implementations for the Midi::Track class.
 *
 * @author Michael van der Werve
 */

#include <cppmidi/track.h>

/**
 * Setting up the basic midi namespace.
 */
namespace Midi {
    /**
     * Identifier for midi tracks, which is basically "MTrk".
     * @var const static char*
     */
    const char* Track::IDENTIFIER = "MTrk";

    /**
     * Stream operator so the track info can be written to any output.
     * @param output Output stream
     * @param t      Track to be written to the output
     * @return std::ostream& Original output stream.
     */
    std::ostream& operator <<(std::ostream& output, const Track& t) {
        output.write(Track::IDENTIFIER, 4);

        for (auto event : t._events)
            output << *event;

        return output;
    }
}
