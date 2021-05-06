#version 330 core

layout (location = 0) out vec4 color;

uniform sampler2D tex_id;

in DATA {
    vec2 uv;
    float faceLightningLevel;
    float visibillity;
} fragments_in;


const vec4 fogColor = vec4(67.f/255.f, 82.f/255.f, 100.f/255.f, 1.0);
//const vec4 fogColor = vec4(1.0f, 1.0f, 1.0f, 1.0f);

void main() {
    color = texture(tex_id, fragments_in.uv) * vec4(fragments_in.faceLightningLevel, fragments_in.faceLightningLevel, fragments_in.faceLightningLevel, 1.0f);

    color = mix(fogColor, color, fragments_in.visibillity);
}