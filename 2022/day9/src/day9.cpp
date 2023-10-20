#include <iostream>
#include <fstream>
#include <sstream>
#include <set>

using Point = std::pair<int, int>;
using PointMap = std::set<Point>;
using Points = std::tuple<Point, Point>;

struct Instruction
{
  Instruction(char direction, size_t steps) 
  : direction(direction)
  , steps(steps)
  {};

  char direction;
  size_t steps;
};

using Instructions = std::vector<Instruction>;

bool IsTouching(Point& headPos, Point& tailPos)
{
    auto [headX, headY] = headPos;
    auto [tailX, tailY] = tailPos;

    auto xDistance = std::abs(headX - tailX);
    auto yDistance = std::abs(headY - tailY);

    bool touching =  (xDistance <= 1) && (yDistance <= 1);
    return touching;
}

Point MoveHead(Point& headStartPos, Instruction& instruction)
{
    if(instruction.direction == 'L') { return Point(headStartPos.first - 1, headStartPos.second); }
    if(instruction.direction == 'R') { return Point(headStartPos.first + 1, headStartPos.second); }
    if(instruction.direction == 'D') { return Point(headStartPos.first, headStartPos.second - 1); }
    if(instruction.direction == 'U') { return Point(headStartPos.first, headStartPos.second + 1); }
    throw;
} 

Point MoveTail(Point& headPos, Point& tailStartPos, Instruction& instruction)
{
    auto newTailPos = tailStartPos;

    if(!IsTouching(headPos, tailStartPos))
    {
        auto [headX, headY] = headPos;
        auto [tailX, tailY] = tailStartPos;

        auto xDistance = headX - tailX;
        auto yDistance = headY - tailY;

        if (yDistance > 1) yDistance = 1;
        else if (yDistance < -1) yDistance = -1;

        if (xDistance > 1) xDistance = 1;
        else if (xDistance < -1) xDistance = -1;

        newTailPos.first += xDistance;
        newTailPos.second += yDistance;
    }

    return newTailPos;
}

Points HandleInstruction(Points& startPos, Instruction& instruction, PointMap& pointMap)
{
    Points endPos = startPos;

    auto [headPos, tailPos] = startPos;

    for(auto i = 0; i < instruction.steps; i++)
    {
        headPos = MoveHead(headPos, instruction);
        tailPos = MoveTail(headPos, tailPos, instruction);
        pointMap.insert(tailPos);
    }

    return {headPos, tailPos};
}

void main_part1(Instructions instructions)
{
    auto headPos = Point(0, 0);
    auto tailPos = Point(0, 0);
    auto positions = Points(headPos, tailPos);

    auto pointMap = PointMap{tailPos};

    for(auto& instruction : instructions)
    {
        positions = HandleInstruction(positions, instruction, pointMap);
    }

    std::cout << "Day 9, part 1, answer is: " << pointMap.size() << std::endl;
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
        Instructions instructions;

        std::string line;
        while (std::getline(input, line)) 
        {
            char direction;
            size_t steps;

            std::istringstream ss(line);
            ss >> direction >> steps;

            Instruction instruction(direction, steps); // convert from stack to index
            instructions.push_back(instruction);
        } 

        main_part1(instructions);
        main_part2();
    }
   
    return 0;
}