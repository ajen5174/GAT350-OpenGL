#version 430
	
layout (location = 0) in vec3 vposition;
layout (location = 1) in vec3 vnormal;

out vec3 fcolor;

uniform vec3 ambient;
uniform vec4 light_position;
uniform mat4 mvp_matrix;
uniform mat4 model_view_matrix;
	
void main()
{
	vec3 normal = normalize(mat3(model_view_matrix) * vnormal);
	vec4 position = model_view_matrix * vec4(vposition, 1.0);
	vec3 position_to_light = normalize(vec3(light_position - position));

	float intensity = max(0.0, dot(normal, position_to_light));


	fcolor = ambient + intensity * vec3(0.1, 0.0, 0.1);
	gl_Position = mvp_matrix * vec4(vposition, 1.0);
	
}
