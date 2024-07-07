#include <iostream>
#include <string>
#include <fstream>
#include <vector>

void read_cpu_program(std::vector<char>&program_stream)
{
    std::string test_path = "C:/Users/Nikita/Desktop/gameboy/tests/cpu/Blarggs/01-special.gb";
    std::ifstream file(test_path);
    if (file.is_open())
    {
        file.seekg(0, std::ifstream::end);
        std::streamsize program_size = file.tellg();
        file.seekg(0, std::ifstream::beg);
        program_stream = std::vector<char>(program_size);
        file.read(program_stream.data(), program_size);
        file.close();
    }
    else
    {
        std:: cout << "Unable to open file: " << test_path << "\n";
    }
}

int main()
{
    std::vector<char> program_stream;
    read_cpu_program(program_stream);
    
	return 0;
}