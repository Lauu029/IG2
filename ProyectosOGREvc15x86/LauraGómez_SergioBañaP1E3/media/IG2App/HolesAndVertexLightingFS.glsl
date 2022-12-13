#version 330 core
in vec2 vUv0; 
in vec3 vFrontColor; 
in vec3 vBackColor;

out vec4 fFragColor; // out del fragment shader

uniform sampler2D texturaM; 
uniform sampler2D texturaS; 
uniform sampler2D texturaC; 

void main() {

    vec3 colorMetal = vec3(texture(texturaM, vUv0)); 
    vec3 colorStones = vec3(texture(texturaS, vUv0)); 
    vec3 colorCorrosion = vec3(texture(texturaC, vUv0));

    vec3 color;

    if(gl_FrontFacing) color = colorMetal.rgb * vFrontColor;
    else color = colorStones.rgb * vBackColor;

    if(colorCorrosion.r > 0.6) discard; //El fragmento queda descartado y no seguirá el proceso de renderizado (efecto return)

    fFragColor = vec4(color, 1.0); // out

}