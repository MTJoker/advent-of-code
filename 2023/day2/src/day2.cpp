#include <iostream>
#include <fstream>

void main_part1()
{
    auto x = 0;
    std::cout << "Day 2, part 1, answer is: " << x << std::endl;
}

void main_part2()
{
    auto x = 0;
    std::cout << "Day 2, part 2, answer is: " << x << std::endl;
}

int main()
{
    std::ifstream input("../2023/day2/data/day2_input.txt");

    if(input.is_open())
    {
        main_part1();
        main_part2();
    }

    return 0;
}