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
        int m_frame_index{0};
    public:
        enum class PlaybackDirection{
            forwards,
            backwards
        };
        TrackletPlayer( const HDC::TrackletDataModel& atdm, QObject *parent = 0);

        void playtracklet(PlaybackDirection pb = PlaybackDirection::forwards); // Play the tracklet
        void pausetracklet(); // Pause reproduction
        void playtrackletat(int index); // Set the frame where to play: TODO
        void setdirection(PlaybackDirection pb); //Set the direction to go to
        void setfpsfactor(float factor = 1.0f); //Set playback speed: TODO
        void selecttrackletid(unsigned int channel);

        void readnewframe(int);

    protected:
        //bool eventFilter( QObject *dist, QEvent *event);
        HDC::Entity* selected_tracklet{nullptr};
        TrackletDataModel tdm;
        PlaybackDirection pbdirection{PlaybackDirection::forwards};

    signals:
        void framechanged(const QVector2D&);
        void trackletopened();



    };

}


#endif/* __TRACKLET_PLAYER_H_ */