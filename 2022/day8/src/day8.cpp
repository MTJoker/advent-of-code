#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using Grid = std::vector<std::vector<unsigned>>;

unsigned CalculateHighestScenicScore(Grid grid)
{
    auto rowCount = grid.size();
    auto colCount = grid[0].size();
    auto highestScore = 0;
    auto currentScore = 0;

    for (auto currentRow = 1; currentRow < rowCount-1; ++currentRow) 
    {
        for (auto currentCol = 1; currentCol < colCount-1; ++currentCol) 
        {
            auto currentHeight = grid[currentRow][currentCol];

            unsigned visibleLeft = 1;
            unsigned visibleRight = 1;
            unsigned visibleTop = 1;
            unsigned visibleBottom = 1;

            // Check to the left
            for (auto col = currentCol - 1; col > 0; --col) 
            {
                if (grid[currentRow][col] >= currentHeight) 
                {
                    break;
                }
                visibleLeft++;
            }

            // Check to the right
            for (auto col = currentCol + 1; col < colCount-1; ++col) 
            {
                if (grid[currentRow][col] >= currentHeight) 
                {
                    break;
                }
                visibleRight++;
            }

            // Check to the top
            for (auto row = currentRow - 1; row > 0; --row) 
            {
                if (grid[row][currentCol] >= currentHeight) 
                {
                    break;
                }
                visibleTop++;
            }

            // Check to the bottom
            for (int row = currentRow + 1; row < rowCount-1; ++row) 
            {
                if (grid[row][currentCol] >= currentHeight) 
                {
                    break;
                }
                visibleBottom++;
            }

            currentScore = visibleLeft * visibleRight * visibleTop * visibleBottom;
            highestScore = (currentScore > highestScore) ? currentScore : highestScore;
        }
    }    

    return highestScore;
}

unsigned CountVisibleTrees(Grid grid)
{
    auto rowCount = grid.size();
    auto colCount = grid[0].size();
    auto count = 0;

    for (auto currentRow = 0; currentRow < rowCount; ++currentRow) 
    {
        for (auto currentCol = 0; currentCol < colCount; ++currentCol) 
        {
            auto currentHeight = grid[currentRow][currentCol];

            bool visibleFromLeft = true;
            bool visibleFromRight = true;
            bool visibleFromTop = true;
            bool visibleFromBottom = true;

            // Check to the left
            for (auto col = currentCol - 1; col >= 0; --col) 
            {
                if (grid[currentRow][col] >= currentHeight) 
                {
                    visibleFromLeft = false;
                    break;
                }
            }

            // Check to the right
            for (auto col = currentCol + 1; col < colCount; ++col) 
            {
                if (grid[currentRow][col] >= currentHeight) 
                {
                    visibleFromRight = false;
                    break;
                }
            }

            // Check to the top
            for (auto row = currentRow - 1; row >= 0; --row) 
            {
                if (grid[row][currentCol] >= currentHeight) 
                {
                    visibleFromTop = false;
                    break;
                }
            }

            // Check to the bottom
            for (int row = currentRow + 1; row < rowCount; ++row) 
            {
                if (grid[row][currentCol] >= currentHeight) 
                {
                    visibleFromBottom = false;
                    break;
                }
            }

            if (visibleFromLeft || visibleFromRight || visibleFromTop || visibleFromBottom) 
            {
                count++;
            }
        }
    }

    return count;
}

void main_part1(Grid& grid)
{
    unsigned visibleTreeCount = CountVisibleTrees(grid);
    std::cout << "Day 8, part 1, answer is: " << visibleTreeCount << std::endl;
}

void main_part2(Grid& grid)
{
    unsigned score = CalculateHighestScenicScore(grid);
    std::cout << "Day 8, part 2, answer is: " << score << std::endl;
}

int main(void)
{
    std::fstream input("../2022/day8/data/day8_input.txt");

    Grid grid;
    std::string line;

    while (std::getline(input, line)) 
    {
        std::vector<unsigned> row;
        for (char c : line) 
        {
            row.push_back(std::stoi(std::string(1, c))); 
        }
        grid.push_back(row);
    }

    if(input.is_open())
    {
        main_part1(grid);
        main_part2(grid);
    }
   
    return 0;
}