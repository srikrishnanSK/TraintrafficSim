#ifndef TRACKS_H
#define TRACKS_H

#include <memory>
#include <string>
#include "ConnecTrains.h"

class connecTrains;

class Tracks {
public:
    Tracks(double length, const std::string& name);
    ~Tracks();
    double getTracklength() const;
    connecTrains* getTrackstartConnection() const;
    connecTrains* getTrackendConnection() const;
    const std::string& getTrackname() const;

private:
    double length;
    std::string name;
    connecTrains* trackStartconnection;
    connecTrains* trackEndconnection;
};
#endif