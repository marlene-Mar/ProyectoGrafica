#version 330 core
layout (location = 0) in vec3 aPos;
layout (location = 1) in vec3 aNormal;
layout (location = 2) in vec2 aTexCoords;

out vec3 FragPos;
out vec3 Normal;
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;
uniform float time;

void main()
{
    // Movimiento sinusoidal del flotador
    vec3 pos = aPos;
    float flot = sin(time * 1.0 + pos.x * 2.0 + pos.z * 2.0) * 0.05;
    pos.y += flot;
    
    // Pasar coordenadas de textura sin modificar
    TexCoords = aTexCoords;
    // Desplazamiento de textura basado en el tiempo
    TexCoords.x += time * 0.05;
    TexCoords.y += time * 0.03;
    
    // Actualiza normal basada en la onda
    Normal = normalize(aNormal + vec3(0.0, flot, 0.0));
    
    // Calcular posición final
    FragPos = vec3(model * vec4(pos, 1.0));
    Normal = mat3(transpose(inverse(model))) * Normal;
    gl_Position = projection * view * model * vec4(pos, 1.0);
}