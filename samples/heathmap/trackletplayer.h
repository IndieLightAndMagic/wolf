#ifndef __TRACKLET_PLAYER_H_
#define __TRACKLET_PLAYER_H_

#include <QObject>
#include <QKeyEvent>

#include "hdata.h"
#include "timedcounter.h"

namespace HDC {

    class TrackletPlayer : public HDC::TimedCounter
    {
        Q_OBJECT
        TrackletDataModel tdm;
    public:

        TrackletPlayer( QObject *parent = 0 );

        bool opentrackfile(std::string track_filename); 

        void playtracklet();
        void pausetracklet();
        void playtrackletat(unsigned int index);



        const HDC::Entity& gettracks();

        void setfpsfactor(float factor = 1.0f);
        signals:
        void framechanged(const QVector3D&);
    protected:
        //bool eventFilter( QObject *dist, QEvent *event);

    };

}


#endif/* __TRACKLET_PLAYER_H_ */