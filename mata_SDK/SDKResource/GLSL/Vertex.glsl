#version 460 core

layout(location = 0) in vec3 InputPosition;
layout(location = 2) in vec2 VTextureCoord;

out vec3     FragPosition;
out vec2     TextureCoord;

uniform mat4 ViewMatrix;
uniform mat4 ProjectionMatrix;

layout (std430, binding = 1) buffer MatrixOutput {
    mat4 Result;
};

void main() {
    gl_Position = ProjectionMatrix * ViewMatrix * Result * vec4(InputPosition, 1.0);
    FragPosition = vec3(Result * vec4(InputPosition, 1.0));
    TextureCoord = VTextureCoord;
}