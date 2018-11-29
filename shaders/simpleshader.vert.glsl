#version 330 core

uniform mat4 rotate;

layout(location = 0) in vec3 pos;
layout(location = 1) in vec3 vertex_color;

out vec3 fragment_color;

void main(void) {
	gl_Position = rotate * vec4(pos, 1.0);
	fragment_color = vertex_color;
}
