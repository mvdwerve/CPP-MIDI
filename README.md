CPP-MIDI
==========

Introduction
----
CPP-MIDI is a very incomplete library for handling MIDI files, and is not released or even alpha yet.

Unimplemented:
- File reading
- Most events

Implemented:
- Header and track info and data writing
- Files recognized by music players
- Base event
- Stub message event

Build
----
Building is very simple. The Makefile will create a static library in the lib/ directory.

Inspect
----
The best way to inspect the generated midi files is by using the linux hexdump utility.
Command:
```
hexdump -C test.mid
```
This will display nicely formatted hex.

Example
----
```
#include <cppmidi/file.h>

int main(int argc, char *argv[]) {
    Midi::File file("name.mid");
    file.writeToFile();
}
```
