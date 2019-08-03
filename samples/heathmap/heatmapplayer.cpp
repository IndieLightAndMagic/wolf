#include "heatmapplayer.h"
#include <iostream>

QQE::HeatMapPlayer::HeatMapPlayer(const QQE::TrackletDataModel& atdm, QObject* parent):
QQE::TrackletPlayer(atdm, parent),
QQE::HeatMap(atdm.court_size.width(), atdm.court_size.height() ){
    connect(this, &QQE::TrackletPlayer::framechanged, this, &QQE::HeatMapPlayer::updateheatmap);

}
void QQE::HeatMapPlayer::updateheatmap(const QVector2D& pos){
	static auto lastmax = getmax();
	inc(pos.x(), pos.y());

	auto max = getmax();
	if (max >= lastmax + 0.05){
		lastmax = max;
		std::cout << "Max Value is: " << max << std::endl;

	}

}


