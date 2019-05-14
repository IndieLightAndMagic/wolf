#version 410 core
out vec4 FragColor;
in vec4 ourColor;
in vec2 TexCoord;

uniform sampler2D heat__texture;
uniform sampler2D court_texture;
uniform float fblend;
uniform float fgrid;


void main(){

    vec4 sampledColor = texture(heat__texture,TexCoord);
    if (sampledColor.r > 0.12f) {
    	sampledColor.b = 1.0f - sampledColor.r*.2;
    	sampledColor.b *= 0.4;
    	
    } 

	FragColor = sampledColor*fblend + texture(court_texture,TexCoord) * (1.0f - fblend);

}