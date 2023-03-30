#include "Junction.h"

//Class Constructor
Junction::Junction(connecTracks* incoming, connecTracks* outgoingFirst, connecTracks* outgoingSecond) : incoming(incoming), outgoingFirst(outgoingFirst), outgoingSecond(outgoingSecond) {
   incoming->connectTrains(outgoingFirst, connecTracks::JUNCTION);
}

//Class Destructor
Junction::~Junction() {}


/**
 * @brief  The setTrainconnection method accepts the a connecTrack object which is to be connected from the entry junction to on junction track segment.
 *         This way a link can be established.
 * @param connecTracks* outgoing
 * @return Returns nothing. Reutrn type is void.
 */
void Junction::setTrainconnection(connecTracks* outgoing) {
   if(outgoing != nullptr) {
     incoming->connectTrains(outgoing, connecTracks::JUNCTION);
   }
}

/**
 * @brief  The getselectedConoutput method returns a connecTracks object that is linked to the entry Junction point.
 * @param  no arguments
 * @return Returns connecTracks object.
 */
connecTracks* Junction::getselectedConoutput() {
   return incoming->getNextlink();
}
