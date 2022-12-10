#version 330 core

uniform sampler2D texFront;
uniform sampler2D texBack; 
uniform sampler2D texturaX;

in vec2 vUv0; // out del vertex shader
out vec4 fFragColor; // out del fragment shader

void main() {
	vec3 colorStones = vec3(texture(texBack, vUv0)); 
    vec3 colorMetal = vec3(texture(texFront, vUv0)); 
    vec3 colorCorrosion = vec3(texture(texturaX, vUv0)); 
	
	if(colorCorrosion.r <= 0.6){
		if(gl_FrontFacing)
            fFragColor = vec4(colorMetal, 1.0);
        else
            fFragColor = vec4(colorStones, 1.0);
	}
	else
		discard;
}