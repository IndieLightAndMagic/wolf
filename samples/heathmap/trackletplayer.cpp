#include "trackletplayer.h"

HDC::TrackletPlayer::TrackletPlayer(QObject* parent):HDC::TimedCounter(parent){



}

bool HDC::TrackletPlayer::opentrackfile(std::string track_filename){

	HDC::Visitor v;
	v.Parse(std::string{RESOURCES_DIR} + "/json/court_cm.json");
    
    tdm.getdata();
    tdm.normalizedata();
    tdm.getspeedandacceleration();
    
	return true;
}