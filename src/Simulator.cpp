#include "Simulator.h"

//Class Constructor
Simulator::Simulator() {}

//Class Destructor
Simulator::~Simulator() {}

/**
 * @brief  The addTrain method adds train objects into a vector if the provided object is NULL.
 *         This method is called from main.cpp once all the trains have been initialized .
 * @param  Trains* train
 * @return Returns nothing. Reutrn type is void.
 */
void Simulator::addTrain(Trains* train) {
    if(train != nullptr) {
        trains.push_back(train);
    }
}

/**
 * @brief  The addTracks method adds track objects into a vector if the provided object is NULL.
 *         This method is called from main.cpp once all the tracks  have been initialized and their
 *         respective connections have been made.
 * @param  Tracks* track
 * @return Returns nothing. Reutrn type is void.
 */
void Simulator::addTracks(Tracks* track) {
    if(track != nullptr ) {
        tracks.push_back(track);
    }
}

/**
 * @brief  The addTrainconnection is used to make connections between the track segments. This method
 *         is called from main.cpp once the track objects have been initialized with their names and 
 *         lengths. The endpoint connection of current track is passed as 1st argument, the startpoint
 *         connection of the pottential next track is added as the 2nd argument and types of track 
 *         connection being DIRECT or TERMINATOR or JUNCTION is configured accordingly. This in turn
 *         if not NULL is used to make an actual link between the curren track object and the next link
 *         object from the ConnecTracks class.
 *         respective connections have been made.
 * @param  Tracks* track
 * @return connecTracks* from, connecTracks* to, connecTracks::trainConnectionType type.
 */
void Simulator::addTrainconnection(connecTracks* from, connecTracks* to, connecTracks::trainConnectionType type) {
    if(from != nullptr && to != nullptr) {
        from->connectTrains(to, type);
    }
}

/**
 * @brief  The addTrainsignal method is used as a connection point to place signals at the end of each respective track.
 *         It takes signal object as first argument and the tracks end connections as a 2nd arument where the signal is to
 *         be placed. If the provided track connection is not null the tracks particular signal is linked to it with initial
 *         state as GREEN done from main.cpp.
 * @param  tsSystem* trainSignal, connecTracks* location
 * @return Returns nothing. Reutrn type is void.
 */
void Simulator::addTrainsignal(tsSystem* trainSignal, connecTracks* location) {
    if(location != nullptr && trainSignal != nullptr) {
        location->setTrainsignal(trainSignal);
    }
}

/**
 * @brief  This is the core function which is used to run the simulation. Once all the reauired initial configurations are complete
 *         this method is called form main.cpp. Initially passes the added Train and Track objects to RoutPlanner class for creating
 *         routes for trains and setting the routes that have been configured for each trains respectively. These routes are then printed 
 *         on the console using the method from RoutPlanner Class printTrainroutes. After this stage we move onto the initialize the
 *         Simulation. For every Train objects present we create a thread using lambda function witth this pointer (current classes object)
 *         and train object as capture list. The logic ensures to verify if the train has reach the destination continously for each train.
 *         Until destination is reached we setthrough the simulation by updating required signals and moving the trains accordingly.
 * @param  no arguments
 * @return Returns nothing. Reutrn type is void.
 */

void Simulator::runSimulation() {

   std::cout << "Configuring Routes for Trains" << std::endl;
   //Initialize RoutePlanner class with its respective objects
   RoutePlanner planner(tracks, trains);

    //Plan routes
    for (Trains* train : trains) {
        std::vector<Tracks*> trainRoute = planner.planRoutesfortrains(train);
        train->settrackRoute(trainRoute);
    }

    //Print configured routes
    planner.printTrainroutes();
    std::cout << "Initializing Simulation now........" << std::endl;

    //Run simulation
    for (Trains* train : trains) {
        std::thread sim([this, train]() {
            while (!train->hastrainreachedDestination()) {
                {
                    //Ensuring that only ine thread can access the shared resource at a time
                    std::unique_lock<std::mutex> lock(mtx);
                    stepThroughsimulation();
                }
                //Adding delay
                std::this_thread::sleep_for(std::chrono::seconds(1));
            }
        });
        //Waiting for threads to finish
        sim.join();
    }
}

/**
 * @brief  The updateTrainsignals method is responsible for updating the respective trains signal based on the current situation.
 *         For every train object it checks there is an endconnections for the curren track and obtains the current signal informatiion
 *         of that train in track if it exists. The trains next track and previous track info is obtained and analyzed to see if there is 
 *         another train in the track. if there is the signal of the current train is made RED , else we verify the direction, track, status,
 *         train has not stopped, ensure there is next track for the train to move, and matches as the next track according to the laid out plan.
 *         The Signal is set appropriately based on the boolean flag. 
 * @param  no arguments
 * @return Returns nothing. Reutrn type is void.
 */
void Simulator::updateTrainsignals() {
    // Check if sgnal exisis in the end of the track and verify if the next track is not empty
    for (auto& track : tracks) {
        connecTracks* endConnection = track->getTrackendConnection();
        if (endConnection != nullptr && endConnection->trainhasSignal()) {
            tsSystem* currentTrainsignal = endConnection->getTrainSignal();
            connecTracks* nextConnection = endConnection->getNextlink();
            if (nextConnection != nullptr && currentTrainsignal != nullptr) {
                Tracks* nextTrack = nextConnection->getParenttrack();
                bool trainInNexttrack = false;
                for (auto& train : trains) {
                    if (train->getCurrenttrack() == nextTrack) {
                        trainInNexttrack = true;
                        break;
                    }
                }

                //If not present do not move, else move accordinly if all the conditions are satisfied
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
                if(currentTrainsignal != nullptr) {
                   currentTrainsignal->setTrainstate(tsSystem::RED);
                }
            }
        }
    }
}

/**
 * @brief  The moveTrain method  get the next track connection linked/present along with the parenttrack information while adating its respective
 *         information  and advancing the routeIndex value with advanceRouteIndex() method from the Train class. If signal is present and is a junction
 *         the trains direction is updated accordingly and only if required. If the train has reached its EOL the trains movement is stopped bby changing
 *         its status to STOPPED, else the index is incremented and the current route information is also updated.
 * @param  Trains* train, connecTracks* nextPoint
 * @return Returns nothing. Reutrn type is void.
 */

void Simulator::moveTrain(Trains* train, connecTracks* nextPoint) {

    if(train != nullptr && nextPoint != nullptr) {
        connecTracks* nextConnection = nextPoint->getNextlink();
        if (nextConnection != nullptr) {
            Tracks* nextTrack = nextConnection->getParenttrack();
            train->updateCurrenttrack(nextTrack);
            train->advanceRouteIndex();

            // Update the train's direction if necessary
            if (nextPoint->trainhasSignal() && nextPoint->getTrainconType() == connecTracks::JUNCTION) {
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
}

/**
 * @brief  The stepThroughsimulation method is another core functionality which is used to run the provided simulation. After the respective
 *         signals have been updated by the updateTrainsignals() method the status for each trains from the provided vectors are obtained and 
 *         verified to see it can move forward or not. The current tracks end point information is obtained based on the direction on whether 
 *         it has to move forward or backward accordingly. The obtained connection is then verified to see if it can move further. After all 
 *         the required verification is passed the respective arguments are passed to the movetrain
 *         method for it to do the necessary actions.
 * @param  no arguments
 * @return Returns nothing. Reutrn type is void.
 */

bool Simulator::stepThroughsimulation() {
    bool allTrainsStopped = true;
    connecTracks* nextPoint = nullptr;
    //Update signals
    updateTrainsignals();

    for (Trains* train : trains) {
        if (train->gettrainStatus() == Trains::STOPPED) {
            continue;
        }
        
        //Verify before moving
        allTrainsStopped = false;
        Tracks* currentTrack = train->getCurrenttrack();
        if(currentTrack != nullptr) {
           nextPoint = (train->gettrainDirection() == Trains::FORWARD) ? currentTrack->getTrackendConnection() : currentTrack->getTrackstartConnection();
        }

        if (nextPoint != nullptr && nextPoint->trainhasSignal() && nextPoint->getTrainSignal()->getTrainstate() == tsSystem::RED) {
            if (train->getCurrentRouteIndex() + 1 < train->gettrackRoute().size() && train->gettrackRoute()[train->getCurrentRouteIndex() + 1] != nextPoint->getParenttrack()) {
                continue;
            }
        }
        
        //Move accordingly
        moveTrain(train, nextPoint);
    }

    //Print the current state
    printStateoftrains();
    return allTrainsStopped;
}


/**
 * @brief  The printStateoftrains is a simple method utilized to view the simulation on console. This provides the Train information and its respective states
 * @param  no arguments
 * @return Returns nothing. Reutrn type is void.
 */

void Simulator::printStateoftrains() {
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

