#version 330 core

out vec4 FragColor;

// Recibimos las coordenadas de textura desde el Vertex Shader
in vec2 TexCoords;

uniform sampler2D texture_diffuse; 

void main()
{
    
    vec4 texColor = texture(texture_diffuse, TexCoords);

    // Si la textura tiene transparencia, descartamos esos píxeles
    if(texColor.a < 0.1)
        discard;

    FragColor = texColor;
}