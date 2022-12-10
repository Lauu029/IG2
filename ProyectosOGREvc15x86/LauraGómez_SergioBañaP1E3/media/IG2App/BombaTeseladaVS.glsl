#version 330 core

in vec4 vertex;
in vec2 uv0;

uniform float sintime;

uniform mat4 modelViewProjectionMatrix;

out vec2 vUv0;
out vec2 vUv1;

void main(void) {
    vUv0 = uv0;
    vUv1 = uv0;

    float ZF = sintime * 0.25 + 0.75;

    vUv1.s = (vUv0.s - 0.5) * ZF + 0.5;
    vUv1.t = (vUv0.t - 0.5) * ZF + 0.5;

    gl_Position = modelViewProjectionMatrix * vertex;
}