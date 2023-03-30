#ifndef TRACKS_H
#define TRACKS_H

#include <memory>
#include <string>
#include "ConnecTracks.h"

class connecTracks;//Forward Decleration 

/**This class is responsible for handling all operations related to tracks to set their lengths, names, and get their start and end points*/
class Tracks {
public:
   //Constructor and Destructor
   Tracks(int length, const std::string& name);
   ~Tracks();
   //Operations for handling tracks
   int getTracklength() const;
   connecTracks* getTrackstartConnection() const;
   connecTracks* getTrackendConnection() const;
   const std::string& getTrackname() const;

private:
   int length;
   std::string name;
   connecTracks* trackStartconnection;
   connecTracks* trackEndconnection;
};
#endif