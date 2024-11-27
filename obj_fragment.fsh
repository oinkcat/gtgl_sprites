#version 150

in vec3 v_pos;
in vec3 v_normal;
in vec3 v_color;
in vec3 v_light;

out vec4 out_color;

const float AMBIENT_INTENSITY = 0.2f;
const float MAX_DISTANCE = 10.0f;

void main(void)
{
    float light_dist = length(v_pos - v_light);
    vec3 norm_light = normalize(v_light);

    float light_intensity = dot(v_normal, norm_light)
                            * (1 - pow(light_dist / MAX_DISTANCE, 2));

    float light_intens_w_ambient = max(AMBIENT_INTENSITY, light_intensity);

    out_color = vec4(v_color * light_intens_w_ambient, 1.0f);
}
