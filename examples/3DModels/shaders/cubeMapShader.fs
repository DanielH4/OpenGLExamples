#version 330 core
out vec4 FragColor;

in vec3 texCoords;              //based on the input positions of the vertex shader.

uniform samplerCube skyBox;

void main() {
    FragColor = texture(skyBox, texCoords);
}