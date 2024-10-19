#version 430 core
in vec2 TexCoord;
in vec3 Normal;
out vec4 FragColor;
uniform sampler2D OurTexture;

const vec3 lightDirection = vec3(0,10,-10);

void main()
{
	FragColor = texture(OurTexture,TexCoord)
	
	* clamp( dot( lightDirection, normalize(Normal)), 0.0f, 1.0f);
	
}
