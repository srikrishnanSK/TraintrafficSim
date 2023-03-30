    #include "Trains.h"

//Class Constructor
Trains::Trains(Tracks* initTrack, Direction trainDirection) : currentTrack(initTrack), trainDirection(trainDirection),trainStatus(MOVING) {}

//Class Destructor
Trains::~Trains(){}

/**
 * @brief  The updateCurrenttrack method accepts a track object as Input , which on passing the validation is assigned to the class variable accordingly.
 * @param  Tracks* track
 * @return Returns nothing. return type is void.
 */
void Trains::updateCurrenttrack(Tracks* track) {
   if(track != nullptr) {
         currentTrack = track;
     }
   }

/**
 * @brief  The advanceRouteIndex method is used to increment the currentRouteIndex variablle accordingly based on the total routes available 
 *         which is calculated in the RoutePlanner class.
 * @param  no arguments
 * @return Returns nothing. return type is void.
 */
void Trains::advanceRouteIndex() {
   currentRouteIndex++;
}

/**
 * @brief  The stop method is utilized to update the status of the respective train associated with it.
 * @param  no arguments
 * @return Returns nothing. return type is void.
 */
void Trains::stop() {
   trainStatus = STOPPED;
   }

/**
 * @brief  The getCurrenttrack method is used to return the current track object associated with the train accordingly.
 * @param  no arguments
 * @return Returns currenttrack object of type trains*.
 */
Tracks* Trains::getCurrenttrack() const {
   return currentTrack;
   }

/**
 * @brief  The gettrackRoute method is used to return the associated trackRoute laid out for the train object.
 * @param  no arguments
 * @return Returns vector of object Tracks*.
 */
const std::vector<Tracks*>& Trains::gettrackRoute() const {
   return trackRoute;
   }

/**
 * @brief  The getCurrentRouteIndex method is used to return the associated index with respect to the tracks
 * @param  no arguments
 * @return Returns index of unsigned integer type.
 */
unsigned int Trains::getCurrentRouteIndex() const {
   return currentRouteIndex;
   }

/**
 * @brief  The gettrainDirection method is used to return the associated trains direction.
 * @param  no arguments
 * @return Returns trainDirection of appropriate enum value.
 */
Trains::Direction Trains::gettrainDirection() const {
   return trainDirection;
   }

/**
 * @brief  The settrainDirection method is used to set the associated Trains direction accoringly
 * @param  Direction direction
 * @return Returns nothing. Return type is void.
 */
void Trains::settrainDirection(Direction direction) {
   trainDirection = direction;
   }

/**
 * @brief  The gettrainStatus method is used to return the associated trains status.
 * @param  no arguments
 * @return Returns trainStatus of approtiate Status enum.
 */
Trains::Status Trains::gettrainStatus() const {
   return trainStatus;
   }

/**
 * @brief  The settrackRoute method is used to set the associated trackroute for the tied up train object.
 * @param  const std::vector<Tracks*>& trackRoute
 * @return Returns nothing. Return type is void.
 */
void Trains::settrackRoute(const std::vector<Tracks*>& trackRoute) {
   this->trackRoute = trackRoute;
   }

/**
 * @brief  The hastrainreachedDestination method returns ture if the train has stopped or if the index is greater indicating it has no more tracks to move forward.
 * @param  no arguments
 * @return Returns bool.
 */
bool Trains::hastrainreachedDestination() const {
   return trainStatus == STOPPED || currentRouteIndex >= trackRoute.size();
   }