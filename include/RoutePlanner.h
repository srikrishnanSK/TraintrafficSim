#ifndef ROUTEPLANNER_H
#define ROUTEPLANNER_H

#include <iostream>
#include <vector>
#include <limits>
#include "Tracks.h"
#include "Trains.h"


/**The RoutePlanner class is another core class which aids in planning the routes of each provided train objects. Additionally it also helps choose the next segment in sequence
 * accordingly
*/
class RoutePlanner {
   private:
   //Get the next track in connection based on computation
   Tracks* getNexttrack(Tracks* currentTrack, Trains* train);
   const std::vector<Trains*>& trains;
   const std::vector<Tracks*>& tracks;

public:
   RoutePlanner(const std::vector<Tracks*>& tracks, const std::vector<Trains*>& trains);
   ~RoutePlanner();
   //Plan the routes based on the provided layout
   std::vector<Tracks*> planRoutesfortrains(Trains* train);
   void printTrainroutes() const;
};

#endif
