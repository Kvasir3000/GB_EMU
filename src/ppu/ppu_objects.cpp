#include "ppu.h"

PPU::OBJECT_ATTRIBUTES PPU::sample_object(uint16_t memory_address)
{
	OBJECT_ATTRIBUTES object = { 0 };
	object.y = oam[memory_address++];
	object.x = oam[memory_address++];
	object.tile_id = oam[memory_address++];
	object.attributes = oam[memory_address++];

	return object;
}

void PPU::select_objects()
{
	objects.clear();
	for (uint16_t i = 0; i <= OAM_HIGH - OAM_LOW; i += 4)
	{
		OBJECT_ATTRIBUTES object = sample_object(i);
		int16_t object_y = object.y - 16;
		if (object_y >= 0 && object_y <= LCD_RESOLUTION_Y)
		{
			objects.push_back(object);
		}
	}
}

void PPU::sort_object_priority()
{
	std::sort(objects.begin(), objects.end(), [](OBJECT_ATTRIBUTES obj1, OBJECT_ATTRIBUTES obj2) { return (obj1.x > obj2.x); });
}

void PPU::draw_objects()
{
	if (lcdc & LCDC_OBJ_ENABLE)
	{
		select_objects();
		sort_object_priority();
		for (uint16_t i = 0; i < objects.size(); i++)
		{
			OBJECT_ATTRIBUTES object = objects[i];
			uint16_t tile_addres = TILE_DATA_BASE_1 + (object.tile_id * TILE_SIZE);
			TILE tile = sample_tile(tile_addres);
			decode_tile(tile);
			draw_object_tile(object, tile);
			if (lcdc & LCDC_OBJ_SIZE)
			{
				tile_addres = TILE_DATA_BASE_1 + ((object.tile_id + 1) * TILE_SIZE);
				tile = sample_tile(tile_addres);
				decode_tile(tile);
				object.y += 8;
				draw_object_tile(object, tile);
			}
		}
	}
}

void PPU::draw_object_tile(OBJECT_ATTRIBUTES object, TILE tile)
{
	for (uint8_t i = 0; i < TILE_DIMENSION; i++)
	{
		for (uint8_t j = 0; j < TILE_DIMENSION; j++)
		{
			int16_t x = object.x - LCD_OBJECT_X_OFFSET + i;
			int16_t y = object.y - LCD_OBJECT_Y_OFFSET + j;
			if (x >= 0 && x <= LCD_RESOLUTION_X && y >= 0 && y <= LCD_RESOLUTION_Y)
			{
				uint8_t tile_column = (object.attributes & OAM_ATTRIBUTES_X_FLIP) ? (i * 2) : (14 - (i * 2));
				uint8_t tile_row = (object.attributes & OAM_ATTRIBUTES_Y_FLIP) ? TILE_DIMENSION - j - 1 : j;
				uint8_t pallete_id = (tile.decoded_data[tile_row] & (PIXEL_MASK << tile_column)) >> tile_column;

				if (pallete_id != TRANSPERENT_PIXEL)
				{
					uint8_t pallete_offset = pallete_id * 2;
					uint8_t pallete = (((object.attributes & OAM_ATTRIBUTES_DMG_PALLETE) ? obp1 : obp0) & (PIXEL_MASK << pallete_offset)) >> pallete_offset;
					frame_buffer[y][x] = get_pallet_color(pallete);
				}
			}
		}
	}
}