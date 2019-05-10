#ifndef __H_DATA__ 
#define __H_DATA__

#include <string>
#include <map>

namespace HDC {


    struct HeatData{

        float* heatdata_ptr{nullptr};
        struct {    
            std::string dataset;
            std::string author;
            std::string date;
            std::map<std::string, std::string> classmap;
            struct {
                struct {
                  float width;
                  float height;

              }size;
              struct {
                  float anchor_x;
                  float anchor_y;

              } center;
          }court;          

        }metadata;

    };
    struct AnyJson {

        virtual float GetNumber(std::string field);
        virtual long GetInteger(std::string field);
        virtual std::string GetString(std::string field);
        virtual std::vector<HDC::AnyJson*> GetArray(std::string field);
        virtual HDC::AnyJson* GetJson(std::string field);

    };
    class Visitor {

        void VisitRoot(HDC::AnyJson* json);
        void VisitMetadata(HDC::AnyJson* json);
        void VisitCameras(std::vector<HDC::AnyJson*> jsonarray);
        void VisitCamera(HDC::AnyJson* json);
        void VisitImages(std::vector<HDC::AnyJson*> jsonarray);
        void VisitImage(HDC::AnyJson* json);
        void VisitBBoxes(std::vector<HDC::AnyJson*> jsonarray);
        void VisitBBox(HDC::AnyJson* json);
        void VisitBox2D(std::vector<HDC::AnyJson*> jsonarray);
        void VisitBoxCourt(std::vector<HDC::AnyJson*> jsonarray);
        void ExitRoot(HDC::AnyJson* json);
        void ExitMetadata(HDC::AnyJson* json);
        void ExitCameras(std::vector<HDC::AnyJson*> jsonarray);
        void ExitCamera(HDC::AnyJson* json);
        void ExitImages(std::vector<HDC::AnyJson*> jsonarray);
        void ExitImage(HDC::AnyJson* json);
        void ExitBBoxes(std::vector<HDC::AnyJson*> jsonarray);
        void ExitBBox(HDC::AnyJson* json);
        void ExitBox2D(std::vector<HDC::AnyJson*> jsonarray);
        void ExitBoxCourt(std::vector<HDC::AnyJson*> jsonarray);


    };

}




#endif //__H_DATA__
