#include "MidiFile.h"

using Midi::File;

int main(int argc, char* argv[]) {
    File midi("test.mid");
    midi.write();
}
