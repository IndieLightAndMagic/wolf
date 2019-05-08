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

    class Plane : public HDC::Geometry{

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
        Plane();
    };

    class TexturedPlane : public HDC::Plane {

    protected:

        std::vector<float> vertices_colors_uvs{
            // positions          // colors           // texture coords
             1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
             1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
        };

    public:
        TexturedPlane();


    };
}
#endif //_HDC_GEOMETRY_