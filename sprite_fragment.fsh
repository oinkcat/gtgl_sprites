uniform sampler2D u_texture;
uniform bool u_keyed;

in vec2 v_texcoord;

out vec4 out_color;

void main(void)
{
    vec4 tex_color = texture2D(u_texture, v_texcoord.xy);
    vec4 final_color = u_keyed
            ? (tex_color.xyz == vec3(1.0f, 0.0f, 1.0f) ? vec4(0.0f) : tex_color)
            : tex_color;

    out_color = final_color;
}
