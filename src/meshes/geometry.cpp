#include "geometry.h"
HDC::Geometry::Geometry() : ObjId(){

    glGenVertexArrays(1, &glvao);
    glGenBuffers(1, &glvbo);
    glGenBuffers(1, &glebo);
    enable();

}

void HDC::Geometry::enable(){
    glBindVertexArray(glvao);
}
void HDC::Geometry::disable(){
    glBindVertexArray(0);
}

void HDC::PlaneGeometry::resetplane(){

    auto fast_vertices_colors = vertices_colors.data();
    auto fast_indices = indices.data();
    auto vertices_size = vertices_colors.size() * sizeof(float);
    auto indices_size = indices.size() * sizeof(unsigned int);
    
    glBindBuffer(GL_ARRAY_BUFFER, glvbo);
    glBufferData(GL_ARRAY_BUFFER, vertices_size, fast_vertices_colors, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, fast_indices, GL_DYNAMIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

}

HDC::PlaneGeometry::PlaneGeometry() : Geometry() {

}

void HDC::PlaneGeometry::setwidth(float width){
    vertices_colors[0] = vertices_colors[6] = width;
    vertices_colors[12] = vertices_colors[18] = -width;

}
const float& HDC::PlaneGeometry::width() const{
    return vertices_colors[0];
}
void HDC::PlaneGeometry::setheight(float height){
    vertices_colors[1] = vertices_colors[19] = height;
    vertices_colors[13] = vertices_colors[7] = -height;
}
const float& HDC::PlaneGeometry::height() const{
    return vertices_colors[1];
}




void HDC::TexturedPlaneGeometry::resetplane(){
    auto fast_vertices_colors_uvs = vertices_colors_uvs.data();
    auto fast_indices = indices.data();
    auto vertices_size = vertices_colors_uvs.size() * sizeof(float);
    auto indices_size = indices.size() * sizeof(unsigned int);
    
    glBindBuffer(GL_ARRAY_BUFFER, glvbo);
    glBufferData(GL_ARRAY_BUFFER, vertices_size, fast_vertices_colors_uvs, GL_DYNAMIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, fast_indices, GL_DYNAMIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    // texture coord attribute
    glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
    glEnableVertexAttribArray(2);

}
HDC::TexturedPlaneGeometry::TexturedPlaneGeometry() : PlaneGeometry() {

    resetplane();

}

void HDC::TexturedPlaneGeometry::setwidth(float width){
    vertices_colors_uvs[0] = vertices_colors_uvs[8] = width;
    vertices_colors_uvs[16] = vertices_colors_uvs[24] = -width;
}
const float& HDC::TexturedPlaneGeometry::width() const{
    return vertices_colors_uvs[0];
}
void HDC::TexturedPlaneGeometry::setheight(float height){
    vertices_colors_uvs[1] = vertices_colors_uvs[25] = height;
    vertices_colors_uvs[17] = vertices_colors_uvs[9] = -height;
}
const float& HDC::TexturedPlaneGeometry::height() const{
    return vertices_colors_uvs[1];
}

HDC::PlaneGeometry120::PlaneGeometry120(){

}

void HDC::PlaneGeometry120::resetplane(){
    vertices_120.clear();
    colors_120.clear();
    for (auto&index : indices){
        vertices_120.push_back(vertices_colors[index * 6 + 0]);
        vertices_120.push_back(vertices_colors[index * 6 + 1]);
        vertices_120.push_back(vertices_colors[index * 6 + 2]);
        colors_120.push_back(vertices_colors[index*6 + 3]);
        colors_120.push_back(vertices_colors[index*6 + 4]);
        colors_120.push_back(vertices_colors[index*6 + 5]);
    }

}

void HDC::PlaneGeometry120::setsize(float width, float height){
    resetplane();
    auto sz = vertices_120.size();
    for (auto index = 0; index < sz; index += 3){
        vertices_120[index + 0] *= width;
        vertices_120[index + 1] *= height;
        vertices_120[index + 2] = 0.0f;  
    }

}


HDC::TexturedPlaneGeometry120::TexturedPlaneGeometry120() {

}
void HDC::TexturedPlaneGeometry120::resetplane() {
    PlaneGeometry120::resetplane();
    uvs_120.clear();
    for (auto&index : indices){
        uvs_120.push_back(uvs[index * 6 + 0]);
        uvs_120.push_back(uvs[index * 6 + 1]);
        uvs_120.push_back(uvs[index * 6 + 2]);

    }

}