#include <cstdlib>
#include <iostream>
#include <thread>
#include <algorithm>
#include <chrono>
#include <vector>
#include <numeric>
#include <thread>
#include <ctime>
#include <bitset>
#include <limits>
#include "Lib\SDL2\include\SDL.h"
#include "Lib\glew\include\GL\glew.h"
#include "Lib\glm\glm.hpp"
#include "intrin.h"


using namespace std;

class Timer {
	std::uint64_t tp;
public:
	Timer() {
		tp = get_time_stamp();
	}
	
	void reset(){
		tp = get_time_stamp();
	}
	
	std::uint64_t elapsed() const{
		return get_time_stamp() - tp;
	}

	~Timer() {
		std::cout << get_time_stamp() - tp << "ms." << std::endl;
	}

	std::uint64_t get_time_stamp() const {
		return std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::steady_clock::now().time_since_epoch()).count();
	}
	
	std::uint64_t duration() const {
		return get_time_stamp() - tp;
	}	
	
};


float vertices[9] = {-1,-1,0,
						0,1,0,
						1,-1,0};
						
						
float square[18] = { -1.0f, 1.0f,0.0f,
					 1.0f, 1.0f,0.0f,
					 1.0f,-1.0f,0.0f,
					 1.0f,-1.0f,0.0f,
					-1.0f,-1.0f,0.0f,
					-1.0f, 1.0f,0.0f
					};
						
void check_error(int line)
{
	GLenum error = 0;
	error = glGetError();
	if(error != GLEW_OK)
	{
		std::cout<<"line #: "<<line<<" "<<"error code: "<<error<<"\n";
		system("pause");
	}
}
#define check(x) check_error(__LINE__)
GLuint create_shader(GLenum type,const char* source)
{
	GLuint shader=glCreateShader(type);
	glShaderSource(shader,1,&source,nullptr);
	
	glCompileShader(shader);
	GLint status = 0;
	glGetShaderiv(shader,GL_COMPILE_STATUS,&status);
	if( status == GL_FALSE)  
	{
		char buffer[1024];
		glGetShaderInfoLog(shader,1024,nullptr,buffer);
		std::cout<<buffer<<std::endl;
	}
	return shader;
}

GLuint create_program(const char* vpath,const char* fpath)
{
	char* vsource = (char*)SDL_LoadFile(vpath,nullptr);
	char* fsource = (char*)SDL_LoadFile(fpath,nullptr);
	
	GLuint program = glCreateProgram();
	GLuint vshader = create_shader(GL_VERTEX_SHADER,vsource);
	GLuint fshader = create_shader(GL_FRAGMENT_SHADER,fsource);
	
	SDL_free(vsource);
	SDL_free(fsource);
	
	check();
	glAttachShader(program,vshader);
	glAttachShader(program,fshader);
	glLinkProgram(program);
	GLint lstatus = 0;
	glGetProgramiv(program,GL_LINK_STATUS,&lstatus);
	if( lstatus == GL_FALSE)  
	{
		char buffer[1024];
		glGetProgramInfoLog(program,1024,nullptr,buffer);
		std::cout<<buffer<<std::endl;
	}
	
	glDeleteShader(vshader);
	glDeleteShader(fshader);
	
	return program;
}

const glm::vec2 point[4] = { {-0.5,0.5},{0.5,0.5},{0.5,-0.5},{-0.5,-0.5}};
const glm::vec2 point1[5] = { {0,0},{0,150},{150,0},{-150,0} , {0,-150} };

struct Circle{
	glm::vec3 pos;
	float radius;
};

Circle circles[6] = { {{0.0,0.0,0.0},10.0f},
					  {{0.5,0.0,0.0},8.0f},
					  {{1.0,0.5,0.0},5.0f},
					  
					  {{0.0,4.0,0.0},10.0f},
					  {{-0.5,0.0,0.0},8.0f},
					  {{0.0,0.5,0.0},5.0f}
					  
					};
					
int main(int, char**)
{
	SDL_Init(SDL_INIT_VIDEO);
	
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK,SDL_GL_CONTEXT_PROFILE_CORE);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION,4);
	SDL_GL_SetAttribute(SDL_GL_CONTEXT_MINOR_VERSION,6);
	//SDL_GL_SetAttribute(SDL_GL_DEPTH_SIZE,24);
	
	
	
	SDL_Window* window = SDL_CreateWindow("Test Graphics",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,640,480,SDL_WINDOW_OPENGL|SDL_WINDOW_RESIZABLE);
	SDL_GLContext context	= SDL_GL_CreateContext(window);
	
	glewExperimental = 1;
	if(GLEW_OK != glewInit())
	{
		exit(1);
	}
	
	std::cout<<glGetString(GL_VENDOR)<<std::endl;
	std::cout<<glGetString(GL_RENDERER)<<std::endl;
	std::cout<<glGetString(GL_VERSION)<<std::endl;
	
	SDL_GL_SetSwapInterval(0);
	
	GLuint vao,circle_vao,multicircle_vao;
	glGenVertexArrays(1,&vao);
	glBindVertexArray(vao);
	
	GLuint vbo;
	glGenBuffers(1,&vbo);
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glBufferData(GL_ARRAY_BUFFER,sizeof(square),square,GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,12,0);
	glBindVertexArray(0);
	
	
	glGenVertexArrays(1,&circle_vao);
	glBindVertexArray(circle_vao);
	
	GLuint cbo;
	glGenBuffers(1,&cbo);
	glBindBuffer(GL_ARRAY_BUFFER,cbo);
	glBufferData(GL_ARRAY_BUFFER,sizeof(point),point,GL_STATIC_DRAW);	
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,2,GL_FLOAT,GL_FALSE,2 * sizeof(float),0);
	glVertexAttribDivisor(1,1);
	
	glBindBuffer(GL_ARRAY_BUFFER,vbo);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,3 * sizeof(float),0);
	
	glBindVertexArray(0);
	
	
	glGenVertexArrays(1,&multicircle_vao);
	glBindVertexArray(multicircle_vao);
	
	GLuint mbo;
	glGenBuffers(1,&mbo);
	glBindBuffer(GL_ARRAY_BUFFER,mbo);
	glBufferData(GL_ARRAY_BUFFER,sizeof(circles),circles,GL_STATIC_DRAW);
	
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0,3,GL_FLOAT,GL_FALSE,16,0);
	
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1,1,GL_FLOAT,GL_FALSE,16,(void*)12);
	glBindVertexArray(0);
	
	
	GLuint program = create_program("simple.vert","simple.frag");
	GLuint circle_program = create_program("circle.vert","circle.frag");
	GLuint multi = create_program("multi.vert","multi.frag");
	
	
	
	glm::ivec2 winSize;
	SDL_GetWindowSize(window,&winSize.x,&winSize.y);
	

	glProgramUniform2i(program,glGetUniformLocation(program,"resolution"),winSize.x,winSize.y);
	glProgramUniform2i(circle_program,glGetUniformLocation(circle_program,"resolution"),winSize.x,winSize.y);
	glProgramUniform2i(multi,glGetUniformLocation(multi,"resolution"),winSize.x,winSize.y);
	
	check();
	
	bool active = true;
	glEnable(GL_DEPTH_TEST);
	glDepthFunc(GL_LESS);
	Uint32 fps = 0, maxfps = 0;
	Uint64 ticks = 0;
	
	int option = 0;
	const int max_options = 3;//use to switch between draw options;
	int event_counter = 0;
	while(active)
	{
		SDL_Event event;
		while(SDL_PollEvent(&event))
		{
			++event_counter;
			if(event.type == SDL_QUIT)
			{
				active = false;
			}
			if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_ESCAPE)
			{
				active = false;
			}
			if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_n)
			{
				++option;
				if(option >= max_options) option = 0; 
			}
			if(event.type == SDL_KEYDOWN && event.key.keysym.sym == SDLK_v)
			{
				std::cout<<"swap\n";
				SDL_GL_SetSwapInterval( SDL_GL_GetSwapInterval() == 1?0:1 );
			}
			if(event.type == SDL_WINDOWEVENT)
			{
				if(event.window.event == SDL_WINDOWEVENT_RESIZED)
				{
					std::cout<<"resized\n";
					SDL_GetWindowSize(window,&winSize.x,&winSize.y);
					glViewport(0,0,winSize.x,winSize.y);
				}
			}
			
		}
		
		glm::ivec2 mouse;
		SDL_GetMouseState(&mouse.x,&mouse.y);
	
		glClearColor(1,1,1,1);
		glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
		
		switch(option)
		{
			case 0:
				glClearColor(.6,.6,.6,1);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glUseProgram(program);
				glProgramUniform2i(program,glGetUniformLocation(program,"resolution"),winSize.x,winSize.y);
				glUniform2i(glGetUniformLocation(program,"mouse"),mouse.x,mouse.y);
				glBindVertexArray(vao);
				glDrawArraysInstanced(GL_TRIANGLES,0,6,5);
				glBindVertexArray(0);
				glUseProgram(0);
			break;
			
			case 1:
				glClearColor(.4,.4,.4,1);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glUseProgram(circle_program);
				glProgramUniform2i(circle_program,glGetUniformLocation(circle_program,"resolution"),winSize.x,winSize.y);
				glBindVertexArray(circle_vao);
				glDrawArraysInstanced(GL_TRIANGLES,0,6,5);
				glBindVertexArray(0);
				glUseProgram(0);
			break;
			
			case 2:
				glClearColor(.2,.2,.2,1);
				glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
				glUseProgram(multi);
				glProgramUniform2i(multi,glGetUniformLocation(multi,"resolution"),winSize.x,winSize.y);
				glBindVertexArray(multicircle_vao);
				glDrawArrays(GL_TRIANGLES,0,6);
				glBindVertexArray(0);
				glUseProgram(0);
			break;
		}
		check();
		
		SDL_GL_SwapWindow(window);
		
		if(SDL_GetTicks64() > ticks + std::uint64_t(1000))
		{
			char title[128];
			maxfps = fps > maxfps?fps:maxfps;
			snprintf(title,sizeof(title),"fps: %d  maxfps: %d  eventcount: %d",fps,maxfps,event_counter);
			SDL_SetWindowTitle(window,title);
			fps = 0;
			ticks = SDL_GetTicks64();
		}
		else
		{
			++fps;
		}
		
	}
	glDeleteBuffers(1,&vbo);
	glDeleteVertexArrays(1,&vao);
	SDL_GL_DeleteContext(context);
	SDL_DestroyWindow(window);
	SDL_Quit();
	
	return 0;
}
