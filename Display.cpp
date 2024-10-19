#include "Display.hpp"
#include "SDL.h"
#include "glew.h"
#include <iostream>
Display::Display(int w,int h,const char* name):window{},context{},active{true}
{
	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_COMPATIBILITY);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,6);
	SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);
	
	
	SDL_Window* window = SDL_CreateWindow(name,SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,w,h,SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
	
	context	= SDL_GL_CreateContext(window);
	
	glewExperimental = 1;
	if(GLEW_OK != glewInit())
	{
		exit(1);
	}
	
	std::cout<<glGetString(GL_VENDOR)<<std::endl;
	std::cout<<glGetString(GL_RENDERER)<<std::endl;
	std::cout<<glGetString(GL_VERSION)<<std::endl;
}

Display::~Display()
{
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
}

bool Display::IsActive() const {
	return active;
}
