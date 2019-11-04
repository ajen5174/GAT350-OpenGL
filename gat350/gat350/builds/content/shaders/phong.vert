#version 430
	
layout (location = 0) in vec3 vposition;
layout (location = 1) in vec3 vnormal;

out vec3 fposition;
out vec3 fnormal;

struct material_s
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess; 
};

uniform material_s material;

struct light_s
{
	vec4 position;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
};

uniform light_s light;

uniform mat4 mvp_matrix;
uniform mat4 model_view_matrix;
	
void main()
{
	fnormal = normalize(mat3(model_view_matrix) * vnormal);
	fposition = vec3(model_view_matrix * vec4(vposition, 1.0));




	gl_Position = mvp_matrix * vec4(vposition, 1.0);
	
}
