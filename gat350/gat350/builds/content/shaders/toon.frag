#version 430
	
in vec3 fposition;
in vec3 fnormal;

out vec4 color;

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
uniform int steps = 4;

float scale = 1.0 / steps;

vec3 toon(vec3 position, vec3 normal)
{
	vec3 position_to_light = normalize(vec3(light.position) - position);

	//diffuse
	float lDotN = max(0.0, dot(position_to_light, normal));
	vec3 diffuse = light.diffuse * material.diffuse * floor(lDotN * steps) * scale;

	return diffuse;
}

void main()
{

	//ambient. all lights have highlights and less intense lights. the ambience of the light applies to all the scene, without regards to the view
	vec3 ambient = light.ambient * material.ambient;

	// diffuse
	vec3 diffuse = toon(fposition, fnormal);



	color = vec4(ambient + diffuse, 1.0);
}
