#include "gameboy.h"

GAMEBOY::GAMEBOY(std::string rom_path)
{
    std::vector<uint8_t> program_data;
    read_program(program_data, rom_path);
    cartridge = new CARTRIDGE(rom_path);
    timers = TIMERS();
	bus = new BUS(program_data, cartridge, &timers);
    cpu = new CPU(bus);
    timer_interrupt_requested = false;
}


void GAMEBOY::run_emulation()
{
	while (true)
    {
        uint8_t elapsed_t_cycles = cpu->tick();
        timer_interrupt_requested = timers.tick(elapsed_t_cycles);
        if (timer_interrupt_requested)
        {
            request_timer_interrupt();
        }
	}
}

// Remove this function from here, cartridge should be storing data, not bus
void GAMEBOY::read_program(std::vector<uint8_t>& program_data, std::string rom_path)
{
    std::ifstream file(rom_path, std::ios::binary);
    if (file.is_open())
    {
        file.seekg(0, std::ifstream::end);
        std::streamsize program_size = file.tellg();
        file.seekg(0, std::ifstream::beg);
        program_data = std::vector<uint8_t>(program_size);
        file.read((char*)program_data.data(), program_size);
        file.close();
    }
    else
    {
        std::cout << "Unable to open file: " << rom_path << "\n";
    }
}

void GAMEBOY::request_timer_interrupt()
{
    uint8_t interrupt_flag = bus->read_memory(IF);
    bus->write_memory(IF, interrupt_flag | IF_TIMER_MASK);
    bus->write_memory(TIMA, bus->read_memory(TMA)); 
    timer_interrupt_requested = false;
}