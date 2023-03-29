#include "ConnecTrains.h"

connecTrains::connecTrains(Tracks* parentTrack) {

   this->parentTrack = parentTrack;
   this->nextLink = nullptr;
   this->trainSignal = nullptr;
   this->trainType = TERMINATOR;
}

void connecTrains::connectTrains(connecTrains* train, trainConnectionType type) {
    this->nextLink = train;
    this->trainType = type;
}

connecTrains* connecTrains::getNextlink() {
    return nextLink;
}

Tracks* connecTrains::getParenttrack() {
    return parentTrack;
}

connecTrains::trainConnectionType connecTrains::getTrainconType() {
    return trainType;
}

void connecTrains::setTrainsignal(tsSystem* trainSignal) {
    this->trainSignal = trainSignal;
}

bool connecTrains::trainhasSignal() const {
    return trainSignal != nullptr;
}

tsSystem* connecTrains::getTrainSignal() const {
    return trainSignal;
}

double connecTrains::getTraindistanceTo(const connecTrains* train) const {
    if (train == nullptr) {
        return 0;
    }

    double distance = 0;
    connecTrains* currentCon = const_cast<connecTrains*>(this);
    while (currentCon != nullptr && currentCon != train) {
        Tracks* track = currentCon->getParenttrack();
        distance += track->getTracklength();
        currentCon = currentCon->getNextlink();
    }

    return distance;
}
