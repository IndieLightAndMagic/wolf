#version 410 core
out vec4 FragColor;
in vec4 col;
in vec2 TexCoord;
void main() {

	FragColor = vec4(TexCoord.x, TexCoord.y, 0.0f, 0.0f);

}
