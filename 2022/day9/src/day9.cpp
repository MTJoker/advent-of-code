#include <iostream>
#include <fstream>

void main_part1()
{
    std::cout << "Day 9, part 1, answer is: " << 0 << std::endl;
}

void main_part2()
{
    std::cout << "Day 9, part 2, answer is: " << 0 << std::endl;
}

int main(void)
{
    std::fstream input("../2022/day9/data/day9_input.txt");

    if(input.is_open())
    {
        main_part1();
        main_part2();
    }
   
    return 0;
}