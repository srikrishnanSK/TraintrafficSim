#include "SignalSystem.h"


tsSystem::tsSystem(connecTracks* connecTrain, trainSignalstate initState){
    this->connecTrack = connecTrain;
    this->currentTrainstate = initState;
}


void tsSystem::setTrainstate(trainSignalstate state) {
    currentTrainstate = state;
}

tsSystem::trainSignalstate tsSystem::getTrainstate() {
    return currentTrainstate;
}

connecTracks* tsSystem::getTrackconnectionpoint() const {
    return connecTrack;
}

