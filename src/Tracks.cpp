#include "Tracks.h"
#include "ConnecTracks.h"

Tracks::Tracks(double length, const std::string& name){
    this->length = length;
    this->name= name;
    trackStartconnection = new connecTracks(this);
    trackEndconnection = new connecTracks(this);
}

Tracks::~Tracks() {
    delete trackStartconnection;
    delete trackEndconnection;
}

double Tracks::getTracklength() const {
    return length;
}

connecTracks* Tracks::getTrackstartConnection() const {
    return trackStartconnection;
}

connecTracks* Tracks::getTrackendConnection() const {
    return trackEndconnection;
}

const std::string& Tracks::getTrackname() const {
    return name;
}
