#ifndef TRACKS_H
#define TRACKS_H

#include <memory>
#include <string>
#include "ConnecTracks.h"

class connecTracks;

class Tracks {
public:
    Tracks(double length, const std::string& name);
    ~Tracks();
    double getTracklength() const;
    connecTracks* getTrackstartConnection() const;
    connecTracks* getTrackendConnection() const;
    const std::string& getTrackname() const;

private:
    double length;
    std::string name;
    connecTracks* trackStartconnection;
    connecTracks* trackEndconnection;
};
#endif