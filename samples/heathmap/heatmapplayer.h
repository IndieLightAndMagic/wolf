#ifndef __HEATMAP_PLAYER__
#define __HEATMAP_PLAYER__

#include <QObject>
#include <QKeyEvent>

#include "trackletplayer.h"
#include "heatmap.h"
namespace QQE {

    class HeatMapPlayer : public QQE::TrackletPlayer, public QQE::HeatMap
    {
        Q_OBJECT
        
    public:
        HeatMapPlayer( const QQE::TrackletDataModel& atdm, QObject *parent = 0);
        void updateheatmap(const QVector2D&);
        bool opentrackfile(std::string track_filename) ;
    protected:

    signals:
        //void framechanged(const QVector2D&);
        void heatmapchanged(/**/);


    };

}


#endif/* __HEATMAP_PLAYER__ */