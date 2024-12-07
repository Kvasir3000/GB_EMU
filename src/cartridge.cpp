#include "cartridge.h"


CARTRIDGE::CARTRIDGE()
{

}

CARTRIDGE::CARTRIDGE(std::string rom_path)
{
    read_program(rom_path);
    //read_save(rom_path);
   
    init_memory_banks(rom_banks, 2 << program_data[ROM_SIZE_ADDR], ROM_BANK_SIZE_KIB);

    int banks[6] = {0, 0, 1, 4, 16, 8};
    auto a = program_data[RAM_SIZE_ADDR];
    init_memory_banks(ram_banks, banks[program_data[RAM_SIZE_ADDR]], RAM_BANK_SIZE_KIB);
    
    fill_rom();
    //fill_ram();


    ram_bank_idx = 0;
    rom_bank_idx = 1;
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

void CARTRIDGE::read_save(std::string rom_path)
{
#if defined _WIN32
    std::string save_path = rom_path;
    save_path.pop_back();
    save_path.pop_back();
    save_path.push_back('s');
    save_path.push_back('a');
    save_path.push_back('v');
    std::cout << save_path << "\n";
    save_file = std::fstream(save_path, std::ios::binary | std::ios::out  | std::ios::in);
    if (save_file.is_open())
    {
        save_file.seekg(0, std::ifstream::end);
        std::streamsize program_size = save_file.tellg();
        save_file.seekg(0, std::ifstream::beg);
        save_data = std::vector<uint8_t>(program_size);
        save_file.read((char*)save_data.data(), program_size);
    }
    else
    {
        save_file.open(save_path, std::ios::binary | std::ios::out);
        std::cout << "Unable to open file: " << save_path << "\n";
    }

   
#else
    std::cout << "Open files for Linux system is not written yet\n";
#endif
}

void CARTRIDGE::save()
{
    for (uint16_t i = 0; i < ram_banks.size(); i++)
    {
        save_file.write((char*)(&ram_banks[i]), sizeof(uint8_t) * RAM_BANK_SIZE_KIB);
    }

    save_file.close();
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

void CARTRIDGE::fill_ram()
{
    uint16_t bank = 0;
    for (uint64_t i = 0; i < save_data.size(); i++)
    {
        if ((i % RAM_BANK_SIZE_KIB == 0) && i != 0)
        {
            bank++;
        }
        ram_banks[bank][i % RAM_BANK_SIZE_KIB] = save_data[i];
    }
    save_data.clear();
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
