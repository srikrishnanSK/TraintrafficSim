#ifndef JUNCTION_H
#define JUNCTION_H

#include "ConnecTracks.h"

/** This class is responsible for creating junctions and establishing respective connections accordingly*/

class Junction {
   private:
   connecTracks* incoming;
   connecTracks* outgoingFirst;
   connecTracks* outgoingSecond;

public:
   //Constrcutor and Destructor
   Junction(connecTracks* incoming, connecTracks* outgoingirst, connecTracks* outgoingSecond);
   ~Junction();
   //Set the required connection
   void setTrainconnection(connecTracks* outgoing);
   //Get the provided connection output
   connecTracks* getselectedConoutput();
};
#endif