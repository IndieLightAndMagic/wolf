#include "trackletplayer.h"
#include <iostream>
HDC::TrackletPlayer::TrackletPlayer(QObject* parent):HDC::TimedCounter(parent){


    connect(this, &TimedCounter::counter_ticked, this, &HDC::TrackletPlayer::readnewframe);
    
}
void HDC::TrackletPlayer::readnewframe(int){
    
    auto size = tdm.id_entity_map[0].ktlet.positions.size();
    static int lastx = 0;
    static int lasty = 0;
    m_frame_index += pbdirection == PlaybackDirection::forwards ? 1 : -1;
    auto frameindex = m_frame_index % size;
    auto& qv3d = tdm.id_entity_map[0].ktlet.positions[frameindex];
    emit framechanged(QVector2D{std::floorf(qv3d.x()*tdm.court_size.width()),std::floorf(qv3d.y()*tdm.court_size.height())});
    std::cout 
    << frameindex 
    << " : " 
    << " (" 
    << qv3d.x() << " , "
    << qv3d.y() << ") "
    << std::floorf(qv3d.x()*tdm.court_size.width())
    << " , "
    << std::floorf(qv3d.y()*tdm.court_size.height()) 
    << std::endl;


}

bool HDC::TrackletPlayer::opentrackfile(std::string track_filename){

    HDC::Visitor v;
    v.Parse(std::string{RESOURCES_DIR} + track_filename);
    
    tdm.getdata();
    tdm.normalizedata();
    tdm.getspeedandacceleration();

    emit trackletopened();

    return true;
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

