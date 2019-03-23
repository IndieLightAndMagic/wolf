#version 330 core
out vec4 FragColor;

in vec4 col;
in vec2 TexCoord;


void main() {
   FragColor = vec4(TexCoord.x, 0.0f, 0.0f, 0.0f);
}