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
uniform vec3 viewPos;

void main()
{
   float ambientStrenght = 0.1;
   float specularStrength = 0.5;
   vec3 ambient = ambientStrenght * lightColor;

   vec3 norm = normalize(normal);

   vec3 lightDir = normalize(lightPos - fragPos);
   vec3 viewDir = normalize(viewPos - fragPos);
   vec3 reflectDir = -lightDir - 2 * dot(norm, -lightDir) * norm;
   // vec3 reflectDir = reflect(-lightDir, norm);

   float diff = max(dot(norm, lightDir), 0.0);
   vec3 diffuse = diff * lightColor;

   float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);
   vec3 specular = specularStrength * spec * lightColor;

   vec3 result = (ambient + diffuse + specular) * objectColor;
   // FragColor = mix(texture(texture1, tex), texture(texture2, tex), 0.5), vec4(color, 1.0);
   FragColor = vec4(result, 1.0);
}