#version 150

uniform mat4 u_mvp;

in vec2 a_pos;
in vec2 a_texcoord;

out vec2 v_texcoord;

void main(void)
{
    vec4 pos = vec4(a_pos.xy, 0.0f, 1.0f);
    gl_Position = u_mvp * pos;

    v_texcoord = a_texcoord;
}
