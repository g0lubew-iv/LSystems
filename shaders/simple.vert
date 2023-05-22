#version 330 core

layout(location = 0) in vec3 position;

layout(std140, binding = 0) uniform matrices {
    mat4 view;
    mat4 projection;
};

void main() {
    gl_Position = projection * view * vec4(position, 1);
}