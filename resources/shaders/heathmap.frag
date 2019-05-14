#version 410 core
out vec4 FragColor;
in vec4 ourColor;
in vec2 TexCoord;

uniform sampler2D heat__texture;
uniform sampler2D court_texture;
uniform float fblend;
uniform float fgrid;


void main(){


    /*float x = TexCoord.x * fgrid;
	x = floor(x);
	x /= fgrid;
    float y = TexCoord.y * fgrid;
    y = floor(y);
    y /= fgrid;*/
    vec4 sampledColor = texture(heat__texture,TexCoord);
    

	FragColor = sampledColor*fblend + texture(court_texture,TexCoord) * (1.0f - fblend);

}