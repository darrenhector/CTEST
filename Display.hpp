#ifndef DISPLAY_HPP
#define DISPLAY_HPP
#include "SDL.h"
class Display
{
public:
	Display(int w,int h,const char* name);
	~Display();
	
	bool IsActive() const;
protected:
	SDL_Window* window;
	SDL_GLContext context;
	bool active;
};

#endif
