    #include "Trains.h"

    Trains::Trains(Tracks* initTrack, Direction trainDirection): currentTrack(initTrack), trainDirection(trainDirection), trainStatus(MOVING) {}

    void Trains::addtrackRoute(Tracks* track) {
        trackRoute.push_back(track);
    }

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