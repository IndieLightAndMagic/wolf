#include "trackletplayer.h"

void HDC::TrackletPlayer::TrackletPlayer(QObject* parent):HDC::TimedCounter(parent){



}

bool HDC::TrackletPlayer::opentrackfile(std::string track_filename){
	return true;
}