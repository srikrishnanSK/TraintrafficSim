#include "Tracks.h"

//Class contructor
Tracks::Tracks(int length, const std::string& name) : length(length),name(name) {
    trackStartconnection = new connecTracks(this);
    trackEndconnection = new connecTracks(this);
}

//Class Destructor
Tracks::~Tracks() {
    delete trackStartconnection;
    delete trackEndconnection;
}

/**
 * @brief  The getTracklength is used to return the set tracks length.
 * @param  no arguments.
 * @return Returns length of integer type.
 */
int Tracks::getTracklength() const {
    return length;
}

/**
 * @brief  The getTrackstartConnection method is used to return the starting point of a track accordingly.
 * @param  no arguments
 * @return Returns an object of connecTracks* type.
 */
connecTracks* Tracks::getTrackstartConnection() const {
    return trackStartconnection;
}

/**
 * @brief  The getTrackendConnection method is used to return the end point of a track accordingly.
 * @param  no arguments
 * @return Returns an object of connecTracks* type.
 */
connecTracks* Tracks::getTrackendConnection() const {
    return trackEndconnection;
}

/**
 * @brief  The getTrackname method is used to return the associated tracks name.
 * @param  no arguments
 * @return Returns name of type string.
 */
const std::string& Tracks::getTrackname() const {
    return name;
}
