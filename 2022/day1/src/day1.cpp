#include <string>
#include <iostream>
#include <fstream>
#include <numeric>

auto countCalories(std::ifstream& input)
{
    auto result = std::vector<unsigned>{};
    unsigned caloriesCurrent = 0;

    while(input)
    {
        std::string line;
        std::getline(input, line);

        if(!line.empty())
        {
            caloriesCurrent += stoi(line);
        }
        else
        {
            result.push_back(caloriesCurrent);
            caloriesCurrent = 0;
        }        
    }

    std::sort(result.begin(), result.end(), std::greater<unsigned>());

    return result;
}

void main_part1(const std::vector<unsigned> calories)
{
    std::cout << "Day 1, part 1, answer is: " << calories[0] << std::endl;
}

void main_part2(const std::vector<unsigned> calories)
{
    std::cout << "Day 1, part 2, answer is: " << std::accumulate(calories.begin(), calories.begin() + 3, 0) << std::endl;
}

int main()
{
    std::ifstream input("../2022/day1/data/day1_input.txt");

    if(input.is_open())
    {
        auto calories = countCalories(input);

        main_part1(calories);
        main_part2(calories);
    }

    return 0;
}