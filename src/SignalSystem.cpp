#include "SignalSystem.h"


tsSystem::tsSystem(connecTrains* connecTrain, trainSignalstate initState){
    this->connecTrain = connecTrain;
    this->currentTrainstate = initState;
}


void tsSystem::setTrainstate(trainSignalstate state) {
    currentTrainstate = state;
}

tsSystem::trainSignalstate tsSystem::getTrainstate() {
    return currentTrainstate;
}

connecTrains* tsSystem::getTrainconnectionpoint() const {
    return connecTrain;
}

