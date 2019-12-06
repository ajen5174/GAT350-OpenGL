#version 430
	
layout (location = 0) in vec3 vposition;

out vec3 ftexcoord;

uniform mat4 view_matrix;
uniform mat4 projection_matrix;
	
void main()
{
	ftexcoord = vposition;

	gl_Position = projection_matrix * view_matrix * vec4(vposition, 1.0);

}
