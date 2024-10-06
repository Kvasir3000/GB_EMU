#include "gameboy.h"

GAMEBOY::GAMEBOY(std::string rom_path)
{
    std::vector<uint8_t> program_data;
    read_program(program_data, rom_path);
	bus = new BUS(program_data);
    cpu = new CPU(bus);
    timers = TIMERS(bus);
}


void GAMEBOY::run_emulation()
{
	while (true)
    {
        uint8_t elapsed_t_cycles = cpu->tick();
        timers.tick(elapsed_t_cycles);
	}
}


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