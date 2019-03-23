#version 330 core    
layout (location = 0) in vec4 posAttr;
layout (location = 1) in vec4 colAttr;
layout (location = 2) in vec2 texAttr;

out vec4 col;
out vec2 TexCoord;
uniform mat4 matrix;

void main() {
	
	col = colAttr;
	TexCoord = texAttr;
	gl_Position = matrix * posAttr;

}
