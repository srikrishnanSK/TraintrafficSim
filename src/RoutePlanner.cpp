#include "RoutePlanner.h"


//Class Contructor
RoutePlanner::RoutePlanner(const std::vector<Tracks*>& tracks, const std::vector<Trains*>& trains): tracks(tracks), trains(trains) {}
//Class Destructor
RoutePlanner::~RoutePlanner(){}

/**
 * @brief  The planRoutesfortrains method takes a train object as input which is validated before obtaining the current track information.
 *         The obtaining track information if not NULL is pushed as a connection back into the vector before proceeding to called the getNexttrack
 *         method. This is performed until its laid out for all the trains. The returns nextTrack in line is also validated before added to the
 *         train route vector. The route planned all depends on the initial train position and track position they are placed on.
 * @param  Trains* train.
 * @return Returns std::vector<Tracks*>.
 */
std::vector<Tracks*> RoutePlanner::planRoutesfortrains(Trains* train) {
    std::vector<Tracks*> trainRoute;
    if(train != nullptr) {
        //get Current track info
        Tracks* currentTrack = train->getCurrenttrack();
        while (currentTrack != nullptr) {
            trainRoute.push_back(currentTrack);
            //Get the next track
            Tracks* nextTrack = getNexttrack(currentTrack, train);
            //Check
            if(nextTrack == nullptr) {
                break;
            }
            currentTrack = nextTrack;
        }
    }

    return trainRoute;
}

/**
 * @brief  The getNexttrack method called from the planRoutesfortrains method accepts the current track and train objects as input. The validated
 *         Inputes are then used to verify if the track is same as current track not to proceed further as EOL. If not we obtain the end point of the
 *         current track of which the train will exit, the start connection of the next track which the current train might enter potentially. It is also 
 *         validated to see if it has any other track segments it has left that can be provided based on the Index provided. The data is then further validated
 *         to see if the endpoint connection of the current track is equal to the startpoint connection of the next track, and additionally it also validates
 *         that previous is not the same as the candidate track to avoid circular motion. After which te distance is updated and nextTrack information is also 
 *         updated accordingly.The std::numeric_limits<int>::max() is used to assign the max interger value to minDistance variable which isused in simillar
 *         refernce to determine minimum number in a group of numbers.
 * @param  Tracks* currentTrack, Trains* train
 * @return Returns Tracks* object.
 */
Tracks* RoutePlanner::getNexttrack(Tracks* currentTrack, Trains* train) {
    int minDistance = std::numeric_limits<int>::max();
    Tracks* nextTrack = nullptr;
    if(currentTrack != nullptr && train != nullptr) {
        for (Tracks* track : tracks) {
            //Checks
            if (track == currentTrack) {
                continue;
            }

            //Get required information for validation
            connecTracks* trackStartpoint = currentTrack->getTrackendConnection();
            connecTracks* trackEndpoint = track->getTrackstartConnection();
            connecTracks* trackPrevendpoint = train->getCurrentRouteIndex() > 0 ? train->gettrackRoute()[train->getCurrentRouteIndex() - 1]->getTrackstartConnection() : nullptr;

            //Verify and update accordingly
            if (trackStartpoint->getNextlink() == trackEndpoint && trackEndpoint != trackPrevendpoint) {
                int distance = trackStartpoint->getTraindistanceTo(trackEndpoint);
                if (distance < minDistance) {
                    minDistance = distance;
                    nextTrack = track;
                }
            }
        }
    }

    return nextTrack;
}

/**
 * @brief  The printTrainroutes is a simple method used to print the planned routes for each train onto the console
 * @param  no arguments
 * @return Returns nothing. Reutrn type is void.
 */
void RoutePlanner::printTrainroutes() const {
    std::cout << "Routes are as follows:" << std::endl;
    int trainId = 0;
    for (const Trains* train : trains) {
        std::cout << "Train  number" << trainId << " route:";
        for (Tracks* track : train->gettrackRoute()) {
            std::cout << " " << track->getTrackname();
        }
        std::cout << std::endl;
        trainId++;
    }
    std::cout << "----------------------" << std::endl;
}
