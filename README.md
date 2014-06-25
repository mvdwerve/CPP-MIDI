CPP-MIDI
==========

Introduction
----
CPP-MIDI is a very incomplete library for handling MIDI files, and is not released or even alpha yet.

Unimplemented:
- File reading
- Events (Notes, SysEx messages, MetaEvents)

Implemented:
- Header and track info writing


Build
----
Building is very simple. The Makefile will create a static library in the lib/ directory.


Example
----
```
#include <cppmidi/file.h>

int main(int argc, char *argv[]) {
    Midi::File file("name.mid");
    file.writeToFile();
}
```
