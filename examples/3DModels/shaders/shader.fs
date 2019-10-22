#version 330 core

out vec4 FragColor;

in vec2 vTexCoords;

uniform sampler2D tex_diff1;
uniform bool isModel = false;
uniform bool isCubeMap = false;

void main() {
    vec4 texColor = texture(tex_diff1, vTexCoords);
    if(!isModel && texColor.a < 0.1f)
        discard;
    FragColor = texColor;
}