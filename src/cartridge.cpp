#include "cartridge.h"


CARTRIDGE::CARTRIDGE()
{

}

CARTRIDGE::CARTRIDGE(std::string rom_path)
{
    read_program(rom_path);
    ram_bank_idx = 0;
    rom_bank_idx = 0;
    std::vector<uint8_t>ram_bank1(0x2000);
    ram_banks.emplace_back(ram_bank1);
}

CARTRIDGE::CARTRIDGE(std::string rom_path, std::vector<uint8_t> program_data)
{
    read_program(rom_path);
    ram_bank_idx = 0;
    rom_bank_idx = 0; 
    std::vector<uint8_t>ram_bank1(0x2000);
    ram_banks.emplace_back(ram_bank1);
}

uint8_t CARTRIDGE::read_rom(uint16_t memory_address)
{
   /* if (memory_address >= ROM_BANK_00_LOW && memory_address <= ROM_BANK_00_HIGH)
    {
        return program_data[memory_address];
    }
    else if (memory_address >= ROM_BANK_00_LOW && memory_address <= ROM_BANK_NN_HIGH)
    {

    }*/
    return program_data[memory_address];
}

uint8_t CARTRIDGE::read_ram(uint16_t memory_address)
{
    return ram_banks[ram_bank_idx][memory_address - EXTERNAL_RAM_LOW];
}

void CARTRIDGE::write_ram(uint16_t memory_address, uint8_t data)
{
    ram_banks[ram_bank_idx][memory_address - EXTERNAL_RAM_LOW] = data;
}


void CARTRIDGE::read_program(std::string rom_path)
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