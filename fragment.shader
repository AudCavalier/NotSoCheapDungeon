#version 330 core
out vec4 FragColor;
in vec2 UV;
in vec4 Vcolor;

uniform sampler2D tex;

void main(){
    FragColor = mix(texture(tex, UV), Vcolor, 0.2);
}