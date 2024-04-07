#shader vertex
#version 330 core

layout(location = 0)in vec3 position;

out vec3 vColor;

uniform mat4 u_MVP;

void main()
{
	gl_Position = u_MVP * vec4(position, 1.0);
	vColor = position+0.5;
};

#shader fragment
#version 330 core

layout(location = 0)out vec4 color;

in vec3 vColor;

void main()
{
	color = vec4(vColor.r, vColor.g, vColor.b, 1.0);
};