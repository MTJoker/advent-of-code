#include <unordered_set>
#include <fstream>
#include <iostream>
#include <sstream>

unsigned DetectConsecutiveChars(std::string message, unsigned areaSize)
{
    std::vector<char> currentChars;
    unsigned position = 0;
    unsigned charCount = 0;

    for (int i = 0; i < message.length(); ++i) 
    {
        charCount++;

        if(std::find(currentChars.begin(), currentChars.end(), message[i]) == currentChars.end())
        {
            currentChars.push_back(message[i]);

            if (currentChars.size() == areaSize) 
            {
                position = charCount;
                break;
            }
        }
        else
        {
            currentChars.clear();
        }                
    }

    return position;
}

void main_part1(std::string message)
{
    auto searchedChars = DetectConsecutiveChars(message, 4);
    std::cout << "Day 6, part 1, answer is: " << searchedChars << std::endl;
}

void main_part2(std::string message)
{
    auto searchedChars = DetectConsecutiveChars(message, 14);
    std::cout << "Day 6, part 2, answer is: " << searchedChars << std::endl;
}

int main(void)
{
    std::ifstream input("../2022/day6/data/day6_input.txt");

    if(input.is_open())
    {
        std::string message;
        std::getline(input, message);

        main_part1(message);
        main_part2(message);
    }
   
    return 0;
}