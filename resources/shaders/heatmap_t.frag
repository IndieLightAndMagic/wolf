#version 120
varying vec4 color;
varying vec2 texcoordout;
//uniform sampler2D court_texture;

void main(void)
{
	gl_FragColor = vec4(texcoordout.x, 0.0, 1.0 - texcoordout.x, 0.0);
	//gl_FragColor = texture2D(court_texture, texcoordout);
}