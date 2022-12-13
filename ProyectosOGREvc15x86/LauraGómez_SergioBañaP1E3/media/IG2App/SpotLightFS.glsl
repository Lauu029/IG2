#version 330 core

in vec2 vUv0;
in vec3 vWorldNormal;
in vec4 vWorldVertex; 
out vec4 fFragColor;

uniform sampler2D textureS;

uniform mat4 worldMat;
uniform mat4 normalMat;

uniform vec4 lightPosition;
uniform float cutoff;

void main(void) {
    vec3 texture = vec3(texture(textureS, vUv0));

    vec3 worldVertex = vec3(worldMat * vWorldVertex);
    vec3 worldNormal = normalize(vec3(normalMat * vec4(vWorldNormal,0)));

    vec3 color = texture;
    if (dot(worldNormal, normalize(worldVertex - vec3(vec3(lightPosition)))) < cutoff * 0.15 + 0.85)
    {
        color = texture * 0.2;   
    }  

    fFragColor = vec4(color, 1.0);
}