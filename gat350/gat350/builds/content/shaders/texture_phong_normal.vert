#version 430
	
layout (location = 0) in vec3 vposition;
layout (location = 1) in vec3 vnormal;
layout (location = 3) in vec2 vtexcoord;
layout (location = 5) in vec3 vtangent;

out vec3 fposition;
out vec3 fnormal;
out vec2 ftexcoord;
out mat3 ftbn_matrix;


uniform mat4 mvp_matrix;
uniform mat4 model_view_matrix;
	
void main()
{
	fposition = vec3(model_view_matrix * vec4(vposition, 1.0));
	ftexcoord = vtexcoord;

	fnormal = normalize(mat3(model_view_matrix) * vnormal);
	vec3 tangent = normalize(mat3(model_view_matrix) * vtangent);
	vec3 bitangent = normalize(cross(fnormal, tangent));

	ftbn_matrix = mat3(tangent, bitangent, fnormal);

	gl_Position = mvp_matrix * vec4(vposition, 1.0);
	
}
