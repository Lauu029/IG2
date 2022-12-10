#version 330 core
in vec4 vertex; // atributos de los vértices a procesar
in vec3 normal;
in vec2 uv0; // coordenadas de textura 0

out vec2 vUv0; // out del vertex shader
out vec3 vFrontColor; // color rgb de la iluminación de la cara front
out vec3 vBackColor;

uniform mat4 modelViewProjMat; // constante de programa
uniform mat4 modelViewMat; // View*Model matrix
uniform mat4 normalMat;
uniform vec3 lightDiffuse;
uniform vec4 lightPosition;
uniform vec3 materialDiffuseFront;
uniform vec3 materialDiffuseBack;

float diff(vec3 cVertex, vec3 cNormal)
{
    vec3 lightDir = lightPosition.xyz; 
    if (lightPosition.w == 1)
        lightDir = lightPosition.xyz - cVertex;

    return max(dot(cNormal, normalize(lightDir)), 0.0); // dot: coseno ángulo

}

void main() {

    //diffuse en view space
    vec3 viewVertex = vec3(modelViewMat * vertex);
    vec3 viewNormal = normalize(vec3(normalMat * vec4(normal,0)));
    
    vec3 diffuseFront = diff(viewVertex, viewNormal) * lightDiffuse*materialDiffuseFront;
    vFrontColor =diffuseFront; // + specular

    vec3 diffuseBack = diff(viewVertex, -viewNormal) * lightDiffuse *materialDiffuseBack;
    vBackColor = diffuseBack; // + specular

    vUv0 = uv0;
    gl_Position = modelViewProjMat * vertex; //obligatorio

}
