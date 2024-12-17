#version 460 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

vec3 FragPos;
vec3 Normal;
vec2 TexCoords;
vec4 FragPosLightSpace;

uniform mat4 projection;
uniform mat4 view;
uniform mat4 model;
uniform mat4 lightSpaceMatrix;

void main() {
	FragPos = vec3(model * vec4(aPos, 1.0));
	Normal = transpose(inverse(mat3(model))) * aNormal;
	TexCoords = aTexCoords;
	FragPosLightSpace = lightSpaceMatrix * vec4(FragPos, 1.0);
	gl_Position = lightSpaceMatrix * model * vec4(FragPos, 1.0);
}