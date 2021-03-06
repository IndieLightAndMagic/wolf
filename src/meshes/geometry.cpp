#include "geometry.h"
QQE::Geometry::Geometry() : ObjId(){

#ifdef __APPLE__
    glGenVertexArrays(1, &glvao);
#endif
    glGenBuffers(1, &glvbo);
    glGenBuffers(1, &glebo);
    enable();

}

void QQE::Geometry::enable(){
#ifdef __APPLE__
    glBindVertexArray(glvao);
#endif
}
void QQE::Geometry::disable(){
#ifdef __APPLE__
    glBindVertexArray(0);
#endif
}

void QQE::PlaneGeometry::resetplane(){

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

QQE::PlaneGeometry::PlaneGeometry() : Geometry() {

}

void QQE::PlaneGeometry::setwidth(float width){
    vertices_colors[0] = vertices_colors[6] = width;
    vertices_colors[12] = vertices_colors[18] = -width;

}
const float& QQE::PlaneGeometry::width() const{
    return vertices_colors[0];
}
void QQE::PlaneGeometry::setheight(float height){
    vertices_colors[1] = vertices_colors[19] = height;
    vertices_colors[13] = vertices_colors[7] = -height;
}
const float& QQE::PlaneGeometry::height() const{
    return vertices_colors[1];
}




void QQE::TexturedPlaneGeometry::resetplane(){
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
QQE::TexturedPlaneGeometry::TexturedPlaneGeometry() : PlaneGeometry() {

    resetplane();

}

void QQE::TexturedPlaneGeometry::setwidth(float width){
    vertices_colors_uvs[0] = vertices_colors_uvs[8] = width;
    vertices_colors_uvs[16] = vertices_colors_uvs[24] = -width;
}
const float& QQE::TexturedPlaneGeometry::width() const{
    return vertices_colors_uvs[0];
}
void QQE::TexturedPlaneGeometry::setheight(float height){
    vertices_colors_uvs[1] = vertices_colors_uvs[25] = height;
    vertices_colors_uvs[17] = vertices_colors_uvs[9] = -height;
}
const float& QQE::TexturedPlaneGeometry::height() const{
    return vertices_colors_uvs[1];
}

