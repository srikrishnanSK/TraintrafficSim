#include "Tracks.h"
#include "ConnecTrains.h"

Tracks::Tracks(double length, const std::string& name){
    this->length = length;
    this->name= name;
    trackStartconnection = new connecTrains(this);
    trackEndconnection = new connecTrains(this);
}

Tracks::~Tracks() {
    delete trackStartconnection;
    delete trackEndconnection;
}

double Tracks::getTracklength() const {
    return length;
}

connecTrains* Tracks::getTrackstartConnection() const {
    return trackStartconnection;
}

connecTrains* Tracks::getTrackendConnection() const {
    return trackEndconnection;
}

const std::string& Tracks::getTrackname() const {
    return name;
}
