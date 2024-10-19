#version 430 core
layout(location = 0)out vec4 Color;
uniform ivec2 mouse;
uniform ivec2 resolution;
int radius = 50;

in vec2 point;



void main()
{


	Color = vec4(1.0f,1.0f,0.0f,1.0f);
	
	float dis = distance(vec2(mouse.x ,resolution.y - mouse.y) + point,vec2(gl_FragCoord) ) ;
	
	if( dis * dis > radius * radius)
	{
		discard;
	}
	else Color = vec4(0.3,0.3,0.9,1.0);
	
	




	
}

