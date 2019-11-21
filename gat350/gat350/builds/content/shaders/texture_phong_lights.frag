#version 430
#define POINT		0
#define DIRECTION	1
#define SPOTLIGHT	2
#define MAX_LIGHTS  5


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
	int type;
	vec4 position;
	vec3 direction;
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float cutoff;
	float exponent;
};

uniform light_s lights[MAX_LIGHTS];
layout (binding = 0) uniform sampler2D texture_sample;

void phong(light_s in_light, vec3 position, vec3 normal, out vec3 ambient, out vec3 diffuse, out vec3 specular)
{
	vec3 position_to_light;
	if(in_light.type == POINT || in_light.type == SPOTLIGHT) position_to_light = normalize(vec3(in_light.position) - position);
	else if(in_light.type == DIRECTION) position_to_light = normalize(-in_light.direction);

	//ambient. all lights have highlights and less intense lights. the ambience of the light applies to all the scene, without regards to the view
	ambient = in_light.ambient * material.ambient;


	diffuse = vec3(0.0);
	specular = vec3(0.0);

	float spot_intensity = 1.0;
	
	if(in_light.type == SPOTLIGHT)
	{
		float cos_angle = dot(in_light.direction, -position_to_light);
		float angle = acos(cos_angle);

		if(angle > in_light.cutoff) return;
		spot_intensity = pow(cos_angle, in_light.exponent);
	}

	//diffuse. this is the light applying to objects while taking into account the faces facing the light, simply makes things facing away from the light darker than things that face the light.
	float lDotN = max(0.0, dot(position_to_light, normal));
	diffuse = ((in_light.diffuse * material.diffuse) * lDotN) * spot_intensity;

	//specular. this creates the highlight effect
	specular = vec3(0.0);
	if(lDotN > 0.0)
	{
		vec3 position_to_view = normalize(-position.xyz);
		vec3 light_reflect = reflect(-position_to_light, normal);
		float intensity = max(0.0, dot(position_to_view, light_reflect));
		intensity = pow(intensity, material.shininess);
		specular = (in_light.specular * material.specular * intensity) * spot_intensity;

	}

}


void main()
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;

	for(int i = 0; i < MAX_LIGHTS; i++)
	{
		vec3 a;
		vec3 d;
		vec3 s;

		phong(lights[i], fposition, fnormal, a, d, s);
		ambient = ambient + a;
		diffuse = diffuse + d;
		specular = specular + s;

	}

	color = vec4(ambient + diffuse, 1.0f) * texture(texture_sample, ftexcoord) + vec4(specular, 1.0f);
}
