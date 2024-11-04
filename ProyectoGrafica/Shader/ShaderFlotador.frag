#version 330 core
out vec4 FragColor;

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

uniform sampler2D diffuseTexture;
uniform float time;

void main()
{
    // Dirección de luz desde arriba
    vec3 lightDir = normalize(vec3(0.0, 1.0, 0.0));
    
    // Cálculo de iluminación difusa
    float diff = max(dot(normalize(Normal), lightDir), 0.0);
    
    // Color base de la textura
    vec4 texColor = texture(diffuseTexture, TexCoords);
    
    // Cálculo de iluminación especular simple
    vec3 viewDir = normalize(-FragPos);
    vec3 reflectDir = reflect(-lightDir, normalize(Normal));
    float spec = pow(max(dot(viewDir, reflectDir), 0.0), 16.0);
    
    // Color final
    vec3 ambient = texColor.rgb * 0.3;
    vec3 diffuse = texColor.rgb * diff * 0.7;
    vec3 specular = vec3(0.3) * spec;
    
    vec3 finalColor = ambient + diffuse + specular;
    
    FragColor = vec4(finalColor, 1.0);
}