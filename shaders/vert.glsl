#version 450

layout (location = 0) in vec2 position;
uniform mat4 matrix;

void main() {
    gl_Position = matrix * vec4(position, 0, 1);
}