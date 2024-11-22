#pragma once
#include <SDL.h>
#include <map>

#include "common/memory_map_defs.h"
#include "common/interrupts_defs.h"''


#define JOYPAD_A        0b00000001
#define JOYPAD_RIGHT    0b00000001
#define JOYPAD_B        0b00000010
#define JOYPAD_LEFT     0b00000010
#define JOYPAD_SELECT   0b00000100 
#define JOYPAD_UP       0b00000100
#define JOYPAD_START    0b00001000
#define JOYPAD_DOWN     0b00001000
#define JOYPAD_D_PAD    0b00100000 
#define JOYPAD_BUTTONS  0b00010000


class JOYPAD
{
public:
	JOYPAD();
	uint8_t read_input();
	void    write_p1(uint8_t data);
	uint8_t read_p1();
private:
	std::map<SDL_Keycode, uint16_t> select_buttons_map;
	std::map<SDL_Keycode, uint16_t> d_pad_map;
	uint8_t p1;
	uint8_t d_pad;
	uint8_t buttons;
};