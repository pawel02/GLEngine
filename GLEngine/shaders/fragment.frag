#version 420
out vec4 FragColor;

in vec2 TexCoords;
in float texID;
in vec3 aNormal;
in vec3 FragPos;
in vec3 LightPos;

uniform sampler2D u_Textures[2];


struct Light
{
	vec3 position;

	vec3 ambient; 
	vec3 diffuse;
	vec3 specular;
};
uniform Light light;

struct Material
{
	vec3 ambient;
	vec3 diffuse;
	vec3 specular;
	float shininess;
};
uniform Material material;

void main()
{
	//ambient
	vec3 ambient = light.ambient * material.ambient;

	//direction between the light source and the frag position 
	vec3 norm = normalize(aNormal);
	vec3 lightDir = normalize(LightPos - FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse =  light.diffuse * (diff * material.diffuse);

	//specular
	float specularStrength = 0.5;
	vec3 viewDir = normalize(-FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), material.shininess);

	vec3 specular = light.specular * (spec * material.specular);

	//FragColor = texture(u_Textures[int(round(texID))], TexCoords) * vec4(ambient + diffuse + specular, 1.0);
	FragColor = vec4(ambient + diffuse + specular, 1.0);
}