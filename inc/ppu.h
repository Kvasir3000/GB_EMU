#pragma once 

#include <stdint.h>
#include <string.h>
#include <iostream>
#include <SDL.h>
#include <assert.h>
#include <chrono>
#include <thread>
#include <vector>
#include <algorithm>

#include "common/ppu_defs.h"
#include "utils/debug.h"
#include "common/memory_map_defs.h"
#include "common/interrupts_defs.h"

//#define DEBUG_PPU


class PPU
{
public:
	PPU();
	uint8_t tick(uint8_t elapsed_dots);

	uint8_t read_oam(uint16_t memory_address);
	void    write_oam(uint16_t memory_address, uint8_t data);
	uint8_t read_vram(uint16_t memory_address);
	void    write_vram(uint16_t memory_address, uint8_t data);
	uint8_t read_scy();
	void    write_scy(uint8_t data);
	uint8_t read_scx();
	void    write_scx(uint8_t data);
	uint8_t read_ly();
	void    write_bgp(uint8_t data);
	uint8_t read_bgp();
	void    write_obp0(uint8_t data);
	uint8_t read_obp0();
	void    write_obp1(uint8_t data);
	uint8_t read_obp1();
	void    write_lyc(uint8_t data);
	uint8_t read_lyc();
	void    write_stat(uint8_t data);
	uint8_t read_stat();
	void    write_wx(uint8_t data);
	uint8_t read_wx();
	void    write_wy(uint8_t data);
    uint8_t read_wy();
	uint8_t read_lcdc();
	void    write_lcdc(uint8_t data);

private:
	enum MODES
	{
		MODE_0_HORIZONTAL_BLANK,
		MODE_1_VERTICAL_BLANK,
		MODE_2_OAM_SCAN,
		MODE_3_DRAWING_PIXELS
	} current_mode;
	uint16_t scanline_dots;
	uint8_t  current_line;

	uint8_t    scy;
	uint8_t    scx;
	uint8_t    lcdc;
	uint8_t    bgp;
	uint8_t    obp0;
	uint8_t    obp1;
	uint8_t    lyc;
	uint8_t    wy;
	uint8_t    wx;
	uint8_t    stat;
 	uint8_t    vram[VRAM_HIGH - VRAM_LOW + 1];
	uint8_t    oam[OAM_HIGH - OAM_LOW + 1];
	
	SDL_Color frame_buffer[LCD_RESOLUTION_Y][LCD_RESOLUTION_X];

	struct TILE
	{
		uint8_t  raw_data[TILE_SIZE];
		uint16_t decoded_data[TILE_DIMENSION];
	};
	uint8_t   tile_map_cache[TILE_MAP_DIMENSION];
	TILE      tile_cache[TILE_MAP_DIMENSION];
	TILE      sample_tile(uint16_t memory_address);
	void      decode_tile(TILE& tile);
	void      render_tile(SDL_Renderer* renderer, uint16_t x, uint16_t y, uint16_t scaler, TILE tile);
	SDL_Color get_pallet_color(uint8_t pallet_id);

	uint8_t get_stat_interrupt(uint8_t condition);

	std::chrono::milliseconds frame_duration;
	std::chrono::high_resolution_clock::time_point last_frame_time;
	void render_frame();

	void fetch_tile_map_line(uint8_t y_tile_map, uint16_t tile_map_base_address);
	void fetch_tile_line();
	uint8_t get_pallete(uint8_t tile_id_x, uint8_t tile_x_offset, uint8_t tile_row);
	void scnaline_background();
	void scanline_window();

	struct OBJECT_ATTRIBUTES
	{
		uint8_t y;
		uint8_t x;
		uint8_t tile_id;
		uint8_t attributes;
	};
	OBJECT_ATTRIBUTES sample_object(uint16_t memory_address);
	std::vector<OBJECT_ATTRIBUTES> objects;
	void select_objects();
	void sort_object_priority();
	void draw_objects();
	void draw_object_tile(OBJECT_ATTRIBUTES object, TILE tile);
	
	void           init_window();
	SDL_Window*    window;
	SDL_Renderer*  renderer;
	void           render_frame_buffer();

	// PPU debug
	SDL_Window*   vram_window;
	SDL_Renderer* vram_renderer;
	SDL_Window*   tile_map_window; 
	SDL_Renderer* tile_map_renderer;
	void          init_debug_windows();
	void          render_vram_debug();
	void          render_tile_map_debug();
	void          render_viewport_debug();
};