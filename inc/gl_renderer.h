#pragma once 

#include <stdint.h>
#include <SDL.h>
#include <SDL_pixels.h>
#include <glew.h>
#include <SDL_opengl.h>
#include <iostream>
#include <assert.h>
#include <string>
#include <fstream>

#include "common/ppu_defs.h"

class OPENGL_RENDERER
{
public:
	OPENGL_RENDERER();
	void render_frame_buffer(SDL_Color frame_buffer[LCD_RESOLUTION_Y][LCD_RESOLUTION_X]);
private:
	SDL_Window* window;
	SDL_GLContext context;

	struct Vertex
	{
		GLfloat position[3];
		GLfloat texture_coordinates[2];
	};
	Vertex screen_quad[6];
	GLuint vob;
	GLuint vao;
	void init_vertex_buffer();

	uint8_t* texture_data;

	GLuint  vertex_shader;
	GLchar* vs_source;
	GLuint  fragment_shader;
	GLchar* fs_source;
	GLuint  shader_program;
	void  init_shaders();
	char* read_shader(std::string shader_name);
};