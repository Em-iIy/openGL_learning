#version 330 core
out vec4 FragColor;

in vec3 color;
in vec2 tex;
in vec3 normal;
in vec3 fragPos;

// uniform sampler2D texture1;
// uniform sampler2D texture2;

uniform vec3 objectColor;
uniform vec3 lightColor;
uniform vec3 lightPos;

void main()
{
   float ambientStrenght = 0.1;
   vec3 ambient = ambientStrenght * lightColor;

   vec3 norm = normalize(normal);
   vec3 lightDir = normalize(lightPos - fragPos);
   float diff = max(dot(norm, lightDir), 0.0);
   vec3 diffuse = diff * lightColor;


   vec3 result = (ambient + diffuse) * objectColor;
   // FragColor = mix(texture(texture1, tex), texture(texture2, tex), 0.5), vec4(color, 1.0);
   FragColor = vec4(result, 1.0);
}