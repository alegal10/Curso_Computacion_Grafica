#version 330 core

struct Material {
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
    float shininess;
};

struct Light {
    vec3 position;
    vec3 ambient;
    vec3 diffuse;
    vec3 specular;
};

in vec3 FragPos;
in vec3 Normal;
in vec2 TexCoords;

out vec4 color;
uniform vec3 viewPos;
uniform Material material;
uniform Light light;
uniform sampler2D texture_diffuse; 

void main() {
    vec3 norm = normalize(Normal);
    vec3 viewDir = normalize(viewPos - FragPos);

    // --- CÁLCULO LUZ 1 ---
    vec3 lightDir1 = normalize(light.position - FragPos);
    float diff1 = max(dot(norm, lightDir1), 0.0);
    vec3 reflectDir1 = reflect(-lightDir1, norm);
    float spec1 = pow(max(dot(viewDir, reflectDir1), 0.0), material.shininess * 128.0f);
    
    vec3 ambient1  = light.ambient  * material.ambient;
    vec3 diffuse1  = light.diffuse  * (diff1 * material.diffuse);
    vec3 specular1 = light.specular * (spec1 * material.specular);

    // --- RESULTADO FINAL ---
    // Sumamos los componentes de ambas luces
    vec3 finalLight = (ambient1 + diffuse1 + specular1);
    // Multiplicamos por la textura del modelo
    color = vec4(finalLight, 1.0) * texture(texture_diffuse, TexCoords);  
}