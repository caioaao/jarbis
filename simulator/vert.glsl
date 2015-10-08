#version 330 core
layout(location=0) in vec2 in_pos;
uniform mat3 mvp;
vec3 pos_2d;

void main()
{
    pos_2d = transpose(mvp) * vec3(in_pos, 1.);
    gl_Position = vec4(pos_2d[0], pos_2d[1], 0, pos_2d[2]);
}
