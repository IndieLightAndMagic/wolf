#include "trackletplayer.h"
#include <iostream>
HDC::TrackletPlayer::TrackletPlayer(const HDC::TrackletDataModel& atdm, QObject* parent):HDC::TimedCounter(parent){

    tdm = atdm;
    connect(this, &TimedCounter::counter_ticked, this, &HDC::TrackletPlayer::readnewframe);
    
}
void HDC::TrackletPlayer::selecttrackletid(unsigned int channel) {

    assert(tdm.id_entity_map.find(channel) != tdm.id_entity_map.end());
    selected_tracklet = &(tdm.id_entity_map[channel]);
}
void HDC::TrackletPlayer::readnewframe(int){

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



void HDC::TrackletPlayer::playtracklet(HDC::TrackletPlayer::PlaybackDirection pb){

    pause();
    setdirection(pb);
    start();

}
void HDC::TrackletPlayer::pausetracklet(){
    pause();
}
void HDC::TrackletPlayer::playtrackletat(int atindex){
    //setcountervalue(atindex);
}

void HDC::TrackletPlayer::setfpsfactor(float factor){

}
void HDC::TrackletPlayer::setdirection(PlaybackDirection pb){
    pbdirection = pb;
}


