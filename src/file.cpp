#include <cppmidi/file.h>
#include <arpa/inet.h>

#define SWAP_SHORT(s) ((s & 0xFF) << 8 | (s & 0xFF00) >> 8)
#define SWAP_INT(i) ((i & 0xFF) << 24 | (i & 0xFF00) << 8 | (i & 0xFF0000) >> 8 | (i & 0xFF000000) >> 24)
#define CHARPTR(i) (reinterpret_cast<const char*>(&i))

namespace Midi {
    File::File(const std::string str) {
        /* XXX:2014-6-24:mvdwerve: fstream is now used for writing only and truncated on read. */
        _file.open(str, std::ios::trunc | std::ios::binary | std::ios::out);

    }

    const bool File::modeBigEndian = (ntohl(1) == 1);

    File::~File() {
        _file.flush();
        _file.close();
    }

    bool File::addTrack(const Track& t) {
        if (!_head.setNumTracks(_head.getNumTracks() + 1))
            return false;

        _tracks.push_back(t);
        return true;
    }

    std::ostream& operator <<(std::ostream& output, const File& f) {
        output << f._head;

        for (auto track : f._tracks)
            output << track;

        return output;
    }

    void File::writeIntBig(std::ostream &stream, uint32_t i) {
        uint32_t result = (File::modeBigEndian) ? i : SWAP_INT(i);

        stream.write(CHARPTR(result), sizeof(i));
    }

    void File::writeIntLittle(std::ostream &stream, uint32_t i) {
        uint32_t result = (File::modeBigEndian) ? SWAP_INT(i) : i;

        stream.write(CHARPTR(result), sizeof(i));
    }

    void File::writeShortBig(std::ostream &stream, uint16_t s) {
        uint16_t result = (File::modeBigEndian) ? s : SWAP_SHORT(s);

        stream.write(CHARPTR(result), sizeof(s));
    }

    void File::writeShortLittle(std::ostream &stream, uint16_t s) {
        uint16_t result = (File::modeBigEndian) ? SWAP_SHORT(s) : s;

        stream.write(CHARPTR(result), sizeof(s));
    }

    void File::writeByte(std::ostream &stream, uint8_t a) {
        stream << (char) a;
    }
}
