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

HDC::Plane::Plane() : Geometry() {

	auto fast_vertices_colors = vertices_colors.data();
	auto fast_indices = indices.data();
	auto vertices_size = vertices_colors.size() * sizeof(float);
	auto indices_size = indices.size() * sizeof(unsigned int);
	
	glBindBuffer(GL_ARRAY_BUFFER, glvbo);
    glBufferData(GL_ARRAY_BUFFER, vertices_size, fast_vertices_colors, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, fast_indices, GL_STATIC_DRAW);

    // position attribute
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);
    // color attribute
    glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

}


HDC::TexturedPlane::TexturedPlane() : Plane() {

	auto fast_vertices_colors_uvs = vertices_colors_uvs.data();
	auto fast_indices = indices.data();
	auto vertices_size = vertices_colors_uvs.size() * sizeof(float);
	auto indices_size = indices.size() * sizeof(unsigned int);
	
	glBindBuffer(GL_ARRAY_BUFFER, glvbo);
    glBufferData(GL_ARRAY_BUFFER, vertices_size, fast_vertices_colors_uvs, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, glebo);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices_size, fast_indices, GL_STATIC_DRAW);

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