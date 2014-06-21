#ifndef MIDIHEADER_h
#define MIDIHEADER_h

namespace Midi {
class MidiHeader {
public:
    /* This is "MThd" */
    const static int IDENTIFIER = 0x4D546864;

    MidiHeader() {}
}
}

#endif
