#version 330 core

layout(location = 0) in vec3 coord3d;

uniform mat4 rotate;

void main(void) {
	gl_Position = rotate * vec4(coord3d, 1.0);
}
