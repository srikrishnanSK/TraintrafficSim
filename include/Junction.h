#ifndef JUNCTION_H
#define JUNCTION_H

#include "ConnecTracks.h"

class Junction {
    private:
    connecTracks* incoming;
    connecTracks* outgoingFirst;
    connecTracks* outgoingSecond;
    
public:
    Junction(connecTracks* incoming, connecTracks* outgoingirst, connecTracks* outgoingSecond);
    void setTrainconnection(connecTracks* outgoing);
    connecTracks* getselectedConoutput();
};
#endif