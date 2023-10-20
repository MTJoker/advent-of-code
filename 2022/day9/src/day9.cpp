#include <iostream>
#include <fstream>
#include <sstream>
#include <set>

using Point = std::pair<int, int>;
using PointMap = std::set<Point>;
using Points = std::vector<Point>;

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

Points MoveTail(Point head, Points& tails, Instruction& instruction)
{
    for(auto& tail : tails)
    {
        if(!IsTouching(head, tail))
        {
            auto [headX, headY] = head;
            auto [tailX, tailY] = tail;

            auto xDistance = headX - tailX;
            auto yDistance = headY - tailY;

            if (yDistance > 1) yDistance = 1;
            else if (yDistance < -1) yDistance = -1;

            if (xDistance > 1) xDistance = 1;
            else if (xDistance < -1) xDistance = -1;

            tail.first += xDistance;
            tail.second += yDistance;
        }
        head = tail;
    }

    return tails;
}

Points HandleInstruction(Points& points, Instruction& instruction, PointMap& pointMap)
{
    auto headPos = points.front();    
    Points tails(points.begin() + 1, points.end());

    for(auto i = 0; i < instruction.steps; i++)
    {
        headPos = MoveHead(headPos, instruction);
        tails = MoveTail(headPos, tails, instruction);
        pointMap.insert(tails.back());
    }

    Points result;
    result.push_back(headPos);
    result.insert(result.end(), tails.begin(), tails.end());

    return result;
}

Points Initialize(Point head, unsigned numTails)
{
    auto tailPos = head;

    Points points;
    points.push_back(head);
    for(auto i = 0; i < numTails; i++)
    {
        points.push_back(tailPos);
    }

    return points;
}

void main_part1(Instructions instructions)
{
    auto head = Point(0, 0);

    auto points = Initialize(head, 1);
    auto pointMap = PointMap{head};

    for(auto& instruction : instructions)
    {
        points = HandleInstruction(points, instruction, pointMap);
    }

    std::cout << "Day 9, part 1, answer is: " << pointMap.size() << std::endl;
}

void main_part2(Instructions instructions)
{
    auto head = Point(0, 0);
    auto points = Initialize(head, 9);
    auto pointMap = PointMap{head};

    for(auto& instruction : instructions)
    {
        points = HandleInstruction(points, instruction, pointMap);
    }

    std::cout << "Day 9, part 2, answer is: " << pointMap.size() << std::endl;
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
        main_part2(instructions);
    }
   
    return 0;
}