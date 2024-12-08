#version 330 core

out vec4 FragColor;
in vec3 arrowColor;

void main() {
    FragColor = vec4(arrowColor, 1.0);
}
