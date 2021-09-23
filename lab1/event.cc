#include "event.h"

Event::Event(Event::EventType e, double t, double l): type(e), timestamp(t), pktlen(l) {}

bool Event::operator< (const Event& e) {
    return timestamp < e.timestamp;
}
