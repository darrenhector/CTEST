#version 430 core
layout(location = 0) in vec3 pos;
uniform ivec2 mouse;
const vec2 offsets[5] = { vec2(0,0),{0,150},{150,0},{-150,0} , {0,-150} };
out vec2 point;
void main()
{
	point = offsets[gl_InstanceID];
	gl_Position = vec4(pos,1.0f);
}
