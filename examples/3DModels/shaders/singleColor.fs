#version 330 core

out vec4 FragColor;

in vec2 vTexCoords;

uniform sampler2D tex_diff1;

void main() {
    FragColor = vec4(0.04f, 0.28f, 0.26f, 1.0f);
}