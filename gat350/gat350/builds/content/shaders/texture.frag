#version 430
	
in vec3 fcolor;
in vec2 ftexcoord;

out vec4 color;


layout (binding = 0) uniform sampler2D texture_sample1; //whatever texture is bound in main will be used here
layout (binding = 1) uniform sampler2D texture_sample2; 
	
void main()
{
	vec4 color1 = texture(texture_sample1, ftexcoord);
	vec4 color2 = texture(texture_sample2, ftexcoord);

	color = mix(color1, color2, 0.5);
	//color = texture(texture_sample1, ftexcoord) * vec4(fcolor, 1.0);


}
