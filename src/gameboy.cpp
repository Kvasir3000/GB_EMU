#include "gameboy.h"

GAMEBOY::GAMEBOY()
{
    get_rom_file();

    joypad = JOYPAD();
    cartridge = new CARTRIDGE(rom_path);
    timers = TIMERS();
    ppu = new PPU();
    bus = new BUS(cartridge, &timers, ppu, &joypad);
    cpu = new CPU(bus);

    interrupts = false;
    run_emulator = true;
}


void GAMEBOY::get_rom_file()
{
    rom_path = std::string(260, '\0');

#if defined _WIN32
    OPENFILENAME open_file_name;
    ZeroMemory(&open_file_name, sizeof(open_file_name));
    open_file_name.lStructSize = sizeof(open_file_name);
    open_file_name.hwndOwner = NULL;
    open_file_name.lpstrFile = (LPSTR)rom_path.c_str();
    open_file_name.nMaxFile = MAX_PATH;
    open_file_name.lpstrFilter = "ROM Files\0*.gb\0";
    open_file_name.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;
    open_file_name.lpstrTitle = (LPCSTR)"Open File";
    if (GetOpenFileName(&open_file_name)) 
    {
        size_t path_size = rom_path.find_last_of("b");
        rom_path.resize(path_size + 1);
        std::cout << "Selected file: " << rom_path << "\n";
    }
#else
    FIILE* fp = popen("zenity --file-selection --title=\"Select a file\"", "r");
    if (fp)
    {
        if (fgets(rom_path.c_str(), rom_path.size(), fp) != NULL)
        {
            rom_path[rom_path.size() - 1] = 0;
            std::cout << "Selected file: " << rom_path << "\n";
        }
        pclose(fp);
    }
    std::cout << "Open files for Linux system is not written yet\n";
#endif
}

void GAMEBOY::run_emulation()
{
	while (run_emulator)
    {
        elapsed_t_cycles = cpu->tick();
        interrupts |= timers.tick(elapsed_t_cycles);
        interrupts |= ppu->tick(elapsed_t_cycles);
        interrupts |= joypad.read_input(run_emulator);
        request_interrupts();
    }
}

void GAMEBOY::request_interrupts()
{
    if (interrupts & REQUEST_TIMER_INTERRUPT)
    {
        add_interrupt(IF_TIMER_MASK);
        bus->write_memory(TIMA, bus->read_memory(TMA));
    }
    if (interrupts & REQUEST_VBLANK_INTERRUPT)
    {
        add_interrupt(IF_VBLANK_MASK);
    }
    if (interrupts & REQUEST_LCD_INTERRUPT)
    {
        add_interrupt(IF_LCD_MASK);
    }
    if (interrupts & REQUEST_JOYPAD_INTERRUPT)
    {
        add_interrupt(IF_JOYPAD_MASK);
    }
    interrupts = 0;
}

void GAMEBOY::add_interrupt(uint8_t interrupt_type)
{
    uint8_t interrupt_flag = bus->read_memory(IF);
    bus->write_memory(IF, interrupt_flag | interrupt_type);
}