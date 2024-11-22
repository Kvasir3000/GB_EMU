#include "joypad.h"

JOYPAD::JOYPAD()
{
    p1 =      0xCF;
    d_pad =   0x0F;
    buttons = 0x0F;

    d_pad_map.emplace(SDLK_RIGHT, JOYPAD_RIGHT);
    d_pad_map.emplace(SDLK_LEFT,  JOYPAD_LEFT);
    d_pad_map.emplace(SDLK_UP,    JOYPAD_UP);
    d_pad_map.emplace(SDLK_DOWN,  JOYPAD_DOWN);

    select_buttons_map.emplace(SDLK_d,      JOYPAD_A);
    select_buttons_map.emplace(SDLK_f,      JOYPAD_B);
    select_buttons_map.emplace(SDLK_SPACE,  JOYPAD_SELECT);
    select_buttons_map.emplace(SDLK_RETURN, JOYPAD_START);

}

uint8_t JOYPAD::read_input()
{
    SDL_Event events;
    uint8_t interrupt = 0;
    while (SDL_PollEvent(&events))
    {
        if (events.type == SDL_QUIT)
        {

        }
        else if (events.type == SDL_KEYDOWN)
        {
            interrupt = REQUEST_JOYPAD_INTERRUPT;
            SDL_Keycode key = events.key.keysym.sym;
            if ((p1 & JOYPAD_D_PAD) && d_pad_map[key])
            {
                d_pad = ~d_pad_map[key];
            }
            if ((p1 & JOYPAD_BUTTONS) && select_buttons_map[key])
            {
                buttons = ~select_buttons_map[key];
            }
        }
        else if (events.type == SDL_KEYUP)
        {
            SDL_Keycode key = events.key.keysym.sym;
            if ((p1 & JOYPAD_D_PAD) && d_pad_map[key])
            {
                d_pad |= d_pad_map[key];
            }
            if ((p1 & JOYPAD_BUTTONS) && select_buttons_map[key])
            {
                buttons |= select_buttons_map[key];
            }
        }
    }
    return interrupt;
}

void JOYPAD::write_p1(uint8_t data)
{
    p1 = (data & 0x30);
}

uint8_t JOYPAD::read_p1()
{
    if ((p1 & 0xF0) == 0x30)
    {
        return 0xF;
    }
    if ((p1 & JOYPAD_D_PAD))
    {
        return (p1 & 0xF0) | (d_pad & 0x0F);
    }
    else
    {
        return (p1 & 0xF0) | (buttons & 0x0F);
    }
}