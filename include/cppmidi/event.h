#ifndef MIDI_EVENT_h
#define MIDI_EVENT_h

#include <iostream>
#include <vector>

namespace Midi {
    class Event {
    public:
        virtual std::ostream& print(std::ostream& output) const = 0;

        friend std::ostream& operator <<(std::ostream& output, const Event& t) {
            return t.print(output);
        }

        uint8_t getChannel() { return _channel; }
        uint8_t getLength() { return _length;  }
    protected:
        uint8_t _channel;
        uint64_t _length;
    };
}

#endif
