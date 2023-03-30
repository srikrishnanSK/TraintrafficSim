#ifndef CONNECTRACKS_H
#define CONNECTRACKS_H

#include "Tracks.h"
#include "SignalSystem.h"

class Tracks;// Forward declaration
class tsSystem;//Forward Declerarion

/** This class is responsible for connectin trains and tracks, holding their respective signals, providing all required track related
 *  information and also help calculate distance between tracks to find the shortest path 
*/
class connecTracks {
public:
   enum trainConnectionType {
      DIRECT = 0, 
      JUNCTION, 
      TERMINATOR 
   };

   //Constructor and Destructor
   connecTracks(Tracks* parentTrack);
   ~connecTracks();

   //Connect Trains, set signal and compute distance
   void connectTrains(connecTracks* train, trainConnectionType type);
   void setTrainsignal(tsSystem* trainSsignal);
   bool trainhasSignal() const;
   int getTraindistanceTo(const connecTracks* train) const;

   //Get track links and signal information
   connecTracks* getNextlink();
   Tracks* getParenttrack();
   trainConnectionType getTrainconType();
   tsSystem* getTrainSignal() const;

private:
   Tracks* parentTrack;
   connecTracks* nextLink;
   trainConnectionType trainType;
   tsSystem* trainSignal;
};

#endif