#version 410 core
out vec4 FragColor;
in vec4 ourColor;
in vec2 TexCoord;
uniform sampler2D ourTexture;
uniform float pcsSlider;
void main(){
   
   vec4 red = vec4(abs(TexCoord.x), 0.0f, 0.0f, 0.0f);
   vec4 blue = vec4(0.0f, TexCoord.y, 0.0f, 0.0f);
   //FragColor=texture(ourTexture,TexCoord)*pcsSlider;
   FragColor=(red + blue) * pcsSlider + texture(ourTexture,TexCoord)*(1.0f - pcsSlider);
}