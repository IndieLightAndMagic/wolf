#version 120

attribute vec4 vertex;
attribute vec2 texcoord;
uniform mat4 matrix;
varying vec4 color;
varying vec2 texcoordout;
void main(void)
{
    //vec3 toLight = normalize(vec3(0.0, 0.3, 1.0));
    //float angle = max(dot(normal, toLight), 0.0);
    texcoordout = texcoord;
    vec3 col = vec3(1.0, 0.3, 0.0);
    color = vec4(col * 0.2 + col * 0.8, 1.0);
    color = clamp(color, 0.0, 1.0);
    gl_Position = matrix * vertex;
}
