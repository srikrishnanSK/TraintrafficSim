#include "Junction.h"

Junction::Junction(connecTracks* incoming, connecTracks* outgoingFirst, connecTracks* outgoingSecond) : incoming(incoming), outgoingFirst(outgoingFirst), outgoingSecond(outgoingSecond) {
    incoming->connectTrains(outgoingFirst, connecTracks::JUNCTION);
}

void Junction::setTrainconnection(connecTracks* outgoing) {
    incoming->connectTrains(outgoing, connecTracks::JUNCTION);
}

connecTracks* Junction::getselectedConoutput() {
    return incoming->getNextlink();
}
