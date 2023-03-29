#ifndef SIGNALSYSTEM_H
#define SIGNALSYSTEM_H

#include "ConnecTrains.h"

/** Forward declaration of classes ConnectTracks*/
class connecTrains;

class tsSystem {
public:
    enum trainSignalstate { 
        GREEN = 0, 
        RED 
    };

    tsSystem(connecTrains* connecTrain, trainSignalstate initState);
    void setTrainstate(trainSignalstate state);
    trainSignalstate getTrainstate();
    connecTrains* getTrainconnectionpoint() const;


private:
    trainSignalstate currentTrainstate;
    connecTrains* connecTrain;
};

#endif