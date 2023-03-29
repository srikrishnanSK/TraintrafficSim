#include "SignalSystem.h"


tsSystem::tsSystem(connecTracks* connecTrack, trainSignalstate initState) : connecTrack(connecTrack),currentTrainstate(initState){}


void tsSystem::setTrainstate(trainSignalstate state) {
    currentTrainstate = state;
}

tsSystem::trainSignalstate tsSystem::getTrainstate() {
    return currentTrainstate;
}

connecTracks* tsSystem::getTrackconnectionpoint() const {
    return connecTrack;
}

