#include "cartridge.h"


CARTRIDGE::CARTRIDGE()
{

}

CARTRIDGE::CARTRIDGE(std::string rom_path)
{
    read_program(rom_path);
   
    init_memory_banks(rom_banks, 2 << program_data[ROM_SIZE_ADDR], ROM_BANK_SIZE_KIB);

    int banks[6] = {0, 0, 1, 4, 16, 8};
    auto a = program_data[RAM_SIZE_ADDR];
    init_memory_banks(ram_banks, banks[program_data[RAM_SIZE_ADDR]], RAM_BANK_SIZE_KIB);
    
    fill_rom();

    ram_bank_idx = 0;
    rom_bank_idx = 1;
    //std::vector<uint8_t>ram_bank1(0x2000);
    //ram_banks.emplace_back(ram_bank1);
}

CARTRIDGE::CARTRIDGE(std::string rom_path, std::vector<uint8_t> program_data)
{
    read_program(rom_path);
    ram_bank_idx = 0;
    rom_bank_idx = 0; 
    std::vector<uint8_t>ram_bank1(0x2000);
    ram_banks.emplace_back(ram_bank1);
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

void CARTRIDGE::init_memory_banks(std::vector<std::vector<uint8_t>>& memory_bank, uint8_t number_of_banks, uint16_t bank_size)
{
    for (uint8_t i = 0; i < number_of_banks; i++)
    {
        std::vector<uint8_t>bank(bank_size, 0);
        memory_bank.emplace_back(bank);
    }
}

void CARTRIDGE::fill_rom()
{
    uint16_t bank = 0;
    for (uint64_t i = 0; i < program_data.size(); i++)
    {
        if ((i % ROM_BANK_SIZE_KIB == 0) && i != 0)
        {
            bank++;
        }
        rom_banks[bank][i % ROM_BANK_SIZE_KIB] = program_data[i];
    }
    program_data.clear();
}


uint8_t CARTRIDGE::read_rom_bank0(uint16_t memory_address)
{
    return rom_banks[0][memory_address];
}


uint8_t CARTRIDGE::read_rom_bank_nn(uint16_t memory_address)
{
    return rom_banks[rom_bank_idx][memory_address];
}

void CARTRIDGE::write_rom(uint16_t memory_address, uint8_t data)
{
    if (memory_address >= MBC1_ROM_BANK_NUMBER_REGISTER_LOW && memory_address <= MBC1_ROM_BANK_NUMBER_REGISTER_HIGH)
    {
        rom_bank_idx = ((data & ROM_BANK_BIT_MASK) == 0) ? 1 : data & ROM_BANK_BIT_MASK;
    }
    else if (memory_address >= MBC1_RAM_ENABLE_REGISTER_LOW && memory_address <= MBC1_RAM_ENABLE_REGISTER_HIGH)
    {
        ram_enable = ((data & ENABLE_RAM_BIT_MASK) == ENABLE_RAM) ? true : false;
    }
    else if (memory_address >= MBC1_RAM_BANK_NUMBER_REGISTER_LOW && memory_address <= MBC1_RAM_BANK_NUMBER_REGISTER_HIGH)
    {
        ram_bank_idx = data & RAM_BANK_BIT_MASK;
    }
    else
    {
        std::cout << "Warning: write to ROM address is disabled 0x" << std::hex << memory_address;
    }
}

uint8_t CARTRIDGE::read_ram(uint16_t memory_address)
{
    if (ram_enable && ram_banks.size())
    {
        return ram_banks[ram_bank_idx][memory_address];
    }
    else
    {
        return 0xFF;
    }
}

void CARTRIDGE::write_ram(uint16_t memory_address, uint8_t data)
{
    if (ram_enable && ram_banks.size())
    {
        ram_banks[ram_bank_idx][memory_address] = data;
    }
}
