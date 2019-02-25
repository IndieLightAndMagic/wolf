//profound carnage splash: pcs
//wolfenstein3d class splash: wcs

#version 330 core
out vec4 FragColor;
  
in vec3 ourColor;
in vec2 TexCoord;

uniform sampler2D ourTexture;
uniform float pcsSlider;
uniform float wcsSlider;

void main()
{
    //FragColor = texture(pcsTexture, TexCoord) * pcsSlider + texture(wcsTexture, TexCoord) * wcsSlider;
    FragColor = texture(ourTexture, TexCoord);

}
