#version 330 core

in vec2 vUv0;
uniform sampler2D texturaS;
uniform sampler2D texturaM;
uniform sampler2D texturaC;

out vec4 fFragColor;

void main(){
    vec3 colorSpace= vec3(texture(texturaS, vUv0));
    vec3 colorMetal= vec3(texture(texturaM, vUv0));
    vec3 colorChecker= vec3(texture(texturaC,vUv0));

if(colorChecker==vec3(1.0,1.0,1.0)){
       fFragColor= vec4(0.0,1.0,0.0,1.0);
}
    else{
       fFragColor=vec4(1.0,0.0,0.0,1.0);
    }
    //fFragColor=vec4(0.0,1.0,0.0,1.0);
}