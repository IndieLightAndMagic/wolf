#version 410 core
layout (location = 0) in vec4 posAttr;
layout (location = 1) in vec4 colAttr;
layout (location = 2) in vec2 texAttr;

uniform mat4 matrix;
uniform float selector;

layout (std140) uniform Atlas
{
    uint fAtlas[130];
};

out vec4 col;
vec4 getColorFromTexture(){

    uint ucol = fAtlas[int(selector)];  
    float ur  = (ucol & 0xffu);
    float ug  = ((ucol & 0xff00u) >> 8);
    float ub  = ((ucol & 0xff0000u)>> 16);


    return vec4(ur/255.0, ug/255.0, ub/255.0, 1.0f);

}


void main() {
    
    col = getColorFromTexture();
    gl_Position = matrix * posAttr;
}
