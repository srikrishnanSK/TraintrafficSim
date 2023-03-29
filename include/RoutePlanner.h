#ifndef ROUTEPLANNER_H
#define ROUTEPLANNER_H

#include "Tracks.h"
#include "Trains.h"
#include <vector>

class RoutePlanner {
    private:
    Tracks* getNexttrack(Tracks* currentTrack, Trains* train);
    const std::vector<Trains*>& trains;
    const std::vector<Tracks*>& tracks;

public:
    void printStats() const;
    std::vector<Tracks*> planRoutesfortrains(Trains* train);
    RoutePlanner(const std::vector<Tracks*>& tracks, const std::vector<Trains*>& trains);
};

#endif
