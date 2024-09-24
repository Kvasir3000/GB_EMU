#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <stdint.h>
#include "cpu.h"
#include "bus.h"



void read_cpu_program(std::vector<uint8_t>&program_data)
{
    std::string test_path = "../tests/cpu/Blarggs/02-interrupts.gb";
    std::ifstream file(test_path, std::ios::binary);
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
        std:: cout << "Unable to open file: " << test_path << "\n";
    }
}


int main()
{
    std::vector<uint8_t> program_data;
    read_cpu_program(program_data);
    BUS bus(program_data); 
    CPU gameboy_cpu(&bus);
    gameboy_cpu.start_emulation();
	return 0;
}