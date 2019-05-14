#include "heatmapplayer.h"
#include <iostream>

HDC::HeatMapPlayer::HeatMapPlayer(const HDC::TrackletDataModel& atdm, QObject* parent):
HDC::TrackletPlayer(atdm, parent),
HDC::HeatMap(atdm.court_size.width(), atdm.court_size.height() ){
    connect(this, &HDC::TrackletPlayer::framechanged, this, &HDC::HeatMapPlayer::updateheatmap);

}
void HDC::HeatMapPlayer::updateheatmap(const QVector2D& pos){
	static auto lastmax = getmax();
	inc(pos.x(), pos.y());

	auto max = getmax();
	if (max >= lastmax + 0.05){
		lastmax = max;
		std::cout << "Max Value is: " << max << std::endl;

	}

}


