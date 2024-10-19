#version 430 core
layout(location = 0) in vec3 pos;
layout(location = 1) in float radius;
uniform ivec2 resolution;
out vec2 point;
out float rad;

vec3 vertices[6] = {
vec3(1, 1, 0),
vec3(1,-1, 0),
vec3( -1,1, 0),
vec3( -1,1, 0),
vec3(  -1,-1, 0),
vec3(1, -1, 0)
};

void main()
{
	point = vec2(pos.x * 0.5 + 1,1.0 - (pos.y * 0.5 + 1));
	//point = vec2(pos.x + 0.5,1.0f - (pos.y + 0.5) ) * resolution;
	
	rad = radius;
	
	gl_Position = vec4(vertices[gl_VertexID],1.0f);

	 

  
	
}
