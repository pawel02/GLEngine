#version 420
layout(location = 0) in vec3 aPos;
layout(location = 1) in vec2 aTex;
layout(location = 2) in vec3 Normal;
layout(location = 3) in float TexID;


out vec2 TexCoords;
out float texID;

out vec3 aNormal;
out vec3 FragPos;

out vec3 LightPos;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

uniform vec3 lightPos;
void main()
{
	gl_Position = projection * view * model * vec4(aPos, 1.0);
	//world coordinates
	FragPos = vec3(view * model * vec4(aPos, 1.0f));
	//Color = aColor;
	TexCoords = aTex;
	texID = TexID;
	aNormal = mat3(transpose(inverse(view * model))) * Normal;
	LightPos = vec3(view * vec4(lightPos, 1.0));
}