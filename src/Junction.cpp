#include "Junction.h"

Trackjunction::Trackjunction(connecTrains* incoming, connecTrains* outgoingFirst, connecTrains* outgoingSecond) {
    this->incoming = incoming;
    this->outgoingFirst = outgoingFirst;
    this->outgoingSecond = outgoingSecond;
    incoming->connectTrains(outgoingFirst, connecTrains::JUNCTION);
}

void Trackjunction::setTrainconnection(connecTrains* outgoing) {
    incoming->connectTrains(outgoing, connecTrains::JUNCTION);
}

connecTrains* Trackjunction::getselectedConoutput() {
    return incoming->getNextlink();
}
