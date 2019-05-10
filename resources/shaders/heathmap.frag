#version 410 core
out vec4 FragColor;
in vec4 ourColor;
in vec2 TexCoord;

uniform sampler2D heat__texture;
uniform sampler2D court_texture;
uniform float fblend;
uniform float fgrid;


void main(){

   float x = TexCoord.x * fgrid;
   x = floor(x);
   x /= fgrid;

   float y = TexCoord.y * fgrid;
   y = floor(y);
   y /= fgrid;


   vec4 red = vec4(1.0f - x, 0.0f, 0.0f, 0.0f);
   vec4 blue = vec4(0.0f, 0.0f, 1.0 - y, 0.0f);
   FragColor=(red + blue)*fblend + texture(court_texture,TexCoord) * (1.0f - fblend);

}