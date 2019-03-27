#version 410 core
out vec4 FragColor;
in vec4 col;
in vec2 TexCoord;


layout (std140) uniform Atlas
{
	uvec3 fAtlas[4096];
};

void main() {

	FragColor = vec4(TexCoord.x, TexCoord.y, 0.0f, 0.0f);

}

