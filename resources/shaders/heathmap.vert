#version 410 core
layout (location = 0) in vec4 posAttr;
layout (location = 1) in vec4 colAttr;
layout (location = 2) in vec2 texAttr;

out vec4 ourColor;
out vec2 TexCoord;
uniform mat4 matrix;

void main() {
	
	TexCoord = texAttr;
	ourColor = colAttr;
	gl_Position = matrix * posAttr;


}
