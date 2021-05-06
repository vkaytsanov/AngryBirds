#version 330 core

layout (location = 0) in vec3 position;
layout (location = 1) in vec2 uv;
layout (location = 2) in uint faceLightningLevel;

out DATA{
    vec2 uv;
    float faceLightningLevel;
    float visibillity;
} vertices_out;

// Camera Matrices
uniform mat4 viewMatrix;
uniform mat4 projMatrix;

uniform int CHUNK_SIZE_X;
uniform int CHUNK_SIZE_Z;
uniform int chunkX;
uniform int chunkZ;

uniform int renderDistance;

const float fog_density = 0.01f;
float fog_gradient = float(renderDistance + 1.0f);

void main(){
    // real position of the chunk
    vec3 world_position = vec3(position.x + chunkX * CHUNK_SIZE_X, position.y, position.z + chunkZ * CHUNK_SIZE_Z);

    // fog
    vec4 relative_camera_pos = viewMatrix * vec4(world_position, 1.0f);
    float fog_distance = length(relative_camera_pos) + 1.0f;
    vertices_out.visibillity = exp(-pow((fog_distance * fog_density), fog_gradient));
    vertices_out.visibillity = clamp(vertices_out.visibillity, 0.0f, 1.0f);

    // light on the face of the cube, varies between 3-10 and is 1 byte
    float light = float(faceLightningLevel);
    light /= 10.0f;

    vertices_out.uv = uv;
    vertices_out.faceLightningLevel = light;

    gl_Position = projMatrix * viewMatrix * vec4(world_position, 1.0);
}