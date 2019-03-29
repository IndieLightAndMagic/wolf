#version 410 core
out vec4 FragColor;
in vec4 col;
in vec2 TexCoord;


layout (std140) uniform Atlas
{
    uvec3 fAtlas[4096];
};

uint getcoord(float c){
    c = c * 64.0;
    uint ic = floatBitsToUint(c);
    
    if (ic == 64u)
        ic = 63u; 
    
    return ic;
}
vec4 getColorFromTexture(){

    uint x = getcoord(TexCoord.x);
    uint y = getcoord(TexCoord.y);
    
    uint fAtlas_index =  x + y  * 64u * 11u;

    uint offset_module_shift = 8u * (fAtlas_index & 0x03u); // RNG [0, 3]
    fAtlas_index = fAtlas_index >> 2u;


    
    float r = TexCoord.x;
    float g = TexCoord.y;

    return vec4(r, g, 0.0f, 1.0f);

}
void main() {
    FragColor = getColorFromTexture();
}      