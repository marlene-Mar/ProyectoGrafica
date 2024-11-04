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
uniform float time; //Tiempo usado para animar el movimiento

void main()
{
    // Movimiento sinusoidal del flotador
    vec3 pos = aPos; // Copia la posición del vértice original
    float flot = sin(time * 1.0 + pos.x * 2.0 + pos.z * 2.0) * 0.05; // Movimiento sinusoidal en función del tiempo y posición
    pos.y += flot;  // Movimiento vertical sinusoidal

    //Desplazamiento lineal en z
    pos.z += sin(time) * 0.5; // Modifica la posición en z para generar un movimiento adelante y atrás
    
    // Pasar coordenadas de textura sin modificación adicional
    TexCoords = aTexCoords;

    // Calcular normal basada en el movimiento sinusoidal
    Normal = normalize(aNormal + vec3(0.0, flot, 0.0)); // Modifica la normal con el movimiento sinusoidal en y
    
    // Calcular posición final
    FragPos = vec3(model * vec4(pos, 1.0)); // Transforma la posición ajustada por el movimiento al espacio
    Normal = mat3(transpose(inverse(model))) * Normal; // Ajustar la normal al espacio usando la matriz de transformación del modelo
    gl_Position = projection * view * model * vec4(pos, 1.0); // Transforma la posición final del vértice a espacio de pantalla
}
