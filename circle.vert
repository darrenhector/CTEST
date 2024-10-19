#version 430 core
layout(location = 0) in vec3 pos;
layout(location = 1) in vec2 circle_pos;
uniform ivec2 resolution;
out vec2 point;

void main()
{
	point = vec2(circle_pos.x + 0.5,1.0f - (circle_pos.y + 0.5) ) * resolution + vec2(pos)*resolution;


	//gl_Position = vec4(pos + vec3(circle_pos * 0.25, 0.0),1.0f);
	
	gl_Position = vec4(pos  ,1.0f) + vec4(0,0 ,0,0);
	 

  
	
}
