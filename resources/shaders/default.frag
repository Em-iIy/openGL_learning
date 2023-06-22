#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 tex;

uniform sampler2D texture1;
uniform sampler2D texture2;

void main()
{
   // FragColor = texture(texture1, tex);
   FragColor = mix(texture(texture1, tex), texture(texture2, tex), 0.5), vec4(color, 1.0);
   // FragColor = vec4(color, 1.0);
}