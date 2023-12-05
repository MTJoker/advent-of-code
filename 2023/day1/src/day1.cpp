#include <iostream>
#include <fstream>

std::vector<std::string> ReadContents(std::ifstream& input)
{
    auto result = std::vector<std::string>{};
    std::string line;

    while (std::getline(input, line)) 
    {
        result.push_back(line);     
    }

    return result;
}

auto sumOfCalibrationValues(std::vector<std::string>& content)
{
    uint sum = 0;

    for(const std::string& line : content)
    {
        int firstDigit = -1;
        int lastDigit = -1;

        for (char c : line) 
        {
            if (std::isdigit(c)) 
            {
                if (firstDigit == -1) 
                {
                    firstDigit = c - '0';
                }
                lastDigit = c - '0';
            }
        }

        if(firstDigit == -1 && lastDigit == -1)
        {
            throw;
        }
        
        sum += firstDigit * 10 + lastDigit;
    }

    return sum;
}

auto sumOfCalibrationValuesWordBased(std::vector<std::string>& content)
{
    int sum = 0;

    const std::string digitNames[] = {
        "zero",
        "one",
        "two",
        "three",
        "four",
        "five",
        "six",
        "seven",
        "eight",
        "nine",
    };

    auto numberOfDigitNames = sizeof(digitNames) / sizeof(digitNames[0]);

    for(auto line : content)
    {
        auto isDigit = [](char c) { return std::isdigit(c); };

        auto firstWordDigitIter = line.end();
        auto firstWordDigitValue = 0;
        for (int i = 0; i < numberOfDigitNames; i++) 
        {
            auto digitWordIter = std::search(line.begin(), line.end(), digitNames[i].begin(), digitNames[i].end());
            if (digitWordIter <= firstWordDigitIter) 
            {
                firstWordDigitIter = digitWordIter;
                firstWordDigitValue = i;
            }
        }

        auto firstDigitIter = std::find_if(line.begin(), line.end(), isDigit);

        sum += (firstWordDigitIter > firstDigitIter) ? static_cast<int>(*firstDigitIter - '0') * 10 : firstWordDigitValue * 10;

        auto lastWordDigitIter = line.rend();
        int lastWordDigitValue = 0;
        for (int i = 0; i < numberOfDigitNames; i++) 
        {
            auto digitWordIter = std::search(line.rbegin(), line.rend(), digitNames[i].rbegin(), digitNames[i].rend());
            if (digitWordIter <= lastWordDigitIter) 
            {
                lastWordDigitIter = digitWordIter;
                lastWordDigitValue = i;
            }
        }

        auto lastDigitIter = std::find_if(line.rbegin(), line.rend(), isDigit);

        sum += (lastWordDigitIter > lastDigitIter) ? static_cast<int>(*lastDigitIter - '0') : lastWordDigitValue;
    }

    return sum;
}

void main_part1(std::vector<std::string>& content)
{
    std::cout << "Day 1, part 1, answer is: " << sumOfCalibrationValues(content) << std::endl;
}

void main_part2(std::vector<std::string>& content)
{
    std::cout << "Day 1, part 2, answer is: " << sumOfCalibrationValuesWordBased(content) << std::endl;
}

int main()
{
    std::ifstream input("../2023/day1/data/day1_input.txt");

    auto content = ReadContents(input);

    main_part1(content);
    main_part2(content);

    return 0;
}