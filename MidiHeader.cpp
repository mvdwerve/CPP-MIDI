#include <fstream>
#include <iostream>
#include "MidiHeader.h"

namespace Midi {
    Header::Header() : _fileFormat(MidiMode::MULTITRACK_SYNC), _deltaTicks(1) {

    }

    Header::~Header() {

    }

    std::ostream& operator <<(std::ostream& output, const Header head) {
        char format[4] = {0};
        char len[4] = {0};
        char time[4] = {0};

        format[3] = (char) head._fileFormat;
        len[3] = (char) head._numTracks;

        output.write(HEADER_IDENTIFIER, 4);
        output.write(HEADER_LENGTH, 4);
        output.write(format, 4);
        output.write(len, 4);
        output.write(time, 4);
        return output;
    }
}
