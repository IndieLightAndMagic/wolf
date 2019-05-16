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
        void setsize(float width, float height);
        PlaneGeometry();
        void setwidth(float width);
        const float& width() const;
        void setheight(float height);
        const float& height() const;


    };
    class PlaneGeometry120  {
        int vertexAttrLocation;
        int colorAttrLocation;
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
        std::vector<float> vertices_120{
        };
        std::vector<float> colors_120{
        };

    public:
        PlaneGeometry120();
        void resetplane();
        inline int& getvertexattr(){ return vertexAttrLocation; };
        inline int& getcolorattr(){return colorAttrLocation; };
        inline float* getvertexdata(){ return vertices_120.data(); };
        inline float* getcolordata(){ return colors_120.data(); };
        inline unsigned char getnumvertices() { return vertices_120.size() / 3; }
        void setsize(float width, float height);
        const float& width() const;
        const float& height() const;

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

    class TexturedPlaneGeometry120 : public HDC::PlaneGeometry120 {
    protected:
        std::vector<float> uvs {};
    public:
        void resetplane();
        TexturedPlaneGeometry120();
        void setsize(float width, float height);
        const float& width() const;
        const float& height() const;


    };

}
#endif //_HDC_GEOMETRY_