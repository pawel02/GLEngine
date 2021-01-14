#version 420
out vec4 FragColor;

in vec3 Color;
in vec2 TexCoords;

uniform sampler2D ourTexture;
uniform sampler2D ourTexture2;
void main()
{
	//the first texture is flipped on the x axis
	//FragColor = mix(texture(ourTexture2, vec2(1.0 - TexCoords.x, TexCoords.y) * 1.5), texture(ourTexture, TexCoords), 0.1);
	FragColor = texture(ourTexture, TexCoords);
}