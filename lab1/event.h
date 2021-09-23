#ifndef EVENT_H
#define EVENT_H

class Event {
  public:
    enum EventType {
        ARRIVAL,
        OBSERVE
    };
    EventType type;
    double timestamp;
    double pktlen; //Only valid for arrival (ik bad coding)
    Event(EventType e, double t, double pktlen);
    bool operator< (const Event& e);
};

#endif
