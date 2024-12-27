#include "sdl_renderer.h"


SDL_RENDERER::SDL_RENDERER()
{
	int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
	if (result < 0)
	{
		std::cout << "SDL_Init failed: " << SDL_GetError() << "\n";
		assert(false);
	}

	window = SDL_CreateWindow("Game Boy", 250, 100, LCD_RESOLUTION_X * LCD_RESOLUTION_SCALER, LCD_RESOLUTION_Y * LCD_RESOLUTION_SCALER, SDL_WINDOW_SHOWN);
	if (!window)
	{
		std::cout << "SDL_CreateWindow failed: " << SDL_GetError() << "\n";
		assert(false);
	}

	renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
	if (!renderer)
	{
		std::cout << "SDL_CreateRenderer failed " << SDL_GetError() << "\n";
		assert(false);
	}
}


void SDL_RENDERER::render_frame_buffer(SDL_Color frame_buffer[LCD_RESOLUTION_Y][LCD_RESOLUTION_X])
{
	for (uint16_t i = 0; i < LCD_RESOLUTION_Y; i++)
	{
		for (uint16_t j = 0; j < LCD_RESOLUTION_X; j++)
		{
			SDL_Color color = frame_buffer[i][j];
			SDL_SetRenderDrawColor(renderer, color.r, color.g, color.b, color.a);
			SDL_Rect rect = { j * LCD_RESOLUTION_SCALER, i * LCD_RESOLUTION_SCALER, LCD_RESOLUTION_SCALER, LCD_RESOLUTION_SCALER };
			SDL_RenderFillRect(renderer, &rect);
		}
	}
	SDL_RenderPresent(renderer);
}
