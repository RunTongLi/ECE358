#ifndef _PACKET_H_
#define _PACKET_H_

struct Packet {
    double arrival;
    double pktlen;
    double departure;
    Packet(double arrive, double len);
};

#endif
