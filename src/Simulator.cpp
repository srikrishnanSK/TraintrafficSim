#include "Simulator.h"
#include "RoutePlanner.h"
#include <iostream>
#include <thread>
#include <chrono>

Simulator::Simulator() {

}

void Simulator::addTracks(Tracks* track) {
    tracks.push_back(track);
}

void Simulator::addTrainconnection(connecTrains* from, connecTrains* to, connecTrains::trainConnectionType type) {
    from->connectTrains(to, type);
}

void Simulator::addTrainsignal(tsSystem* trainSignal, connecTrains* location) {
    location->setTrainsignal(trainSignal);
}

void Simulator::addTrain(Trains* train) {
    trains.push_back(train);
}

bool Simulator::stepThroughsimulation() {
    bool allTrainsStopped = true;

    updateTrainsignals();

    for (Trains* train : trains) {
        if (train->gettrainStatus() == Trains::STOPPED) {
            continue;
        }

        allTrainsStopped = false;
        Tracks* currentTrack = train->getCurrenttrack();
        connecTrains* nextPoint = (train->gettrainDirection() == Trains::FORWARD) ? currentTrack->getTrackendConnection() : currentTrack->getTrackstartConnection();

        if (nextPoint->trainhasSignal() and nextPoint->getTrainSignal()->getTrainstate() == tsSystem::RED) {
            if (train->getCurrentRouteIndex() + 1 < train->gettrackRoute().size() && train->gettrackRoute()[train->getCurrentRouteIndex() + 1] != nextPoint->getParenttrack()) {
                continue;
            }
        }

        moveTrain(train, nextPoint);
    }

    printSimulationState();
    return allTrainsStopped;
}




void Simulator::runMultithreadedsim() {
    std::cout << "Running the multithreaded simulation..." << std::endl;
    RoutePlanner planner(tracks, trains);

    for (Trains* train : trains) {
        std::vector<Tracks*> trainRoute = planner.planRoutesfortrains(train);
        train->settrackRoute(trainRoute);
    }

    planner.printStats();
    std::cout << "Simulation started." << std::endl;

    for (Trains* train : trains) {
        std::thread t([this, train]() {
            while (!train->hastrainreachedDestination()) {
                {
                    std::unique_lock<std::mutex> lock(mtx);
                    stepThroughsimulation();
                }
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        });
        t.detach(); // detach the thread to run independently
    }
}





void Simulator::printSimulationState() {
    std::cout << "\nCurrent simulation state:\n";
    int trainId = 0;
    for (Trains* train : trains) {
        std::cout << "Train " << trainId << ": ";
        std::cout << "Route: ";
        for (const auto& track : train->gettrackRoute()) {
            std::cout << track->getTrackname() << " ";
        }
        std::cout << "\n";
        std::cout << "Current Position: " << train->gettrackRoute()[train->getCurrentRouteIndex()]->getTrackname();
        if (train->gettrainStatus() == Trains::STOPPED) {
            std::cout << " (stopped)";
        }
        std::cout << std::endl;
        trainId++;
    }
    std::cout << "-------------------------\n";
}


void Simulator::moveTrain(Trains* train, connecTrains* nextPoint) {
    connecTrains* nextConnection = nextPoint->getNextlink();
    if (nextConnection != nullptr) {
        Tracks* nextTrack = nextConnection->getParenttrack();
        train->updateCurrenttrack(nextTrack);
        train->advanceRouteIndex();

        // Update the train's direction if necessary
        if (nextPoint->trainhasSignal() && nextPoint->getTrainconType() == connecTrains::JUNCTION) {
            if (train->gettrainDirection() == Trains::FORWARD) {
                train->settrainDirection(Trains::REVERSE);
            } else {
                train->settrainDirection(Trains::FORWARD);
            }
        }
    } else {
        // If the train has reached the end of its route, stop the train
        if (train->getCurrentRouteIndex() + 1 >= train->gettrackRoute().size()) {
            train->stop();
        } else {
            // If the train hasn't reached the end of its route, move it to the next track
            train->advanceRouteIndex();
            train->updateCurrenttrack(train->gettrackRoute()[train->getCurrentRouteIndex()]);
        }
    }
}


void Simulator::updateTrainsignals() {
    for (auto& track : tracks) {
        connecTrains* endConnection = track->getTrackendConnection();
        if (endConnection->trainhasSignal()) {
            tsSystem* currentTrainsignal = endConnection->getTrainSignal();
            connecTrains* nextConnection = endConnection->getNextlink();
            if (nextConnection) {
                Tracks* nextTrack = nextConnection->getParenttrack();
                bool trainInNexttrack = false;
                for (auto& train : trains) {
                    if (train->getCurrenttrack() == nextTrack) {
                        trainInNexttrack = true;
                        break;
                    }
                }

                if (trainInNexttrack) {
                    currentTrainsignal->setTrainstate(tsSystem::RED);
                } else {
                    bool trainApproaching = false;
                    for (auto& train : trains) {
                        if (train->gettrainDirection() == Trains::FORWARD &&
                            train->getCurrenttrack() == track &&
                            train->gettrainStatus() != Trains::STOPPED &&
                            train->getCurrentRouteIndex() + 1 < train->gettrackRoute().size() &&
                            train->gettrackRoute()[train->getCurrentRouteIndex() + 1] == nextTrack) {
                            trainApproaching = true;
                            break;
                        }
                    }
                    currentTrainsignal->setTrainstate(trainApproaching ? tsSystem::GREEN : tsSystem::RED);
                }
            } else {
                currentTrainsignal->setTrainstate(tsSystem::RED);
            }
        }
    }
}
