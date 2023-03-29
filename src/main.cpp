#include <iostream>
#include <map>
#include <chrono>
#include <thread>
#include "Simulator.h"
#include "Tracks.h"
#include "Trains.h"
#include "SignalSystem.h"
#include "Junction.h"

/** Initial Layout
 * A->B->C->Junction->D
 *        |      |
 *        L      F->G->H->Junction->I
 *        |                 |
 *        J                 E 
*/

/** Map Initialization for Tracks comprising of Names of each track as key and their respective lengths as value*/
static std::map<const std::string, double> trackInitializationInfo = {{"A",100},{"B",200},{"C",150},{"D",300},{"E",250},{"F",350},{"G",400},{"H",100},{"I",300},{"J",350},};
/**Map Initialization for Type of Connection a track is going to have with Track index as key and Connection type as their values*/
static std::map<int,connecTrains::trainConnectionType> connectionType = {{0,connecTrains::DIRECT},{1,connecTrains::DIRECT},{2,connecTrains::JUNCTION},{3,connecTrains::TERMINATOR},{4,connecTrains::JUNCTION},{5,connecTrains::DIRECT},{6,connecTrains::DIRECT},{7,connecTrains::JUNCTION},{8,connecTrains::TERMINATOR},{9,connecTrains::JUNCTION},};
/** Map Initialization for Trains in which direction will they move. It has Train number as the Key and FORWARD or REVERSE as its respective value*/
static std::map<int,Trains::Direction> trainDirection = {{0,Trains::FORWARD},{1,Trains::REVERSE},{2,Trains::FORWARD},{3,Trains::REVERSE},{4,Trains::FORWARD},{5,Trains::REVERSE},};
/** Constant value defining total number of Signals to be in place along the Tracks*/
static const unsigned totalSignals = 4; 
/**Initializes different Tracks class object equal to the size of trackInitializationInfo and stores in the vector */
static int initializeTracks(std::vector<Tracks*>&tracks);
/**Initializes different Trains class object with their initial starting points and the direction in which they will move forward */
static int initializeTrains(std::vector<Trains*>&trains,std::vector<Tracks*>&tracks);
/**Initializes different Trains Signal system class objects with tracks end connection point with their respective initial train signal initial states*/
static int initializeSignals(Simulator *simulation,std::vector<tsSystem *>&signals,std::vector<Tracks*>&tracks);
/**Connect various Tracks and add it to the Simulator class*/
static int makeConnections(Simulator *simulation, std::vector<Tracks*>&tracks);

int main() {

    /**Initialte Simulate class*/
    Simulator tsSimulation;

    std::vector<Tracks *> tracks;
    std::vector<Trains *> trains;
    std::vector<tsSystem *> signals;

    /**Init parameters */
    initializeTracks(tracks);
    initializeTrains(trains,tracks);
    initializeSignals(&tsSimulation,signals,tracks);
    /**make track connections*/
    makeConnections(&tsSimulation,tracks);

    /**Add the respective tracks and train objects to the Simulator class*/
    for(auto &track : tracks) {
        tsSimulation.addTracks(track);
    }

    for (auto &train : trains) {
        tsSimulation.addTrain(train);
    }
    
    /**Initate multithreaded Simulation*/
    tsSimulation.runMultithreadedsim();
    /** Let the Simulation stay on console until user ends it*/
    std::cin.get();
    std::cout << "Simulation has Ended" << std::endl;

    /** Clean up all the created objects for Tracks, Trains and clear the vectors*/
    for(auto &trackObj : tracks) {
        delete trackObj;
    }
    
    for(auto &trainObj : trains) {
        delete trainObj;
    }
    
    for(auto &signalObj : signals) {
        delete signalObj;
    }

    /**Clear vectors*/
    tracks.clear();
    trains.clear();
    signals.clear();
    return 0;
}

/**
 * @brief The below function initializes tracks based on the provided map with Track name as key and value as the tracks arbitary lenth. It created track
 *        objects with required constructor arhuments and pushes it back into the vector
 * @param   std::vector<Tracks*>&tracks
 * @return   returns 0 on success.
 */
static int initializeTracks(std::vector<Tracks*>&tracks) {

   for(auto it = trackInitializationInfo.begin(); it != trackInitializationInfo.end(); it ++) {
      try{
         tracks.emplace_back(new Tracks(it->second, it->first));
       } catch (const std::exception& e) {
           std::cout<<"Expecption caught!!!, unable to add the object"<<e.what()<<std::endl;
        }
   }
   return 0;
}

/**
 * @brief The below function initializes trains movement from a particular track. A Train
 *        objects with required constructor arhuments and pushes it back into the vector. Try
 *        and catch has been added for better expception handling while using emplace_back() method.
 *        emplace_back() avoid creating another temporary objecting which can be copied/pushed back 
 *        into the vector provided
 * @param   std::vector<Trains*>&trains,std::vector<Tracks*>&tracks
 * @return   returns 0 on success.
 */

static int initializeTrains(std::vector<Trains*>&trains,std::vector<Tracks*>&tracks) {
   for(unsigned int trainIndex= 0 ; trainIndex < trainDirection.size(); trainIndex++) {
       if(trainIndex == 0 || trainIndex == 2) {
           try{
               trains.emplace_back(new Trains(tracks[0],trainDirection.at(trainIndex)));
           }catch(const std::exception& e) {
               std::cout<<"Expecption caught!!!, unable to add the object"<<e.what()<<std::endl;
           }
       } else if(trainIndex == 1) {
           try{
               trains.emplace_back(new Trains(tracks[2],trainDirection.at(trainIndex)));
           }catch(const std::exception& e) {
               std::cout<<"Expecption caught!!!, unable to add the object"<<e.what()<<std::endl;
           }
       }else if( trainIndex == 3) {
           try{
              trains.emplace_back(new Trains(tracks[1],trainDirection.at(trainIndex)));
           }catch(const std::exception& e) {
               std::cout<<"Expecption caught!!!, unable to add the object"<<e.what()<<std::endl;
           }
       } else if(trainIndex == 4) {
           try{
             trains.emplace_back(new Trains(tracks[6],trainDirection.at(trainIndex)));
           }catch(const std::exception& e) {
               std::cout<<"Expecption caught!!!, unable to add the object"<<e.what()<<std::endl;
           }
       } else if (trainIndex == 5) {
           try{
              trains.emplace_back(new Trains(tracks[5],trainDirection.at(trainIndex)));
           }catch(const std::exception& e) {
               std::cout<<"Expecption caught!!!, unable to add the object"<<e.what()<<std::endl;
           }
       }
   }
   return 0;
}

/**
 * @brief The below function initializes signals movement for all the tracks. A signal
 *        objects with required constructor is pushed back into the vector. The configured
 *        signals are then added to the simulation class which helps keep track of the 
 *        signals pertaining to track segments and tracks.
 * @param   Simulator *simulation,std::vector<tsSystem *>&signals,std::vector<Tracks*>&tracks
 * @return   returns 0 on success.
 */

static int initializeSignals(Simulator *simulation,std::vector<tsSystem *>&signals,std::vector<Tracks*>&tracks) {
   for(unsigned int signalIndex = 0 ; signalIndex < tracks.size() ; signalIndex ++) {
       try{
            signals.emplace_back(new tsSystem(tracks.at(signalIndex)->getTrackendConnection(), tsSystem::GREEN));
            simulation->addTrainsignal(signals[signalIndex],tracks.at(signalIndex)->getTrackendConnection());
           }catch(const std::exception& e) {
               std::cout<<"Expecption caught!!!, unable to add the object"<<e.what()<<std::endl;
           } 
    }
}

/**
 * @brief The below function establishes connections between various tracks. Different index
 *        is utilized to make the appropriate static layout used for the design of Train signal 
 *        system.The addTrainconnection() method of is used to store the layout configuration 
 *        to the simulation class. The try catch have been utilized to handle exception here 
 *        to catch out of range error as .at() methods are being used.
 * @param   Simulator *simulation, std::vector<Tracks*>&tracks
 * @return   returns 0 on success.
 */

static int makeConnections(Simulator *simulation, std::vector<Tracks*>&tracks) {

   for(unsigned int trackIndex = 0; trackIndex < tracks.size(); trackIndex ++) {
       if(trackIndex==4){
          try {
               simulation->addTrainconnection(tracks.at(trackIndex-2)->getTrackendConnection(),tracks.at(trackIndex+1)->getTrackstartConnection(),connectionType.at(trackIndex));
           } catch(const std::out_of_range& oor){
               std::cout <<"Exception thrown , out of range at Index"<<trackIndex<<std::endl;
           }
      } else if(trackIndex == tracks.size()-1) {
           try {
               simulation->addTrainconnection(tracks.at(trackIndex-2)->getTrackendConnection(),tracks.at(trackIndex-5)->getTrackstartConnection(),connectionType.at(trackIndex));
           } catch(const std::out_of_range& oor){
               std::cout <<"Exception thrown , out of range at Index "<<trackIndex<<std::endl;
           }
      } else {
           try {
               simulation->addTrainconnection(tracks.at(trackIndex)->getTrackendConnection(),tracks.at(trackIndex+1)->getTrackstartConnection(),connectionType.at(trackIndex));
          } catch (const std::out_of_range& oor) {
              std::cout <<"Exception thrown in next "<<trackIndex<<std::endl;
          }
        }
    }
   return 0;
}


