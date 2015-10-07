#version 330 core
uniform vec3 triang_color;

out vec4 color;

void main() {
    color = vec4(triang_color, 1);
}
