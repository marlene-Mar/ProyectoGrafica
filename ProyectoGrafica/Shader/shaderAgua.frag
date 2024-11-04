#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform sampler2D diffuseTexture; // Textura del agua
uniform float time; //Tiempo para animar el movimeinto
uniform bool transparency; // Variable de control para activar o desactivar transparencia

void main()
{
    // Coordenadas de textura con distorsión
    vec2 distortedTexCoords = TexCoords;
    distortedTexCoords.x += sin(TexCoords.y * 10.0 + time) * 0.01;
    distortedTexCoords.y += cos(TexCoords.x * 10.0 + time) * 0.01;
    
    // Obtener color de la textura
    vec4 texColor = texture(diffuseTexture, distortedTexCoords);
    
    // Efecto de brillo basado en la normal
    vec3 lightDir = normalize(vec3(0.0, 1.0, 0.0));
    float diff = max(dot(Normal, lightDir), 0.0);
    
    // Color base del agua
    vec3 waterColor = vec3(0.0, 0.4, 0.8);
    
    // Mezclar textura con color base del agua
    vec3 finalColor = mix(texColor.rgb, waterColor, 0.3);
    
    // Añadir brillo
    finalColor += diff * vec3(0.2);
    
    // Efecto de brillos especulares simples
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, Normal);
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 32.0);
    finalColor += spec * vec3(0.3);
    
    // Aplicar transparencia
    float alpha = transparency ? 0.8 : 1.0;
    
    // Asignar el color final al fragmento con el valor de alfa para la transparencia
    FragColor = vec4(finalColor, alpha);
}
