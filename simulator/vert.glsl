#version 330 core
layout(location=0) in vec2 in_pos;

uniform mat4 trans;

void main()
{
    gl_Position = trans * vec4(in_pos, 0.0, 1.0);
}
