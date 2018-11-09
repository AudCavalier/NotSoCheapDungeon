#version 330 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec2 vertexUV;
layout (location = 2) in vec3 colors;

out vec2 UV;
out vec2 TexCoord;
out vec4 Vcolor;

void main(){
    gl_Position = vec4(aPos, 1.0);
    UV = vertexUV;
    Vcolor = vec4(colors.xyz, 1.0);
}