#pragma once

#include <iostream>
#include <SDL.h>
#include <stdint.h>
#include <assert.h>
#include <common/ppu_defs.h>

class SDL_RENDERER
{
public: 
	SDL_RENDERER();
	void render_frame_buffer(SDL_Color frame_buffer[LCD_RESOLUTION_Y][LCD_RESOLUTION_X]);
private:
	SDL_Window* window;
	SDL_Renderer* renderer;
};