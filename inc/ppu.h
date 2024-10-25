#pragma once 

#include <stdint.h>
#include <string.h>

#include "common/ppu_defs.h"
#include "common/memory_map_defs.h"


class PPU
{
public:
	PPU();
	void tick(uint8_t elapsed_dots);

	uint8_t read_oam(uint16_t memory_address);
	void    write_oam(uint16_t memory_address, uint8_t data);
	uint8_t read_vram(uint16_t memory_address);
	void    write_vram(uint16_t memory_address, uint8_t data);

private:
	enum MODES
	{
		MODE_0_HORIZONTAL_BLANK,
		MODE_1_VERTICAL_BLANK, 
		MODE_2_OAM_SCAN,
		MODE_3_DRAWING_PIXELS
	} current_mode;
	uint16_t scanline_dots;

	uint8_t    vram[VRAM_HIGH - VRAM_LOW + 1];
	uint8_t    oam[OAM_HIGH - OAM_LOW + 1];
};