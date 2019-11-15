#version 430
	
layout (location = 0) in vec3 vposition;

out vec3 fcolor;

struct material_s
{
	vec4 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform material_s material;
uniform mat4 mvp_matrix;
	
void main()
{
	fcolor = material.diffuse;
	gl_Position = mvp_matrix * vec4(vposition, 1.0);
}
