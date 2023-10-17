#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include <set>

std::vector<std::string> ReadAssignments(std::ifstream& input)
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

void main_part1(const std::vector<std::string>& assignments)
{
    auto numberOfFullOverlaps = 0;

    auto isFullOverlap = [](unsigned start1, unsigned end1, unsigned start2, unsigned end2)
    {
        return (start1 >= start2 && end1 <= end2) || (start2 >= start1 && end2 <= end1);
    };

    auto checkCondition = [isFullOverlap, &numberOfFullOverlaps](std::string assignment)
    {
        unsigned start1, end1, start2, end2;

        if (sscanf(assignment.c_str(), "%d-%d,%d-%d", &start1, &end1, &start2, &end2) == 4 &&
            isFullOverlap(start1, end1, start2, end2))
        {
            numberOfFullOverlaps++;
        }        
    };

    std::for_each(assignments.begin(), assignments.end(), checkCondition);

    std::cout << "Day 4, part 1, answer is: " << numberOfFullOverlaps << std::endl;
}

void main_part2(const std::vector<std::string> assignments)
{
    auto numberOfPartlyOverlaps = 0;

    auto isPartlyOverlap = [](unsigned start1, unsigned end1, unsigned start2, unsigned end2)
    {
        return end1 >= start2 && end2 >= start1;
    };

    auto checkCondition = [isPartlyOverlap, &numberOfPartlyOverlaps](std::string assignment)
    {
        unsigned start1, end1, start2, end2;

        if (sscanf(assignment.c_str(), "%d-%d,%d-%d", &start1, &end1, &start2, &end2) == 4 &&
            isPartlyOverlap(start1, end1, start2, end2))
        {
            numberOfPartlyOverlaps++;
        }    
    };

    std::for_each(assignments.begin(), assignments.end(), checkCondition);

    std::cout << "Day 4, part 2, answer is: " << numberOfPartlyOverlaps << std::endl;
}

int main(void)
{
    std::ifstream input("../2022/day4/data/day4_input.txt");

    if(input.is_open())
    {
        auto assignments = ReadAssignments(input);

        main_part1(assignments);
        main_part2(assignments);
    }
}