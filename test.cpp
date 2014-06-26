#include <cppmidi/file.h>
#include <cppmidi/events/message.h>
#include <cppmidi/event.h>
#include <cppmidi/track.h>
#include <vector>

using Midi::File;
using Midi::Track;
using Midi::Event;
using Midi::Events::Message;

int main(__attribute__ ((unused)) int argc, __attribute__ ((unused)) char* argv[]) {
    /* This is here because we have to clean up. */
    std::vector<Event*> events;

    /* Loading the basic midi object with a filename of test.mid */
    File midi("test.mid");
    Track *t = new Track();

    Event* tmp;

    /* Creating 16 messages to put in the midi. */
    for (int i = 0; i < 16; i++) {
        tmp = new Message();
        t->addEvent(tmp);
        events.push_back(tmp);
    }

    midi.addTrack(t);
    midi.writeToFile();

    for (auto event : events)
        delete event;
}
