#ifndef SIGNALSYSTEM_H
#define SIGNALSYSTEM_H

#include "ConnecTracks.h"

/** Forward declaration of classes ConnectTracks*/
class connecTracks;

class tsSystem {
public:
    enum trainSignalstate { 
        GREEN = 0, 
        RED 
    };

    tsSystem(connecTracks* connecTrain, trainSignalstate initState);
    void setTrainstate(trainSignalstate state);
    trainSignalstate getTrainstate();
    connecTracks* getTrackconnectionpoint() const;


private:
    trainSignalstate currentTrainstate;
    connecTracks* connecTrack;
};

#endif