
#include <map>
#include <string>
#include <iostream>
#include <functional>

#include <QFile>
#include <QString>
#include <QVector3D>

#include <nlohmann/json.hpp>

using j = nlohmann::json;
#include "hdata.h"

static j _j{};
static j _parse(std::string filename){

    auto stdfile = std::fopen(filename.c_str(), "r");
    auto qfile = QFile();
    qfile.open(stdfile, QIODevice::ReadOnly);
    auto qsize = qfile.size();
    auto qmap = qfile.map(0, qsize);
    auto _json = j::parse(qmap);
    qfile.close();
    std::fclose(stdfile);
    return _json;

}

void HDC::Visitor::Parse(std::string filename){

    _j = _parse(filename);

}
void HDC::TrackletDataModel::getspeedandacceleration(){

    for (auto&[k,e]:id_entity_map){
        auto tracksize = e.ktlet.positions.size();
        if (tracksize > 2){
            for (auto index = 1; index < tracksize; ++index){
                auto pos_t_now = e.ktlet.positions[index];
                auto pos_t_before = e.ktlet.positions[index-1];
                auto speed = QVector3D{
                    pos_t_now.x() - pos_t_before.x(),
                    pos_t_now.y() - pos_t_before.y(),
                    0.0f
                };
                e.ktlet.speeds.push_back(speed);
                auto speedtracksize = e.ktlet.speeds.size();
                if (speedtracksize > 2){
                    for (auto index = 1; index < speedtracksize; ++index){
                        auto speed_t_now = e.ktlet.speeds[index];
                        auto speed_t_before = e.ktlet.speeds[index-1];
                        auto accel = QVector3D{
                            speed_t_now.x() - speed_t_before.x(),
                            speed_t_now.y() - speed_t_before.y(),
                            0.0f
                        };
                        e.ktlet.accels.push_back(accel);
                    }
                }
            }
        }
    }
}
void HDC::TrackletDataModel::normalizedata(){

    auto translation = QVector3D{
        court_anchor_point.x() * court_size.width(),
        court_anchor_point.y() * court_size.height(),
        0.0 
    };
    for (auto& [id, e] : id_entity_map){
        for (auto& position : e.ktlet.positions){
            position += translation;
            position *= QVector3D{1.0f / court_size.width(), 1.0f / court_size.height(), 0.0f};
        }
    }
    for (auto& [id, e] : id_entity_map){
        std::cout << "Checking id: " << id << std::endl;
        for (auto& position : e.ktlet.positions){
            if(position.x() > 1.0f) position.setX(1.0f);
            if(position.y() > 1.0f) position.setY(1.0f);
            if(position.y() < 0.0f) position.setY(0.0f);
            if(position.x() < 0.0f) position.setX(0.0f);
        }
        std::cout << "[OK]" << std::endl;
    }

}
void HDC::TrackletDataModel::getdata(){

    auto class_map = _j["metadata"]["class_map"];
    for (auto& [k_,v_] : class_map.items()){
        auto k = std::stoul(k_);
        std::string v = v_.get<std::string>();
        classcaptions[k] = v;
    }
    assert(!classcaptions.empty());

    court_size = QSize{
            static_cast<int>(_j["metadata"]["court"]["court_size"][0].get<float>()),
            static_cast<int>(_j["metadata"]["court"]["court_size"][1].get<float>())
    };
    assert(court_size.width() > 0.0f);
    assert(court_size.height() > 0.0f);

    court_anchor_point = QVector3D{
        _j["metadata"]["court"]["court_center"][0].get<float>(),
        _j["metadata"]["court"]["court_center"][1].get<float>(),
        _j["metadata"]["court"]["court_center"][2].get<float>()
    };

    enum class state{
        free,
        onid
    };
    auto camera_count = 0u;
    for (auto camera: _j["cameras"]){
        camera_count++;
        auto frame_count = 0;
        std::cout << "Cams: " << camera["id"].get<std::string>() << std::endl;
        for (auto frame : camera["images"]){
            frame_count++;
            state s{state::free};
            auto framenumber = frame["index"].get<int>();
            for (auto& bbox : frame["boundingboxes"]){

                auto id = std::stoul(bbox["id"].get<std::string>());

                auto idnotfound = id_entity_map.find(id) == id_entity_map.end();
                if (idnotfound) {

                    id_entity_map[id] = Entity{};
                    id_entity_map[id].ci.class_caption = classcaptions[id];
                }

                auto& e = id_entity_map[id];


                if (e.ktlet.frame_offset > framenumber) e.ktlet.frame_offset = framenumber;
                auto position = QVector3D{
                    bbox["court_CM"][0].get<float>(), 
                    bbox["court_CM"][1].get<float>(), 
                    bbox["court_CM"][2].get<float>()
                };
                e.ktlet.positions.push_back(position);
            }
        }
        std::cout << "Camera: " << camera_count << " -- " << frame_count << std::endl;
        if (max_frame_count < frame_count) max_frame_count = frame_count;
    }
    _j.erase("metadata");
    _j.erase("fps");
    _j.erase("cameras");

}


























