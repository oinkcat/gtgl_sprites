uniform sampler2D u_texture;

in vec2 v_texcoord;

out vec4 out_color;

void main(void)
{
    out_color = texture2D(u_texture, v_texcoord.xy);
}
