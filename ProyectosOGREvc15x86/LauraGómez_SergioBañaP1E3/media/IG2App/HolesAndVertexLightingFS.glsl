#version 330 core
in vec2 vUv0; // out del vertex shader
in vec3 vFrontColor; // color de la iluminación interpolado
in vec3 vBackColor;

out vec4 fFragColor; // out del fragment shader

uniform sampler2D texturaMetal; // tipo sampler2D para texturas 2D checker
uniform sampler2D texturaStones; // ‐> unidades de textura (int) space
uniform sampler2D texturaCorrosion; // ‐> unidades de textura (int) metal

void main() {

    vec3 colorMetal = vec3(texture(texturaMetal, vUv0)); // acceso a téxel
    vec3 colorStones = vec3(texture(texturaStones, vUv0)); // acceso a téxel
    vec3 colorCorrosion = vec3(texture(texturaCorrosion, vUv0)); // acceso a téxel

    vec3 color;

    if(gl_FrontFacing) color = colorMetal.rgb * vFrontColor;
    else color = colorStones.rgb * vBackColor;

    if(colorCorrosion.r > 0.6) discard; //El fragmento queda descartado y no seguirá el proceso de renderizado (efecto return)

    fFragColor = vec4(color, 1.0); // out

}