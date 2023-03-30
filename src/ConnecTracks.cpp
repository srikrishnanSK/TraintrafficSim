#include "ConnecTracks.h"

//Class Constructor
connecTracks::connecTracks(Tracks* parentTrack): parentTrack(parentTrack), nextLink(nullptr), trainSignal(nullptr),trainType(TERMINATOR) {}

//Class Destructor
connecTracks::~connecTracks() {}

/**
 * @brief  The connectTrains method called from the Simulator class is used to form links netween various track segment.
 *          The method checks if the provided track is not null and assigns it to class variables accordinly.
 * @param  connecTracks* track, trainConnectionType type
 * @return Returns nothing. Reutrn type is void.
 */
void connecTracks::connectTrains(connecTracks* track, trainConnectionType type) {
   if(track != nullptr) {
      this->nextLink = track;
   }
   this->trainType = type;
}

/**
 * @brief  The getNextlink method returns the next track (connecTrack object) in the provided link
 * @param  no arguments
 * @return Returns connecTracks object.
 */
connecTracks* connecTracks::getNextlink() {
   return nextLink;
}

/**
 * @brief  The getParenttrack method returns the parent track or previous (Track object and is also associalted with its respective connecTracks) 
 *         object in the provided link.
 * @param  no arguments
 * @return Returns Tracks object.
 */
Tracks* connecTracks::getParenttrack() {
   return parentTrack;
}

/**
 * @brief  The getTrainconType method is used to return a enum value indicatin which the track is DIRECT or JUNCTION or a TERMINATOR
 * @param  no arguments
 * @return Returns connecTracks object.
 */
connecTracks::trainConnectionType connecTracks::getTrainconType() {
   return trainType;
}

/**
 * @brief  The setTrainsignal method is used to set the singal object to the current classes signal object if the provided argument is not NULL.
 * @param  tsSystem* trainSignal
 * @return Returns nothing. Reutrn type is void.
 */
void connecTracks::setTrainsignal(tsSystem* trainSignal) {
   if(trainSignal != nullptr) {
      this->trainSignal = trainSignal;
   }
}

/**
 * @brief  The trainhasSignal return boolean value if the associalted signal object of the class exists. Const added so nothing is changed making
 *         it only readable.
 * @param  no arguments.
 * @return Returns boolean value.
 */
bool connecTracks::trainhasSignal() const {
   return trainSignal != nullptr;
}

/**
 * @brief  The getTrainSignal method returns a signal object as is.
 * @param  no arguments
 * @return Returns tsSystem object.
 */
tsSystem* connecTracks::getTrainSignal() const {
   return trainSignal;
}

/**
 * @brief  The getTraindistanceTo is used to compute the distance of the whole track route which is then used to
 *         determine the shortest path between the source and destination from RoutePlanner class. The const_cast<connecTracks*>(this) is 
 *         utilized to remove the const for the current class object thus allowing for any modification if required.
 * @param  const connecTracks* train
 * @return Returns interger value of calculated distance.
 */
int connecTracks::getTraindistanceTo(const connecTracks* train) const {
   if (train == nullptr) {
      return 0;
   }

   int distance = 0;
   connecTracks* currentCon = const_cast<connecTracks*>(this);
   while (currentCon != nullptr && currentCon != train) {
      Tracks* track = currentCon->getParenttrack();
      distance += track->getTracklength();
      currentCon = currentCon->getNextlink();
   }

   return distance;
}
