#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <iostream>
#include <thread>
#include <chrono>
#include <vector>
#include <thread>
#include <mutex>
#include "Trains.h"
#include "Tracks.h"
#include "ConnecTracks.h"
#include "Junction.h"
#include "SignalSystem.h"
#include "RoutePlanner.h"

/** Simulator Class is the sole entity responsible for ensuring that all trains have routes laid out for them,
 * update train signals based on track availability, signal state, connections and ensure that the simulation
 * runs smoothly as expected with the provided Layout
*/
class Simulator {
private:
   //Vectors to hold track and train objects
   std::vector<Tracks*> tracks;
   std::vector<Trains*> trains;
   //Logic to handle train movement
   void moveTrain(Trains* train, connecTracks* nextPoint);
   void updateTrainsignals();
   std::mutex mtx;

public:
   //Constructor and Destructor
   Simulator();
   ~Simulator();
   //Methods to add Tracks, Trains, and Signals of the corresponding trains
   void addTracks(Tracks* track);
   void addTrain(Trains* train);
   void addTrainconnection(connecTracks* from, connecTracks* to, connecTracks::trainConnectionType type);
   void addTrainsignal(tsSystem* trainSignal, connecTracks* location);
   //Runs simulation and print the respective states of the trains
   void runSimulation();
   bool stepThroughsimulation();
   void printStateoftrains();
};

#endif