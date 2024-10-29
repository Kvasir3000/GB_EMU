#include "gameboy.h"

GAMEBOY::GAMEBOY(std::string rom_path)
{
    init_window();
    cartridge = new CARTRIDGE(rom_path);
    timers = TIMERS();
    ppu = new PPU();
    bus = new BUS(cartridge, &timers, ppu);
    cpu = new CPU(bus);

    interrupts = false;
}

void GAMEBOY::init_window()
{
   int result = SDL_Init(SDL_INIT_VIDEO | SDL_INIT_JOYSTICK);
   if (result < 0)
   {
       std::cout << "SDL_Init failed: " << SDL_GetError() << "\n";
       assert(false);
   }

   window = SDL_CreateWindow("Game Boy", 250, 250, LCD_RESOLUTION_X * LCD_RESOLUTION_SCALER, LCD_RESOLUTION_Y * LCD_RESOLUTION_SCALER, SDL_WINDOW_SHOWN);
   if (!window)
   {
       std::cout << "SDL_CreateWindow failed: " << SDL_GetError() << "\n";
       assert(false);
   }

   window_surface = SDL_GetWindowSurface(window);
   if (!window_surface)
   {
       std::cout << "SDL_GetWindowSurface failed: " << SDL_GetError() << "\n";
       assert(false);
   }
}

void GAMEBOY::run_emulation()
{
    last_frame_time = std::chrono::high_resolution_clock::now();
	while (true)
    {
        elapsed_t_cycles = cpu->tick();
        interrupts |= timers.tick(elapsed_t_cycles);
        interrupts |= ppu->tick(elapsed_t_cycles);
        request_interrupts();
        auto elaplsed_time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::high_resolution_clock::now() - last_frame_time);
        if (elaplsed_time.count() >= 16)
        {
            // Draw to SDL window
            last_frame_time = std::chrono::high_resolution_clock::now();
        }
    
	}
}


void GAMEBOY::request_interrupts()
{
    if (interrupts & REQUEST_TIMER_INTERRUPT)
    {
        request_timer_interrupt();
    }
    interrupts = 0;
}

void GAMEBOY::request_timer_interrupt()
{
    uint8_t interrupt_flag = bus->read_memory(IF);
    bus->write_memory(IF, interrupt_flag | IF_TIMER_MASK);
    bus->write_memory(TIMA, bus->read_memory(TMA)); 
    interrupts = false;
}