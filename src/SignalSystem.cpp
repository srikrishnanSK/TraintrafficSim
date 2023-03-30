#include "SignalSystem.h"

//Class Constructor
tsSystem::tsSystem(connecTracks* connecTrack, trainSignalstate initState) : connecTrack(connecTrack),currentTrainstate(initState){}

//Class Destrcutor 
tsSystem::~tsSystem(){}

/**
 * @brief  The setTrainstate method is used to set the state of track associated accordingly.
 * @param  trainSignalstate state
 * @return Returns nothing. Reutrn type is void.
 */
void tsSystem::setTrainstate(trainSignalstate state) {
    currentTrainstate = state;
}

/**
 * @brief  The getTrainstate returns the appropriate enum associated with the object related to that track segment.
 * @param  no arguments.
 * @return Returns trainSignalstate.
 */
tsSystem::trainSignalstate tsSystem::getTrainstate() {
    return currentTrainstate;
}
