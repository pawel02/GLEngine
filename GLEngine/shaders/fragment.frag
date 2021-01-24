#version 420
out vec4 FragColor;

in vec3 Color;
in vec2 TexCoords;
in float texID;
in vec3 aNormal;
in vec3 FragPos;
in vec3 LightPos;

uniform sampler2D u_Textures[2];

uniform vec3 lightColor;

uniform vec3 viewPos;

void main()
{
	//ambient
	float ambientStrength = 0.1;
	vec3 ambient = ambientStrength * lightColor;

	//direction between the light source and the frag position 
	vec3 norm = normalize(aNormal);
	vec3 lightDir = normalize(LightPos - FragPos);

	float diff = max(dot(norm, lightDir), 0.0);
	vec3 diffuse = diff * lightColor;

	//specular
	float specularStrength = 0.5;
	vec3 viewDir = normalize(-FragPos);
	vec3 reflectDir = reflect(-lightDir, norm);
	float spec = pow(max(dot(viewDir, reflectDir), 0.0), 256);

	vec3 specular = specularStrength * spec * lightColor;

	FragColor = texture(u_Textures[int(round(texID))], TexCoords) * vec4(ambient + diffuse + specular, 1.0);
}