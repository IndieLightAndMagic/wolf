#include "heatmapplayer.h"
#include <iostream>

HDC::HeatMapPlayer::HeatMapPlayer(const HDC::TrackletDataModel& atdm, QObject* parent):
HDC::TrackletPlayer(atdm, parent),
HDC::HeatMap(atdm.court_size.width(), atdm.court_size.height() ){
    connect(this, &HDC::TrackletPlayer::framechanged, this, &HDC::HeatMapPlayer::updateheatmap);

}
void HDC::HeatMapPlayer::updateheatmap(const QVector2D& pos){

	inc(pos.x(), pos.y());
	std::cout << "Max Value is: " << getmax();

}


