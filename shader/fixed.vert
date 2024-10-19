#version 430 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec2 aTexCoord;
layout (location = 2) in vec3 aNormal;

out vec2 TexCoord;
out vec3 Normal;

uniform float angle;

mat4 rotate_y(float angle);

mat4 translate(vec3 t);

void main()
{
	TexCoord = vec2(aTexCoord.x,1.0f - aTexCoord.y);
	Normal = vec3(rotate_y(angle) * vec4(aNormal,0.0f));
	
	gl_Position = rotate_y(angle) * vec4(pos,1.0f);
	
}

mat4 rotate_y(float angle)
{
	const float cosine = cos(angle);
	const float sine = sin(angle);
	
	const vec4 x = vec4(cosine,0.0f, sine,0.0f);
	const vec4 y = vec4(0.0f,1.0f,0.0f,0.0f);
	const vec4 z = vec4( -sine,0.0f,cosine,0.0f);
	const vec4 w = vec4(0.0f,0.0f,0.0f,1.0f);
	
	return mat4(x,y,z,w);
}

mat4 translate(vec3 t)
{
	return mat4(1,0,0,0,0,1,0,0,0,0,1,0,t.x,t.y,t.z,1);
}

