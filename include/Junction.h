#ifndef JUNCTION_H
#define JUNCTION_H

#include "ConnecTrains.h"

class Trackjunction {
    private:
    connecTrains* incoming;
    connecTrains* outgoingFirst;
    connecTrains* outgoingSecond;
    
public:
    Trackjunction(connecTrains* incoming, connecTrains* outgoingirst, connecTrains* outgoingSecond);
    void setTrainconnection(connecTrains* outgoing);
    connecTrains* getselectedConoutput();
};
#endif