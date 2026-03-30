#version 330 core
// El layout 0 es la posición (ya lo tienes)
layout (location = 0) in vec3 position;
// El layout 2 suele ser donde la clase Model.h guarda las coordenadas de textura (UVs)
layout (location = 2) in vec2 texCoords; 

// Declaramos la variable de salida hacia el Fragment Shader
out vec2 TexCoords;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
    gl_Position = projection * view * model * vec4(position, 1.0f);
    
    // Pasamos las coordenadas del modelo al Fragment Shader
    TexCoords = texCoords;
}