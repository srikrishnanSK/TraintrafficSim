#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>
#include <thread>
#include <mutex>
#include "Trains.h"
#include "Tracks.h"
#include "ConnecTrains.h"
#include "Junction.h"
#include "SignalSystem.h"
#include "RoutePlanner.h"

class Simulator {
public:
    Simulator();
    void addTracks(Tracks* track);
    void addTrainconnection(connecTrains* from, connecTrains* to, connecTrains::trainConnectionType type);
    void addTrainsignal(tsSystem* trainSignal, connecTrains* location);
    void addTrain(Trains* train);
    bool stepThroughsimulation();
    void printSimulationState();
    void runMultithreadedsim();

private:
    std::vector<Tracks*> tracks;
    std::vector<Trains*> trains;
    void moveTrain(Trains* train, connecTrains* nextPoint);
    void updateTrainsignals();
    std::mutex mtx;
};

#endif