#version 430
	
in vec3 fcolor;
out vec4 color;
	
void main()
{
	color = vec4(fcolor, 1.0);
}
