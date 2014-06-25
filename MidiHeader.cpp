#include <fstream>
#include <iostream>
#include <string>
#include <arpa/inet.h>
#include "MidiHeader.h"
#include "MidiFile.h"

namespace Midi {
    /* XXX:2014-06-25:mvdwerve: Deltaticks should be calculated with a time signature. */
    Header::Header() : _fileFormat(MidiMode::MULTITRACK_SYNC), _deltaTicks(64) {

    }

    Header::~Header() {

    }

    std::ostream& operator <<(std::ostream& output, const Header &head) {
        output.write(HEADER_IDENTIFIER, 4);

        File::writeIntBig(output, 6);
        File::writeShortBig(output, head._fileFormat);
        File::writeShortBig(output, head._numTracks);
        File::writeShortBig(output, head._deltaTicks);

        return output;
    }
}
