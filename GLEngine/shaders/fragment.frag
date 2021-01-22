#version 420
out vec4 FragColor;

in vec3 Color;
in vec2 TexCoords;
in float texID;

uniform sampler2D u_Textures[2];

void main()
{
	//the first texture is flipped on the x axis
	//FragColor = mix(texture(ourTexture2, vec2(1.0 - TexCoords.x, TexCoords.y) * 1.5), texture(ourTexture, TexCoords), 0.1);
	FragColor = texture(u_Textures[int(round(texID))], TexCoords) * vec4(1.0, 1.0, 1.0, 1.0);
	//FragColor = vec4(texID);
}