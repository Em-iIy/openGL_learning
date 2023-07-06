#version 330 core

struct Material {
   sampler2D diffuse;
   sampler2D specular;
   float shininess;
};

struct Light {
   vec3 position;
   vec3 direction;
   
   vec3 ambient;
   vec3 diffuse;
   vec3 specular;
   
   float constant;
	float linear;
	float quadratic;

   float cutOff;
};

out vec4 FragColor;

in vec2 tex;
in vec3 normal;
in vec3 fragPos;

uniform Material material;
uniform Light light;

uniform vec3 viewPos;

void main()
{
   vec3 norm = normalize(normal);

   // vec3 lightDir = normalize(-light.direction);
   vec3 lightDir = normalize(light.position - fragPos);
   vec3 viewDir = normalize(viewPos - fragPos);
   vec3 reflectDir = reflect(-lightDir, norm);

   float distance = length(light.position - fragPos);
   float attenuation = 1.0 / (light.constant + light.linear * distance + light.quadratic * (distance * distance));

   vec3 ambient = light.ambient * vec3(texture(material.diffuse, tex));

   vec3 result = ambient;

   float theta = dot(lightDir, normalize(-light.direction));
   if (theta > light.cutOff)
   {
      float diff = max(dot(norm, lightDir), 0.0);
      float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);
      vec3 diffuse = light.diffuse * diff * vec3(texture(material.diffuse, tex));
      vec3 specular = light.specular * spec * vec3(texture(material.specular, tex));
      result += diffuse + specular;
   }



   // result *= attenuation;
   FragColor = vec4(result, 1.0);
}