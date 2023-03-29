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

    void addtrackRoute(Tracks* track);
    void updateCurrenttrack(Tracks* track);
    void advanceRouteIndex();
    void stop();
    void move();
    void settrainDirection(Direction newDirection);
    Tracks* getCurrenttrack() const;
    const std::vector<Tracks*>& gettrackRoute() const;
    size_t getCurrentRouteIndex() const;
    Direction gettrainDirection() const;
    Status gettrainStatus() const;
    void settrackRoute(const std::vector<Tracks*>& route);
    bool hastrainreachedDestination() const;


private:
    Tracks* currentTrack;
    std::vector<Tracks*> trackRoute;
    size_t currentRouteIndex;
    Direction trainDirection;
    Status trainStatus;
};
#endif