#version 330 core

in vec4 vertex; 
in vec3 normal; 

in vec2 uv0; 
out vec2 vUv0; 
out vec3 vWorldNormal; 
out vec4 vWorldVertex; 

uniform mat4 modelViewProjMat; 

void main() {

    vUv0 = uv0; 

    vWorldNormal = normal;
    vWorldVertex = vertex;

    gl_Position = modelViewProjMat * vertex; 
                                            
}