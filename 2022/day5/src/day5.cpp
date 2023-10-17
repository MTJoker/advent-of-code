#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <sstream>

struct Instruction
{
    Instruction(int amount, int src, int dest)
    : amount(amount)
    , src(src)
    , dest(dest)
    {}
    int amount;
    int src;
    int dest;
};

std::vector<std::vector<char> > CreateStacks()
{
    std::vector<std::vector<char> > stacks;

    // sorry, too lazy to read that from the file
    stacks.push_back({'L', 'N', 'W', 'T', 'D'});
    stacks.push_back({'C', 'P', 'H'});
    stacks.push_back({'W', 'P', 'H', 'N', 'D', 'G', 'M', 'J'});
    stacks.push_back({'C', 'W', 'S', 'N', 'T', 'Q', 'L'});
    stacks.push_back({'P', 'H', 'C', 'N'});
    stacks.push_back({'T', 'H', 'N', 'D', 'M', 'W', 'Q', 'B'});
    stacks.push_back({'M', 'B', 'R', 'J', 'G', 'S', 'L'});
    stacks.push_back({'Z', 'N', 'W', 'G', 'V', 'B', 'R', 'T'});
    stacks.push_back({'W', 'G', 'D', 'N', 'P', 'L'});

    return stacks;
}

std::vector<Instruction> CreateInstructions(std::ifstream& input)
{
    std::vector<Instruction> instructions;

    std::string line;

    while (std::getline(input, line)) 
    {
        int amount, src, dest;
        std::string action;
        
        std::istringstream ss(line);
        ss >> action >> amount >> action >> src >> action >> dest;

        Instruction instruction(amount, --src, --dest); // convert from stack to index
        instructions.push_back(instruction);
    }    

    return instructions;
}

void main_part1(std::vector<std::vector<char> > stacks, const std::vector<Instruction> instructions)
{
    for(auto instruction : instructions)
    {        
        for(int moves = 0; moves < instruction.amount; moves++)
        {
            stacks[instruction.dest].push_back(stacks[instruction.src].back());
            stacks[instruction.src].pop_back();
        }
    }

    std::cout << "Day 5, part 1, answer is: "; 
    for (auto stack : stacks)
    {
        std::cout << stack.back();
    }   
    std::cout << std::endl;
}

void main_part2(std::vector<std::vector<char> > stacks, const std::vector<Instruction> instructions)
{
    for(auto instruction : instructions)
    {   
        auto srcStartIt = stacks[instruction.src].end() - instruction.amount;
        auto srcEndIt = stacks[instruction.src].end();

        std::vector<char> srcRange(srcStartIt, srcEndIt);

        stacks[instruction.dest].insert(stacks[instruction.dest].end(), srcRange.begin(), srcRange.end());
        stacks[instruction.src].erase(srcStartIt, srcEndIt);
    }

    std::cout << "Day 5, part 2, answer is: "; 
    for (auto stack : stacks)
    {
        std::cout << stack.back();
    }   
    std::cout << std::endl;
}

int main(void)
{
    std::ifstream input("../2022/day5/data/day5_input.txt");

    if(input.is_open())
    {
        auto stacks = CreateStacks();
        auto instructions = CreateInstructions(input);

        main_part1(stacks, instructions);
        main_part2(stacks, instructions);
    }
   
    return 0;
}