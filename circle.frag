#version 430 core
layout(location = 0)out vec4 Color;

uniform ivec2 resolution;
float radius = 50;

in vec2 point;



void main()
{

	Color = vec4(1,0.5,0.0,1.0);
	float dis =  distance(vec2(point),vec2(gl_FragCoord));
	
	
	if( dis * dis > radius * radius )
	{
		discard;
	}
	else Color = vec4(1,0.5,1.0,1.0);
	
	
	


	
}

