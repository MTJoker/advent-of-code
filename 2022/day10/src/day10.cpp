#include <iostream>
#include <fstream>

void main_part1()
{
    std::cout << "Day 10, part 1, answer is: " << 0 << std::endl;
}

void main_part2()
{
    std::cout << "Day 10, part 2, answer is: " << 0 << std::endl;
}

int main(void)
{
    std::fstream input("../2022/day10/data/day10_input.txt");

    if(input.is_open())
    {

        main_part1();
        main_part2();
    }
   
    return 0;
}