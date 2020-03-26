#version 450 core

layout (location = 0) in vec3 in_pos;

uniform mat4 view;

out vec2 ex_pos;

void main() {
    gl_Position = vec4(in_pos, 1.0);
    ex_pos = vec2(view * vec4(in_pos, 1.0));
}
