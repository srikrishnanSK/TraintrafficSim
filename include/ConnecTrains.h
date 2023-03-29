#ifndef CONNECTRAINS_H
#define CONNECTRAINS_H

#include "Tracks.h"
#include "SignalSystem.h"

class Tracks;
class tsSystem;

class connecTrains {
public:
    enum trainConnectionType {
        DIRECT = 0, 
        JUNCTION, 
        TERMINATOR 
    };
    
    connecTrains(Tracks* parentTrack);
    void connectTrains(connecTrains* train, trainConnectionType type);
    connecTrains* getNextlink();
    Tracks* getParenttrack();
    trainConnectionType getTrainconType();
    void setTrainsignal(tsSystem* trainSsignal);
    bool trainhasSignal() const;
    tsSystem* getTrainSignal() const;
    double getTraindistanceTo(const connecTrains* train) const;

private:
    Tracks* parentTrack;
    connecTrains* nextLink;
    trainConnectionType trainType;
    tsSystem* trainSignal;
};

#endif