#ifndef SIGNALSYSTEM_H
#define SIGNALSYSTEM_H

#include "ConnecTracks.h"


class connecTracks;// Forward Decleration 

/**This class is responsible for handling the signals of the respective tracks*/
class tsSystem {

public:
    enum trainSignalstate { 
        GREEN = 0, 
        RED 
    };

    //Constrcutor and Destructor 
    tsSystem(connecTracks* connecTrain, trainSignalstate initState);
    ~tsSystem();
    
    //Setter and getter methods
    void setTrainstate(trainSignalstate state);
    trainSignalstate getTrainstate();

private:
    trainSignalstate currentTrainstate;
    connecTracks* connecTrack;
};

#endif