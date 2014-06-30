/**
 * track.h
 *
 * Class for maintaining and easily writing the MIDI track data.
 *
 * @author Michael van der Werve
 */

#ifndef MIDI_TRACK_h
#define MIDI_TRACK_h

#include <iostream>
#include <vector>
#include <cppmidi/event.h>

/**
 * Setting up the midi namespace
 */
namespace Midi {
    class Track {
        public:
            /**
             * Identifier for midi tracks, which is basically "MTrk".
             * @var const static char*
             */
            const static char* IDENTIFIER;

            /**
             * Destructor, frees up all the copied pointers.
             */
            virtual ~Track() {
                for (auto event : _events)
                    delete event;
            }

            /**
             * Stream operator so the track info can be written to any output.
             * @param output Output stream
             * @param t      Track to be written to the output
             * @return std::ostream& Original output stream.
             */
            friend std::ostream& operator <<(std::ostream& output, const Track& t);

            /**
             * Method to read the track object from an input stream. The stream should
             * be in binary mode.
             * @param input The input stream.
             * @param track The track object.
             * @return std::istream& THe original input stream.
             */
            friend std::istream& operator >>(std::istream& input, Track& track);


            /**
             * Method to add an event to the internal events. This will simply clone the
             * event and use the internal addEvent function.
             * @param   e   The event to be added.
             */
            bool addEvent(const Event& e) {
                return addEvent(e.clone());
            }

        private:

            /**
             * Method to add an event to the internal events. This should not be used by
             * anybody but this class or friends itself, since it will assume a dynamically
             * allocated variable.
             * @param   e   The event to be added.
             * @todo Check the length.
             */
            bool addEvent(Event* e) {
                _length += e->getLength();
                _events.push_back(e);

                return true;
            }

            /**
             * Integer to keep track of the track length, which is a maximum of 4 bytes.
             * @var uint32_t
             */
            uint32_t _length;

            /**
             * Vector to keep track of all the events for this midi so they can be printed.
             * @var std::vector<Event*>
             */
            std::vector<Event*> _events;
    };
}

#endif
