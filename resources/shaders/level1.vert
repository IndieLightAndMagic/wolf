#version 410 core
layout (location = 0) in vec4 posAttr;
layout (location = 1) in vec4 colAttr;
layout (location = 2) in vec2 texAttr;

uniform mat4 matrix;
uniform float spriteselector;
layout (std140) uniform Atlas
{
    uvec4 fAtlas[4096];
};

out vec4 col;
vec4 getColorFromPalette(uint iselector){
    
    //Retrieve the color from the palette.
    uint selectormodulo = iselector % 4;
    uint selectorindex = iselector >> 2;

    uint ucol = 0;
    if (selectormodulo == 0)
        ucol = fAtlas[selectorindex].x;
    else if (selectormodulo == 1)
        ucol = fAtlas[selectorindex].y;
    else if (selectormodulo == 2)
        ucol = fAtlas[selectorindex].z;
    else if (selectormodulo == 3)
        ucol = fAtlas[selectorindex].w;

    float ur  = (ucol & 0xffu);
    float ug  = ((ucol & 0xff00u) >> 8);
    float ub  = ((ucol & 0xff0000u)>> 16);

    return vec4(ur/255.0, ug/255.0, ub/255.0, 1.0f);

}

uint queryColorSelectorInTexture(){

    //Get the sprite to paint (0 - 11)
    int ispriteselector = int(spriteselector);
    ispriteselector *= 64;

    //calculate the offset of the pixel in the atlas.
    vec2 fcoord = texAttr * 63.0;
    ivec2 coord = ivec2(int(fcoord.x), int(fcoord.y));
    int ioffset = 1024 + coord.x * ispriteselector + 704 * coord.y;

    //calculate the offset in shader fAtlas
    int offsetmodulo = ioffset % 16;
    int offsetindex = ioffset >> 4;
    
    uvec4 local16pixels = fAtlas[offsetindex];
    uint local16modulo = offsetmodulo % 4;
    uint local16index  = offsetmodulo >> 2;
    uint local4pixels  = 0;
    if (local16index == 0)
        local4pixels = local16pixels.x;
    else if (local16index == 1)
        local4pixels = local16pixels.y;
    else if (local16index == 2)
        local4pixels = local16pixels.z;
    else if (local16index == 3)
        local4pixels = local16pixels.w;
    uint palette_index_selector = (local4pixels >> local16modulo) & 0xffu;
    
    return palette_index_selector;
}
void main() {
    
    //Query the pixel in the texture in the atlas.
    col = getColorFromPalette(queryColorSelectorInTexture());
    gl_Position = matrix * posAttr;

}
