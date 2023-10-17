#include <string>
#include <iostream>
#include <fstream>

std::vector<std::string> ReadContents(std::ifstream& input)
{
    auto result = std::vector<std::string>{};

    while(input)
    {
        std::string line;
        std::getline(input, line);

        result.push_back(line);     
    }

    return result;
}

auto GetPrio(char item)
{
    return std::islower(item) ? item - 'a' + 1 : std::tolower(item) - 'a' + 1 + 26;
}

void main_part1(std::vector<std::string> content)
{
    unsigned prio = 0;

    auto FindDuplicates = [&prio](std::string content)
    {
        auto compartment1 = content.substr(0, content.length()/2);
        auto compartment2 = content.substr(content.length()/2);

        for (char item : compartment1) 
        {
            if (compartment2.find(item) != std::string::npos) 
            {
                prio += GetPrio(item);
                break;
            }
        }
    };

    std::for_each(content.begin(), content.end(), FindDuplicates);

    std::cout << "Day 3, part 1, answer is: " << prio << std::endl;
}

void main_part2(std::vector<std::string> content)
{
    unsigned prio = 0;

    for (auto i = 0; i < content.size(); i += 3)
    {
        std::vector<std::string> group;
        group.insert(group.end(), content.begin() + i, content.begin() + i + 3);

        for (char item : group[0]) 
        {
            if (group[1].find(item) != std::string::npos && group[2].find(item) != std::string::npos) 
            {
                prio += GetPrio(item);
                break;
            }
        }
    }

    std::cout << "Day 3, part 2, answer is: " << prio << std::endl;
}

int main(void)
{
    std::ifstream input("../2022/day3/data/day3_input.txt", std::ios::in);

    if(input.is_open())
    {
        auto content = ReadContents(input);

        main_part1(content);
        main_part2(content);
    }
}