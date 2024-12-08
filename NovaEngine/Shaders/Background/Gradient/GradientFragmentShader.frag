#version 330 core
out vec4 FragColor;

in vec3 TexCoords;

uniform vec3 topColor;
uniform vec3 bottomColor;

void main() {
	float mixFactor = 0.5;
	FragColor = vec4(mix(bottomColor, topColor, mixFactor), 1.0);
}