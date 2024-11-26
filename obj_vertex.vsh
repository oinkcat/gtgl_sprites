#version 150

uniform vec3 u_light;
uniform mat4 u_mvp;

in vec3 a_pos;
in vec3 a_normal;
in vec3 a_color;

out vec3 v_pos;
out vec3 v_normal;
out vec3 v_color;
out vec3 v_light;

void main(void)
{
    v_pos = a_pos;
    v_normal = a_normal;
    v_color = a_color;
    v_light = u_light;

    gl_Position = u_mvp * vec4(a_pos, 1.0f);
}
