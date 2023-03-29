#include "Junction.h"

Junction::Junction(connecTracks* incoming, connecTracks* outgoingFirst, connecTracks* outgoingSecond) {
    this->incoming = incoming;
    this->outgoingFirst = outgoingFirst;
    this->outgoingSecond = outgoingSecond;
    incoming->connectTrains(outgoingFirst, connecTracks::JUNCTION);
}

void Junction::setTrainconnection(connecTracks* outgoing) {
    incoming->connectTrains(outgoing, connecTracks::JUNCTION);
}

connecTracks* Junction::getselectedConoutput() {
    return incoming->getNextlink();
}
