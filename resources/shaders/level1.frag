#version 410 core
out vec4 FragColor;

in vec4 col;
in vec2 TexCoord;


void main() {
   FragColor = col;
}