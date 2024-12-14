#version 460 core

layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;
layout (location = 3) in vec3 aTangent;
layout (location = 4) in vec3 aBiTangent;

out vec2 TexCoords;
out vec3 Normal;
out vec3 Tangent;
out vec3 BiTangent;
out mat3 TBNMatrix;
out vec3 FragPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    FragPos = vec3(model * vec4(aPos, 1.0));
    TexCoords = aTexCoords;
    
    mat3 normalMatrix = transpose(inverse(mat3(model)));
    Normal = normalMatrix * aNormal;
    Tangent = normalMatrix * aTangent;
    BiTangent = normalMatrix * aBiTangent;

    BiTangent = normalize(BiTangent - dot(BiTangent, Normal) * Normal);
    TBNMatrix = mat3(Tangent, BiTangent, Normal);

    gl_Position = projection * view * model * vec4(aPos, 1.0);
}