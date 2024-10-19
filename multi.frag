#version 430 core
layout(location = 0)out vec4 Color;

uniform ivec2 resolution;
in float rad;

in vec2 point;

float circleShape(float radius,vec2 position)
{
float value = distance(position,vec2(0.5));
return step(radius,value);
}


void main()
{

	vec2 uv = vec2(gl_FragCoord) / vec2(resolution);
	Color = vec4(1.0,0.5,0.0,1.0);
	float dis =  distance(vec2(0.5) , vec2(gl_FragCoord)) ;

	Color = Color * mix(vec4(1,0,0,1),vec4(0,0,1,1),gl_FragCoord.x / float(resolution.x))* step(1,dis);
	//else Color = vec4(0.0,0.5,0.0,1.0);
	





	
}

