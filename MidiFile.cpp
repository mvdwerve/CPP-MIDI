#include "MidiFile.h"
#include <iomanip>

namespace Midi {
    File::File(const std::string str) {
        /* XXX:2014-6-24:mvdwerve: fstream is now used for reading only and truncated. */
        _file.open(str, std::ios::trunc | std::ios::binary | std::ios::out);

        /* Prepares the file for binary hex writing */
        //_file << std::hex << std::setfill('0') << std::setw(2);
    }

    File::~File() {
        _file.flush();
        _file.close();
    }

    std::ostream& operator <<(std::ostream& output, const File& f) {
        output << f._head;

        for (auto track : f._tracks)
            output << track;

        return output;
    }
}
