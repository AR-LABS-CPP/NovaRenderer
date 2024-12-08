#version 330 core

layout(lines) in; // Input type: a pair of vertices (for a line)
layout(triangle_strip, max_vertices = 4) out; // Output type: a quad (two triangles)

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main() {
    float lineWidth = 0.05; // Thickness of the line (adjust as needed)

    vec4 p0 = gl_in[0].gl_Position; // First point (start of the line)
    vec4 p1 = gl_in[1].gl_Position; // Second point (end of the line)

    // Direction vector of the line
    vec2 dir = p1.xy - p0.xy;
    vec3 normal = normalize(vec3(-dir.y, dir.x, 0.0)) * lineWidth; // Make the normal a vec3

    // Emit the vertices for the quad (thick line)
    gl_Position = projection * view * model * vec4(p0.xyz + normal, 1.0); // First vertex
    EmitVertex();
    
    gl_Position = projection * view * model * vec4(p0.xyz - normal, 1.0); // Second vertex
    EmitVertex();
    
    gl_Position = projection * view * model * vec4(p1.xyz + normal, 1.0); // Third vertex
    EmitVertex();
    
    gl_Position = projection * view * model * vec4(p1.xyz - normal, 1.0); // Fourth vertex
    EmitVertex();

    EndPrimitive();
}