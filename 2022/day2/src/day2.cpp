#include <string>
#include <iostream>
#include <fstream>
#include <map>

typedef char instruction;

struct instructions
{
    instruction one;
    instruction two;
};

enum class Shape { rock , paper, scissors };
enum class GameResult { win, lose, draw };

std::vector<instructions> ReadStrategyGuide(std::ifstream& input)
{
    auto result = std::vector<instructions>{};

    instructions newInstruction;

    while (input >> newInstruction.one >> newInstruction.two)
    {
        result.push_back(newInstruction);
    }

    return result;
}

auto ToShape(char c)
{
    return    (c == 'A' || c == 'X') ? Shape::rock
            : (c == 'B' || c == 'Y') ? Shape::paper
            : (c == 'C' || c == 'Z') ? Shape::scissors
            : throw std::exception();
};

auto ToGameResult(char c)
{
    return    (c == 'X') ? GameResult::lose
            : (c == 'Y') ? GameResult::draw
            : (c == 'Z') ? GameResult::win
            : throw std::exception();
};

auto GetGamePoints(GameResult result)
{
    std::map<GameResult, unsigned> points
    { 
        {GameResult::lose, 0}, 
        {GameResult::draw, 3}, 
        {GameResult::win, 6} 
    };

    return points[result];
}

unsigned GetShapePoints(Shape shape)
{
    auto points = std::map<Shape, unsigned>
    { 
        {Shape::rock, 1}, 
        {Shape::paper, 2}, 
        {Shape::scissors, 3} 
    };

    return points[shape];
}

void main_part1(const std::vector<instructions> inst)
{
    unsigned points = 0;

    auto ApplyRules = [](Shape player, Shape opponent)
    {
        std::map<std::pair<Shape, Shape>, GameResult> rules
        {
            {{Shape::rock, Shape::scissors}, GameResult::win},
            {{Shape::rock, Shape::paper},    GameResult::lose},
            {{Shape::rock, Shape::rock},     GameResult::draw},

            {{Shape::scissors, Shape::paper},    GameResult::win},
            {{Shape::scissors, Shape::rock},     GameResult::lose},
            {{Shape::scissors, Shape::scissors}, GameResult::draw},
            
            {{Shape::paper, Shape::rock},     GameResult::win},
            {{Shape::paper, Shape::scissors}, GameResult::lose},
            {{Shape::paper, Shape::paper},    GameResult::draw}
        };

        return rules[std::make_pair(player, opponent)];
    };

    auto playRound = [ApplyRules, &points](instructions inst)
    {
        auto opponent = ToShape(inst.one);
        auto player = ToShape(inst.two);
        auto gameResult = ApplyRules(player, opponent);

        points += (GetShapePoints(player) + GetGamePoints(gameResult));
    };

    std::for_each(inst.begin(), inst.end(), playRound);

    std::cout << "Day 2, part 1, answer is: " << points << std::endl;
}

void main_part2(const std::vector<instructions> inst)
{
    unsigned points = 0;

    auto GetPlayerShape = [](Shape opponent, GameResult gameResult)
    {
        std::map<std::pair<Shape, GameResult>, Shape> rules
        {
            {{Shape::rock, GameResult::win},  Shape::paper},
            {{Shape::rock, GameResult::lose}, Shape::scissors},
            {{Shape::rock, GameResult::draw}, Shape::rock},

            {{Shape::scissors, GameResult::win},  Shape::rock},
            {{Shape::scissors, GameResult::lose}, Shape::paper},
            {{Shape::scissors, GameResult::draw}, Shape::scissors},
            
            {{Shape::paper, GameResult::win},  Shape::scissors},
            {{Shape::paper, GameResult::lose}, Shape::rock},
            {{Shape::paper, GameResult::draw}, Shape::paper}
        };

        return rules[std::make_pair(opponent, gameResult)];
    };

    auto playRound = [GetPlayerShape, &points](instructions inst)
    {
        auto opponent = ToShape(inst.one);
        auto gameResult = ToGameResult(inst.two);
        auto player = GetPlayerShape(opponent, gameResult);

        points += (GetShapePoints(player) + GetGamePoints(gameResult));
    };

    std::for_each(inst.begin(), inst.end(), playRound);

    std::cout << "Day 2, part 2, answer is: " << points << std::endl;
}

int main()
{
    std::ifstream input("../2022/day2/data/day2_input.txt", std::ios::in);

    if(input.is_open())
    {
        auto guide = ReadStrategyGuide(input);

        main_part1(guide);
        main_part2(guide);
    }
}