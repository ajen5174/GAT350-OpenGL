#version 430
	
in vec3 ftexcoord;
out vec4 color;

layout (binding = 0) uniform samplerCube texture_sample;
	
void main()
{
	color = texture(texture_sample, ftexcoord);

}
