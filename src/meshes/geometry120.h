#ifndef _HDC_GEOMETRY_
#define _HDC_GEOMETRY_

#include "objid.h"
#include "opengl/sys/openglcommon.h"

#include <vector> 

namespace HDC {

    class Plane120 : public HDC::ObjId {
    protected:
        float m_width{1.0f};
        float m_height{1.0f};
        int vertices_location;
        int colors_location;
        int texturecoords_location;
        int normals_location;
        std::vector<float> vertices_colors_uvs{
            // positions          // colors           // texture coords
             1.0f,  1.0f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f, // top right
             1.0f, -1.0f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f, // bottom right
            -1.0f, -1.0f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f, // bottom left
            -1.0f,  1.0f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f  // top left 
        };
        std::vector<unsigned int> indices{
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };
        std::vector<float> vertices{};
        std::vector<float> colors{};
        std::vector<float> texturecoords{};
        std::vector<float> normals{};
    public:
        Plane120();
        enum class Plane120Attr {
            vertices,
            normals,
            texturecoords,
            colors
        };
        void reset(float width = 1.0f, float height = 1.0f);
        void setattrlocation(int attrlocation, const Plane120Attr pattr);
        const int& getattrlocation(const Plane120Attr pattr) const;
        const float* getdata(const Plane120Attr pattr) const ;
        const float& getwidth () const ;
        const float& getheight () const ;
    };
}
#endif //_HDC_GEOMETRY_