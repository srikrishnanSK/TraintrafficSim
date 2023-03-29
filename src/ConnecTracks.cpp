#include "ConnecTracks.h"

connecTracks::connecTracks(Tracks* parentTrack): parentTrack(parentTrack), nextLink(nullptr), trainSignal(nullptr),trainType(TERMINATOR) {}

void connecTracks::connectTrains(connecTracks* train, trainConnectionType type) {
    this->nextLink = train;
    this->trainType = type;
}

connecTracks* connecTracks::getNextlink() {
    return nextLink;
}

Tracks* connecTracks::getParenttrack() {
    return parentTrack;
}

connecTracks::trainConnectionType connecTracks::getTrainconType() {
    return trainType;
}

void connecTracks::setTrainsignal(tsSystem* trainSignal) {
    this->trainSignal = trainSignal;
}

bool connecTracks::trainhasSignal() const {
    return trainSignal != nullptr;
}

tsSystem* connecTracks::getTrainSignal() const {
    return trainSignal;
}

double connecTracks::getTraindistanceTo(const connecTracks* train) const {
    if (train == nullptr) {
        return 0;
    }

    double distance = 0;
    connecTracks* currentCon = const_cast<connecTracks*>(this);
    while (currentCon != nullptr && currentCon != train) {
        Tracks* track = currentCon->getParenttrack();
        distance += track->getTracklength();
        currentCon = currentCon->getNextlink();
    }

    return distance;
}
