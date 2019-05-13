#include "heatmapplayer.h"
#include <iostream>

HDC::HeatMapPlayer::HeatMapPlayer(QObject* parent):
HDC::TrackletPlayer(parent),
HDC::HeatMap(){

}
void HDC::HeatMapPlayer::updateheatmap(QVector2D& pos){

	inc(pos.x(), pos.y());
	std::cout << "Max Value is: " << getmax();
}
bool HDC::HeatMapPlayer::opentrackfile(std::string track_filename){

	assert(TrackletPlayer::opentrackfile(track_filename));
	HeatMap::initheatmap(tdm.court_size, 10);
	return true;
}


