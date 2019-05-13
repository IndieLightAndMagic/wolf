#ifndef __HEATMAP_PLAYER__
#define __HEATMAP_PLAYER__

#include <QObject>
#include <QKeyEvent>

#include "trackletplayer.h"
#include "heatmap.h"
namespace HDC {

    class HeatMapPlayer : public HDC::TrackletPlayer, public HDC::HeatMap
    {
        Q_OBJECT
        
    public:
        HeatMapPlayer( QObject *parent = 0 );
        void updateheatmap(QVector2D&);
        bool opentrackfile(std::string track_filename) ;
    protected:

    signals:
        //void framechanged(const QVector2D&);
        void heatmapchanged(/**/);


    };

}


#endif/* __HEATMAP_PLAYER__ */