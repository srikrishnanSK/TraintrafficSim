#ifndef TRAINS_H
#define TRAINS_H

#include <vector>
#include "Tracks.h"

class Tracks;

class Trains {
public:
    enum Direction {
        FORWARD,
        REVERSE
    };

    enum Status {
        MOVING,
        STOPPED
    };

    Trains(Tracks* initTrack, Direction trainDirection = FORWARD);
    Tracks* getCurrenttrack() const;
    size_t getCurrentRouteIndex() const;
    Direction gettrainDirection() const;
    Status gettrainStatus() const;
    void stop();
    void move();
    void updateCurrenttrack(Tracks* track);
    void advanceRouteIndex();
    void settrainDirection(Direction newDirection);
    void settrackRoute(const std::vector<Tracks*>& route);
    const std::vector<Tracks*>& gettrackRoute() const;
    bool hastrainreachedDestination() const;


private:
    Tracks* currentTrack;
    size_t currentRouteIndex;
    Direction trainDirection;
    Status trainStatus;
    std::vector<Tracks*> trackRoute;
};
#endif