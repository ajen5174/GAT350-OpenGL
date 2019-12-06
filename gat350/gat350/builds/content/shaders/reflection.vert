#version 430
	
layout (location = 0) in vec3 vposition;
layout (location = 1) in vec3 vnormal;

out vec3 freflection;
out vec3 frefraction;

uniform float index;

uniform vec3 camera_position;
uniform mat4 model_matrix;
uniform mat4 mvp_matrix;


void main()
{

	vec3 position = vec3(model_matrix * vec4(vposition, 1.0));
	vec3 normal = vec3(model_matrix * vec4(vnormal, 1.0));

	vec3 view = normalize(camera_position - position);

	freflection = reflect(-view, normal);
	frefraction = refract(-view, normal, index);

	gl_Position = mvp_matrix * vec4(vposition, 1.0);

}
