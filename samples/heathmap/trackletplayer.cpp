#include "trackletplayer.h"
#include <iostream>
QQE::TrackletPlayer::TrackletPlayer(const QQE::TrackletDataModel& atdm, QObject* parent):QQE::TimedCounter(parent){

    tdm = atdm;
    connect(this, &TimedCounter::counter_ticked, this, &QQE::TrackletPlayer::readnewframe);
    
}
void QQE::TrackletPlayer::selecttrackletid(unsigned int channel) {

    assert(tdm.id_entity_map.find(channel) != tdm.id_entity_map.end());
    selected_tracklet = &(tdm.id_entity_map[channel]);
}
void QQE::TrackletPlayer::readnewframe(int){

    auto size = selected_tracklet->ktlet.positions.size();
    static int lastx = 0;
    static int lasty = 0;
    m_frame_index += pbdirection == PlaybackDirection::forwards ? 1 : -1;
    auto frameindex = m_frame_index % size;
    auto& qv3d = selected_tracklet->ktlet.positions[frameindex];
    emit framechanged(QVector2D{std::floorf(qv3d.x()*tdm.court_size.width()),std::floorf(qv3d.y()*tdm.court_size.height())});
    /*std::cout 
    << frameindex 
    << " : " 
    << " (" 
    << qv3d.x() << " , "
    << qv3d.y() << ") "
    << std::floorf(qv3d.x()*tdm.court_size.width())
    << " , "
    << std::floorf(qv3d.y()*tdm.court_size.height()) 
    << std::endl;*/


}



void QQE::TrackletPlayer::playtracklet(QQE::TrackletPlayer::PlaybackDirection pb){

    pause();
    setdirection(pb);
    start();

}
void QQE::TrackletPlayer::pausetracklet(){
    pause();
}
void QQE::TrackletPlayer::playtrackletat(int atindex){
    //setcountervalue(atindex);
}

void QQE::TrackletPlayer::setfpsfactor(float factor){

}
void QQE::TrackletPlayer::setdirection(PlaybackDirection pb){
    pbdirection = pb;
}


