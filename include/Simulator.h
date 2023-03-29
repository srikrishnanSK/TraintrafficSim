#ifndef SIMULATOR_H
#define SIMULATOR_H

#include <vector>
#include <thread>
#include <mutex>
#include "Trains.h"
#include "Tracks.h"
#include "ConnecTracks.h"
#include "Junction.h"
#include "SignalSystem.h"
#include "RoutePlanner.h"

class Simulator {
public:
    Simulator();
    void addTracks(Tracks* track);
    void addTrainconnection(connecTracks* from, connecTracks* to, connecTracks::trainConnectionType type);
    void addTrainsignal(tsSystem* trainSignal, connecTracks* location);
    void addTrain(Trains* train);
    bool stepThroughsimulation();
    void printSimulationState();
    void runMultithreadedsim();

private:
    std::vector<Tracks*> tracks;
    std::vector<Trains*> trains;
    void moveTrain(Trains* train, connecTracks* nextPoint);
    void updateTrainsignals();
    std::mutex mtx;
};

#endif