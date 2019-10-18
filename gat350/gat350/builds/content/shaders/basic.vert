#version 430
	
layout (location = 0) in vec3 vposition;
layout (location = 1) in vec3 vcolor;

out vec3 fcolor;
uniform mat4 mx;
	
void main()
{
	fcolor = vcolor;
	gl_Position = mx * vec4(vposition, 1.0);

}
