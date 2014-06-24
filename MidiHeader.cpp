#include <fstream>
#include <iostream>
#include "MidiHeader.h"

namespace Midi {
    std::ostream& operator <<(std::ostream& output, const Header head) {
        output << Header::IDENTIFIER << Header::LENGTH;

        return output;
    }
}
