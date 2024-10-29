#pragma once 

#include <stdint.h>
#include <string.h>

#include "common/ppu_defs.h"
#include "common/memory_map_defs.h"
#include "common/interrupts_defs.h"


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
	uint8_t    vram[VRAM_HIGH - VRAM_LOW + 1];
	uint8_t    oam[OAM_HIGH - OAM_LOW + 1];

	struct PALLET
	{
		uint8_t data;
	};
	PALLET frame_buffer[LCD_RESOLUTION_Y][LCD_RESOLUTION_X];

	struct TILE
	{
		uint8_t raw_data[16];
	};
	uint8_t tile_map_cache[TILE_MAP_DIMENSION];
	TILE    tile_cache[TILE_MAP_DIMENSION];

	void render_frame();
	void scnaline_background();
	void fetch_tile_map_line(uint8_t y_tile_map);
	void fetch_tile_line(uint8_t y_offset);
};