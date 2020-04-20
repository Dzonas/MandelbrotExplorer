#version 450 core

in vec2 ex_pos;
out vec4 frag_color;

uniform vec3 colormap[16];
uniform uint iterations;

vec2 multiply(vec2 a, vec2 b) {
    float k1 = b.x * (a.x + a.y);
    float k2 = a.x * (b.y - b.x);
    float k3 = a.y * (b.x + b.y);
    return vec2(k1 - k3, k1 + k2);
}

void main() {
    uint i = 0;
    vec2 z = vec2(0.0, 0.0);

    while (z.x * z.x + z.y * z.y < 4.0 && i < iterations) {
        z = multiply(z, z) + ex_pos;
        i++;
    }

    if(i == 100) {
        frag_color = vec4(0.0, 0.0, 0.0, 1.0);
    } else {
        uint j = i % 16;
        frag_color = vec4(colormap[j], 1.0);
    }
}
