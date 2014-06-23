#ifndef MIDIHEADER_h
#define MIDIHEADER_h

namespace Midi {
class Header {
public:
    /* This is "MThd" */
    const static int IDENTIFIER = 0x4D546864;

    Header() {}
};
}

#endif
