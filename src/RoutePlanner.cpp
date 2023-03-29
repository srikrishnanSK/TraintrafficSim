#include "RoutePlanner.h"
#include <iostream>
#include <limits>

RoutePlanner::RoutePlanner(const std::vector<Tracks*>& tracks, const std::vector<Trains*>& trains): tracks(tracks), trains(trains) {}

std::vector<Tracks*> RoutePlanner::planRoutesfortrains(Trains* train) {
    std::vector<Tracks*> trainRoute;
    Tracks* currentTrack = train->getCurrenttrack();
    while (currentTrack != nullptr) {
        trainRoute.push_back(currentTrack);
        Tracks* nextTrack = getNexttrack(currentTrack, train);
        currentTrack = nextTrack;
    }
    return trainRoute;
}

Tracks* RoutePlanner::getNexttrack(Tracks* currentTrack, Trains* train) {
    double minDistance = std::numeric_limits<double>::max();
    Tracks* nextTrack = nullptr;

    for (Tracks* track : tracks) {
        if (track == currentTrack) {
            continue;
        }

        connecTracks* trackStartpoint = currentTrack->getTrackendConnection();
        connecTracks* trackEndpoint = track->getTrackstartConnection();
        connecTracks* trackPrevendpoint = train->getCurrentRouteIndex() > 0 ? train->gettrackRoute()[train->getCurrentRouteIndex() - 1]->getTrackstartConnection() : nullptr;

        if (trackStartpoint->getNextlink() == trackEndpoint && trackEndpoint != trackPrevendpoint) {
            double distance = trackStartpoint->getTraindistanceTo(trackEndpoint);
            if (distance < minDistance) {
                minDistance = distance;
                nextTrack = track;
            }
        }
    }

    return nextTrack;
}

void RoutePlanner::printStats() const {
    std::cout << "Route planner results:" << std::endl;
    int trainId = 0;
    for (const Trains* train : trains) {
        std::cout << "Train " << trainId << " route:";
        for (Tracks* track : train->gettrackRoute()) {
            std::cout << " " << track->getTrackname();
        }
        std::cout << std::endl;
        trainId++;
    }
    std::cout << "----------------------" << std::endl;
}
