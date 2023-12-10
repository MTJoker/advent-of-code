#include <iostream>
#include <fstream>
#include <sstream>
#include <map>

struct Cube
{
    enum class Color { RED, GREEN, BLUE } color;
    int64_t count;
};

struct Game
{
    int64_t id;
    std::map<Cube::Color, int64_t> max;
};

std::istringstream& operator >> (std::istringstream& ss, Cube& cube)
{
    // count
    ss >> cube.count;
    ss.ignore(1);
    char  c = ss.peek();
    if(c != -1)
    {
        switch(c)
        {
            case 'r': cube.color = Cube::Color::RED;   ss.ignore(3); break;
            case 'g': cube.color = Cube::Color::GREEN; ss.ignore(5); break;
            case 'b': cube.color = Cube::Color::BLUE;  ss.ignore(4); break;
            default: throw std::runtime_error("invalid color");
        }
    }

    return ss;
}

std::vector<Game> ParseGames(std::ifstream& input)
{
    std::vector<Game> games;
    std::string line;

    while (std::getline(input, line)) 
    {
        Game game;

        // first, pare content of type: "Game _:"
        std::istringstream ss(line);
        if(ss.peek() != 'G')
        {
            throw std::runtime_error("Invalid line");
        }

        ss.ignore(5);
        ss >> game.id;
        ss.ignore(1);

        // now parse cube information
        Cube cube;
    
        while(ss >> cube)
        {
            game.max[cube.color] = std::max(cube.count, game.max[cube.color]);
            if(auto separator = ss.get(); separator == ',' || separator == ';')
            {
                continue;
            }
        }

        games.push_back(game);
    }

    return games;
}

void main_part1(std::vector<Game>& games)
{
    auto isPossible = [](Game& game)
    {
        return ( (game.max[Cube::Color::RED]   <= 12) && 
                 (game.max[Cube::Color::GREEN] <= 13) &&
                 (game.max[Cube::Color::BLUE]  <= 14) ); 
    };

    auto sumOfIds = 0;

    for(auto&game : games)
    {
        if(isPossible(game))
        {
            sumOfIds += game.id;
        }
    }

    std::cout << "Day 2, part 1, answer is: " << sumOfIds << std::endl;
}

void main_part2(std::vector<Game>& games)
{
    auto power = [](Game& game)
    {
        return ( game.max[Cube::Color::RED] *
                 game.max[Cube::Color::GREEN] *
                 game.max[Cube::Color::BLUE] ); 
    };

    auto sumOfPower = 0;

    for(auto&game : games)
    {
        sumOfPower += power(game);
    }

    std::cout << "Day 2, part 2, answer is: " << sumOfPower << std::endl;
}

int main()
{
    std::ifstream input("../2023/day2/data/day2_input.txt");

    if(input.is_open())
    {
        auto games = ParseGames(input);
        main_part1(games);
        main_part2(games);
    }

    return 0;
}