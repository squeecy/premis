#version 330 core


layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aColor;

out vec3 color;


uniform float scale;

uniform mat4 model_pitch;
uniform mat4 model_roll;
uniform mat4 view;
uniform mat4 proj;

void main()
{
	gl_Position = proj * view * model_pitch * model_roll * vec4(aPos, 1.0);

	color = aColor;
}
