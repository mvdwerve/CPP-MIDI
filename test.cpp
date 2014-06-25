#include <cppmidi/file.h>

using Midi::File;

int main(__attribute__ ((unused)) int argc, __attribute__ ((unused)) char* argv[]) {
    File midi("test.mid");
    midi.writeToFile();
}
