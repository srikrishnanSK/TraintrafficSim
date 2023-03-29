    #include "Trains.h"
/**
 * @brief The train class constructor which takes the track at which the particular train object is going 
 *        to be initialized and additionally on what direction it needs to move. All the train objects
 *        are initialized with inital state to start moving.
 * @param   Tracks* initTrack, Direction trainDirection
 */
Trains::Trains(Tracks* initTrack, Direction trainDirection) : currentTrack(initTrack), trainDirection(trainDirection),trainStatus(MOVING) {}


/**
 * @brief The train class constructor which takes the track at which the particular train object is going 
 *        to be initialized and additionally on what direction it needs to move. All the train objects
 *        are initialized with inital state to start moving.
 * @param   Tracks* initTrack, Direction trainDirection
 * @return   Returns nothing. Reutrn type is void.
 */
void Trains::updateCurrenttrack(Tracks* track) {
   currentTrack = track;
   }

void Trains::advanceRouteIndex() {
   currentRouteIndex++;
}

void Trains::stop() {
   trainStatus = STOPPED;
   }

void Trains::move() {
   trainStatus = MOVING;
   }

Tracks* Trains::getCurrenttrack() const {
   return currentTrack;
   }

const std::vector<Tracks*>& Trains::gettrackRoute() const {
   return trackRoute;
   }

size_t Trains::getCurrentRouteIndex() const {
   return currentRouteIndex;
   }

Trains::Direction Trains::gettrainDirection() const {
   return trainDirection;
   }

void Trains::settrainDirection(Direction direction) {
   trainDirection = direction;
   }

Trains::Status Trains::gettrainStatus() const {
   return trainStatus;
   }

void Trains::settrackRoute(const std::vector<Tracks*>& trackRoute) {
   this->trackRoute = trackRoute;
   }

bool Trains::hastrainreachedDestination() const {
   return trainStatus == STOPPED || currentRouteIndex >= trackRoute.size();
   }