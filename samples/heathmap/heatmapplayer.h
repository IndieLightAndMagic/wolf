#ifndef __HEATMAP_PLAYER__
#define __HEATMAP_PLAYER__

#include <QVector3D>
#include "trackletplayer.h"
class HeatmapPlayer : public HDC::TrackletPlayer{


	Q_OBJECT
public:
	HeatmapPlayer(QObject* parent = 0);
private:
	void updateheatmap(const QVector3D&)
};




#endif