#version 330 core
in vec4 vertex;
in vec2 uv0;
uniform mat4 modelViewProjMat;
out vec2 vUv0;
out vec2 vUv1;

void main(){
    vUv0=uv0;
    float ZF = 0.5;    
    vUv1.s=(uv0.s-0.5)*ZF+0.5;
    vUv1.t=(uv0.t-0.5)*ZF+0.5;
    gl_Position= modelViewProjMat*vertex;
}