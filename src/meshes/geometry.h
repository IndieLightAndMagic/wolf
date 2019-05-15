#ifndef _HDC_GEOMETRY_
#define _HDC_GEOMETRY_

#include "objid.h"
#include "openglcommon.h"

#include <vector> 

namespace HDC {

    class Geometry : public HDC::ObjId {
    protected:
        unsigned int glvao;
        unsigned int glvbo;
        unsigned int glebo;
    public:
        Geometry();
        void enable();
        void disable();
    };

    class PlaneGeometry : public HDC::Geometry{

    protected:
        std::vector<float> vertices_colors{
            // positions          // colors           
             1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   // top right
             1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   // bottom right
            -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   // bottom left
            -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f    // top left 
        };
        std::vector<unsigned int> indices{
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };
    public:
        void resetplane();
        PlaneGeometry();
        void setwidth(float width);
        const float& width() const;
        void setheight(float height);
        const float& height() const;


    };
    class PlaneGeometry120 : public PlaneGeometry{
        int vertexAttrLocation;
        int colorAttrLocation;
    protected:
        std::vector<float> vertices_120{
        };
        std::vector<float> colors_120{
        };

    public:
        PlaneGeometry120(){
            for (auto&index : indices){
                vertices_120.push_back(vertices_colors[index * 6 + 0]);
                vertices_120.push_back(vertices_colors[index * 6 + 1]);
                vertices_120.push_back(vertices_colors[index * 6 + 2]);
                colors_120.push_back(vertices_colors[index*6 + 3]);
                colors_120.push_back(vertices_colors[index*6 + 4]);
                colors_120.push_back(vertices_colors[index*6 + 5]);
            }
        }
        inline int& getvertexattr(){ return vertexAttrLocation; };
        int& getcolorattr(){return colorAttrLocation; };
        float* getvertexdata(){ return vertices_120.data(); };
        float* getcolordata(){ return colors_120.data(); };
        unsigned char getnumvertices() { return vertices_120.size() / 3;

        }

    };

    class TexturedPlaneGeometry : public HDC::PlaneGeometry {

    protected:

        std::vector<float> vertices_colors_uvs{
            // positions          // colors           // texture coords
             1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
             1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
        };

    public:
        void resetplane();
        TexturedPlaneGeometry();
        void setwidth(float width);
        const float& width() const;
        void setheight(float height);
        const float& height() const;



    };
}
#endif //_HDC_GEOMETRY_