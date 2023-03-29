#ifndef CONNECTRAINS_H
#define CONNECTRAINS_H

#include "Tracks.h"
#include "SignalSystem.h"

class Tracks;
class tsSystem;

class connecTracks {
public:
    enum trainConnectionType {
        DIRECT = 0, 
        JUNCTION, 
        TERMINATOR 
    };
    
    connecTracks(Tracks* parentTrack);
    void connectTrains(connecTracks* train, trainConnectionType type);
    connecTracks* getNextlink();
    Tracks* getParenttrack();
    trainConnectionType getTrainconType();
    void setTrainsignal(tsSystem* trainSsignal);
    bool trainhasSignal() const;
    tsSystem* getTrainSignal() const;
    double getTraindistanceTo(const connecTracks* train) const;

private:
    Tracks* parentTrack;
    connecTracks* nextLink;
    trainConnectionType trainType;
    tsSystem* trainSignal;
};

#endif