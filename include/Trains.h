#ifndef TRAINS_H
#define TRAINS_H

#include <vector>
#include "Tracks.h"

class Tracks;//Forward Decleration

/** The Train class is responsible for updating index and tracksegments for the train to move approproately. Additionally,
 *  it is also utilized for setting the trains direction, routes, and also obtain other related status information to update
 *  movement accordingly in the Simulator class.
*/

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
    
    //Constructor and Destructor
    Trains(Tracks* initTrack, Direction trainDirection = FORWARD);
    ~Trains();
    //All essential operations related to the Trains
    void stop();
    void updateCurrenttrack(Tracks* track);
    void advanceRouteIndex();
    void settrainDirection(Direction newDirection);
    void settrackRoute(const std::vector<Tracks*>& route);
    unsigned int getCurrentRouteIndex() const;
    bool hastrainreachedDestination() const;
    Tracks* getCurrenttrack() const;
    Direction gettrainDirection() const;
    Status gettrainStatus() const;
    const std::vector<Tracks*>& gettrackRoute() const;


private:
    Tracks* currentTrack;
    unsigned int currentRouteIndex;
    Direction trainDirection;
    Status trainStatus;
    std::vector<Tracks*> trackRoute;
};
#endif