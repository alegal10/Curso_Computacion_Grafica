#version 330 core

in vec2 TexCoords;
out vec4 FragColor;

uniform sampler2D texture_diffuse1;  

void main()
{
     //FragColor = vec4(1.0f);
     FragColor = texture(texture_diffuse1, TexCoords);
}