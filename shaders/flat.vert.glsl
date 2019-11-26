#version 330 core

uniform mat4 flat_trans;

layout(location = 0) in vec3 flat_pos;
layout(location = 1) in vec3 flat_vertex_color;

out vec3 flat_fragment_color;

void main(void) {
    gl_Position = flat_trans * vec4(flat_pos, 1.0);
    flat_fragment_color = flat_vertex_color;
}
