#version 430

layout (location = 0) in vec3 vposition;
layout (location = 3) in vec2 vtexcoord;

out vec2 ftexcoord;

void main()
{
	ftexcoord = vtexcoord;
	vec3 position = (vposition * 0.5);
   	gl_Position = vec4(position, 1.0);
}
