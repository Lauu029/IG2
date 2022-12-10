#version 330 core

uniform float ZF;
uniform float sintime;
in vec4 vertex;
in vec2 uv0;
uniform mat4 modelViewProjectionMatrix;
out vec2 vUv0;
out vec2 vUv1;

void main(){
    vUv0 = uv0;
    vUv1 = uv0;

    float ZFF = sintime * 0.25 + 0.75;

    vUv1.s=(uv0.s-0.5)*ZFF+0.5;
    vUv1.t=(uv0.t-0.5)*ZFF+0.5;

    gl_Position= modelViewProjectionMatrix*vertex;
}