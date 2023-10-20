#include <iostream>
#include <istream>
#include <fstream>
#include <sstream>

enum class Opcode { unknown, noop, addx };

struct Command
{
    Command()
    : opcode(Opcode::unknown)
    , param(0)
    {}
    Opcode opcode;
    int param;
};

using Commands = std::vector<Command>;
using Register = std::vector<int>;

class CPU
{
public:

    CPU()
    : regX{1}
    {}

    void Excecute(Command& cmd)
    {
        switch(cmd.opcode)
        {
            case Opcode::noop:
            {
                regX.push_back(regX.back());
                break;
            }
            case Opcode::addx:
            {
                regX.push_back(regX.back());
                regX.push_back(regX.back() + cmd.param);
                break;
            }
            default:
            {
                throw;
            }
        }
    }

    unsigned getX(unsigned cycle) { return regX[cycle]; }
    Register getX() { return regX; }

private:

    Register regX;
};

Register main_part1(Commands commands)
{
    CPU cpu;

    for(auto& command : commands)
    {
        cpu.Excecute(command);
    }

    auto cycles = std::vector<unsigned>{20, 60, 100, 140, 180, 220};
    auto signalStrength = 0;

    for(auto cycle : cycles)
    {
        signalStrength += cycle * cpu.getX(cycle - 1);
    }

    std::cout << "Day 10, part 1, answer is: " << signalStrength << std::endl;

    return cpu.getX();
}

void main_part2(Register reg)
{
    auto crtWidth = 40;

    auto image = std::stringstream{};

    for(auto cycle = 0; cycle < reg.size(); cycle++)
    {        
        auto spriteMin = reg[cycle] - 1;
        auto spriteMax = reg[cycle] + 1;

        auto col = cycle % crtWidth;
        if(col == 0) image << std::endl;
        image << ((col >= spriteMin && col <= spriteMax) ? "#" : ".");
    }

    std::cout << "Day 10, part 2, answer is: " << image.str() << std::endl;
}

int main(void)
{
    std::fstream input("../2022/day10/data/day10_input.txt");

    if(input.is_open())
    {
        Commands commands;
        std::string line;
        
        while (std::getline(input, line)) 
        {
            Command command;

            std::istringstream ss(line);
            std::string opcodeStr;
            ss >> opcodeStr;

            if (opcodeStr == "noop") 
            {
                command.opcode = Opcode::noop;
            } 
            else if (opcodeStr == "addx") 
            {
                command.opcode = Opcode::addx;
            }

            unsigned paramValue;
            if (ss >> paramValue)
            {
                command.param = paramValue;
            }

            commands.push_back(command);
        } 

        Register reg = main_part1(commands);
        main_part2(reg);
    }
   
    return 0;
}