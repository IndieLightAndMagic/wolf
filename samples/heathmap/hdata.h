#ifndef __H_DATA__ 
#define __H_DATA__
#include <utility>
#include <vector>
#include <string>
#include <limits>
#include <cmath>
#include <map>

#include <QVector3D>
#include <QColor>
#include <QSize>

namespace HDC {
    
    struct KTlet{
        unsigned int frame_offset{0};
        std::vector<QVector3D>positions;
        std::vector<QVector3D>speeds;
        std::vector<QVector3D>accels;
    };
    struct ClsInfo {

        std::string class_caption;
        QColor color4;

    };
    struct Entity {

        HDC::KTlet ktlet;
        HDC::ClsInfo ci; 

    };
    
    
    struct TrackletDataModel{

        std::map<unsigned int, std::string> classcaptions{};
        std::map<unsigned int, HDC::Entity> id_entity_map{};
        QSize court_size;
        QVector3D court_anchor_point;
        unsigned int max_frame_count{0};
        void getdata();
        void normalizedata();
        void getspeedandacceleration();
    };

    

    class Visitor {

    public:
        
        static void Parse(std::string filename);

        
    };

}




#endif //__H_DATA__
