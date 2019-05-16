#include "geometry120.h"
HDC::Plane120::Plane120(){}
void HDC::Plane120::reset(float width, float height){

    m_width = width * 0.5;
    m_height = height * 0.5;

    vertices.clear();
    colors.clear();
    texturecoords.clear();
    normals.clear();
    vertices_location = -1;
    colors_location = -1;
    normals_location = -1;
    texturecoords_location = -1;

    for (auto& index:indices){
        vertices.push_back(vertices_colors_uvs[index * 8 + 0] * m_width);
        vertices.push_back(vertices_colors_uvs[index * 8 + 1] * m_height);
        vertices.push_back(0.0f);        
        
        for (auto vindex = 3; vindex < 6; ++vindex)
            colors.push_back(vertices_colors_uvs[index * 8 + vindex]);
        
        for (auto vindex = 6; vindex < 8; ++vindex)
            texturecoords.push_back(vertices_colors_uvs[index * 8 + vindex]);
    }

}
void HDC::Plane120::setattrlocation(int attrlocation, const Plane120Attr pattr){
    if (pattr == Plane120Attr::vertices){
        vertices_location = attrlocation;
    } else if (pattr == Plane120Attr::colors){
        colors_location = attrlocation;
    } else if (pattr == Plane120Attr::normals){
        normals_location = attrlocation;
    } else if (pattr == Plane120Attr::texturecoords){
        texturecoords_location = attrlocation;
    }
}
const int& HDC::Plane120::getattrlocation(const Plane120Attr pattr) const {
    if (pattr == Plane120Attr::vertices){
        return vertices_location;
    } else if (pattr == Plane120Attr::normals){
        return normals_location;
    } else if (pattr == Plane120Attr::colors){
        return colors_location;
    } else if (pattr == Plane120Attr::texturecoords){
        return texturecoords_location;
    }
    static int error_location{-1}; 
    return error_location;
}
const float* HDC::Plane120::getdata(const Plane120Attr pattr) const {
    if (pattr == Plane120Attr::vertices){
        return vertices.data();
    } else if (pattr == Plane120Attr::normals){
        return normals.data();
    } else if (pattr == Plane120Attr::colors){
        return colors.data();
    } else if (pattr == Plane120Attr::texturecoords){
        return texturecoords.data();
    }
    return nullptr;  
}
const float& HDC::Plane120::getwidth () const {
    return m_width;
}
const float& HDC::Plane120::getheight () const {
    return m_height; 
}