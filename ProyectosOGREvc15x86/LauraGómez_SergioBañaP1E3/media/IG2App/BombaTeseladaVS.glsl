#version 330 core

in vec4 vertex;
in vec2 uv0;
uniform mat4 modelViewProjectionMatrix;
out vec2 vUv0;

void main(void) {
    vUv0=uv0;
    gl_Position = modelViewProjectionMatrix * vertex;
}