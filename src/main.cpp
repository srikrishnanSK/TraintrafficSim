#include <iostream>
#include <map>
#include <chrono>
#include <thread>
#include "Simulator.h"
#include "Tracks.h"
#include "Trains.h"
#include "SignalSystem.h"
#include "Junction.h"

/** Map Initialization for Tracks comprising of Names of each track as key and their respective lengths as value*/
static std::map<const std::string, int> trackInitializationInfo = {{"A",100},{"B",200},{"C",150},{"D",300},{"E",250},{"F",350},{"G",400},{"H",100},{"I",300},{"J",350},};
/**Map Initialization for Type of Connection a track is going to have with Track index as key and Connection type as their values*/
static std::map<int,connecTracks::trainConnectionType> connectionType = {{0,connecTracks::DIRECT},{1,connecTracks::DIRECT},{2,connecTracks::JUNCTION},{3,connecTracks::TERMINATOR},{4,connecTracks::JUNCTION},{5,connecTracks::DIRECT},{6,connecTracks::DIRECT},{7,connecTracks::JUNCTION},{8,connecTracks::TERMINATOR},{9,connecTracks::JUNCTION},};
/** Map Initialization for Trains in which direction will they move. It has Train number as the Key and FORWARD or REVERSE as its respective value*/
static std::map<int,Trains::Direction> trainDirection = {{0,Trains::FORWARD},{1,Trains::REVERSE},{2,Trains::FORWARD},{3,Trains::REVERSE},{4,Trains::FORWARD},{5,Trains::REVERSE},};
/** Constant value defining total number of Signals to be in place along the Tracks*/
static const unsigned totalSignals = 4; 
/**Initializes different Tracks class object equal to the size of trackInitializationInfo and stores in the vector */
static void initializeTracks(std::vector<Tracks*>&tracks);
/**Initializes different Trains class object with their initial starting points and the direction in which they will move forward */
static void initializeTrains(std::vector<Trains*>&trains,std::vector<Tracks*>&tracks);
/**Initializes different Trains Signal system class objects with tracks end connection point with their respective initial train signal initial states*/
static void initializeSignals(Simulator *simulation,std::vector<tsSystem *>&signals,std::vector<Tracks*>&tracks);
/**Connect various Tracks and add it to the Simulator class*/
static void makeConnections(Simulator *simulation, std::vector<Tracks*>&tracks);

int main() {

   /**Initialte Simulate class*/
   Simulator tsSimulation;
   std::vector<Tracks *> tracks;
   std::vector<Trains *> trains;
   std::vector<tsSystem *> signals;

   ///Init parameters
   initializeTracks(tracks);
   
    //make track connections
   makeConnections(&tsSimulation,tracks);
   
   //Initialize tracks
   initializeTrains(trains,tracks);
   //Initials signals on respective tracks
   initializeSignals(&tsSimulation,signals,tracks);
   

   /**Add the respective tracks and train objects to the Simulator class*/
   for(auto &track : tracks) {
      tsSimulation.addTracks(track);
   }

   for(auto &train : trains) {
      tsSimulation.addTrain(train);
   }

   /** Let the user start the simulation (Press any key to start the simulation)*/
   std::cout<<"Press any key to start the simulation"<<std::endl;
   std::cin.get();
   
   /**Initate multithreaded Simulation*/
   tsSimulation.runSimulation();
   
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
 * @brief  The below function initializes tracks based on the provided map with Track names
 *         as key and their values as the tracks arbitary length. It creats track objects with
 *         required constructor arguments and pushes it back into the vector. Try and catch has 
 *         been added for better expception handling while using emplace_back() method. emplace_back() 
 *         has been used to avoid creating another temporary objecting which can be copied/pushed back 
 *         into the vector provided.
 * @param  std::vector<Tracks*>&tracks
 * @return Returns nothing. Reutrn type is void.
 */
static void initializeTracks(std::vector<Tracks*>&tracks) {

   for(auto it = trackInitializationInfo.begin(); it != trackInitializationInfo.end(); it ++) {
      try{
         tracks.emplace_back(new Tracks(it->second, it->first));
         } catch (const std::exception& e) {
            std::cout<<"Expecption caught!!!, unable to add the object"<<e.what()<<std::endl;
         }
   }
}

/**
 * @brief The below function initializes trains movement from a particular track. Based
 *        on the train Index trains are places on different track segments as per the
 *        design
 * @param   std::vector<Trains*>&trains,std::vector<Tracks*>&tracks
 * @return   Returns nothing. Reutrn type is void.
 */

static void initializeTrains(std::vector<Trains*>&trains,std::vector<Tracks*>&tracks) {
   for(unsigned int trainIndex= 0 ; trainIndex < trainDirection.size(); trainIndex++) {
      Trains* train = nullptr;
      switch (trainIndex)
      {
      case 0:
         train = new Trains(tracks[8],trainDirection.at(trainIndex));
         break;
      case 2:
        train = new Trains(tracks[0],trainDirection.at(trainIndex));
        break;
      case 1:
        train = new Trains(tracks[2],trainDirection.at(trainIndex));
        break;
      case 3:
        train = new Trains(tracks[1],trainDirection.at(trainIndex));
        break;
      case 4:
         train = new Trains(tracks[7],trainDirection.at(trainIndex));
         break;
      case 5:
        train = new Trains(tracks[5],trainDirection.at(trainIndex));
        break;
      default:
        std::cout<<"Invalid index "<<trainIndex<<std::endl;
        break;
      }

     if(train!= nullptr) {
        trains.push_back(train);
     } else{
        std::cout<<"Null point encountered, checked the index and code"<<std::endl;
     }
   }
}

/**
 * @brief The below function initializes signals for all the tracks. A signal
 *        objects with required constructor is pushed back into the vector. The 
 *        configured signals are then added to the simulation class which helps 
 *        keep track of the signals pertaining to track segments and tracks.
 * @param   Simulator *simulation,std::vector<tsSystem *>&signals,std::vector<Tracks*>&tracks
 * @return   returns 0 on success.
 */

static void initializeSignals(Simulator *simulation,std::vector<tsSystem *>&signals,std::vector<Tracks*>&tracks) {
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
 *        to the simulation class. The try catch have been utilized to handle exceptions  
 *        to catch out of range error as .at() method is being used.
 * @param   Simulator *simulation, std::vector<Tracks*>&tracks
 * @return   returns 0 on success.
 */

static void makeConnections(Simulator *simulation, std::vector<Tracks*>&tracks) {

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
}


