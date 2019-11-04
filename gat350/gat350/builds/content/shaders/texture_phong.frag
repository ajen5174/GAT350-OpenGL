#version 430
	
in vec3 fposition;
in vec3 fnormal;
in vec2 ftexcoord;

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
layout (binding = 0) uniform sampler2D texture_sample;

void main()
{
	vec3 position_to_light = normalize(vec3(light.position) - fposition);

	//ambient. all lights have highlights and less intense lights. the ambience of the light applies to all the scene, without regards to the view
	vec3 ambient = light.ambient * material.ambient;

	//diffuse. this is the light applying to objects while taking into account the faces facing the light, simply makes things facing away from the light darker than things that face the light.
	float lDotN = max(0.0, dot(position_to_light, fnormal));
	vec3 diffuse = light.diffuse * material.diffuse * lDotN;

	//specular. this creates the highlight effect
	vec3 specular = vec3(0.0);
	if(lDotN > 0.0)
	{
		vec3 position_to_view = normalize(-fposition.xyz);
		vec3 light_reflect = reflect(-position_to_light, fnormal);
		float intensity = max(0.0, dot(position_to_view, light_reflect));
		intensity = pow(intensity, material.shininess);
		specular = light.specular * material.specular * intensity;

	}

	color = vec4(ambient + diffuse, 1.0f) * texture(texture_sample, ftexcoord) + vec4(specular, 1.0f);
//	color = vec4(ambient + diffuse + specular, 1.0);
}
