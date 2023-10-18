#include <iostream>
#include <fstream>
#include <sstream>

class File 
{
public:
    File(const std::string& name, unsigned size) : name(name), size(size) {}

private:    
    std::string name;
    unsigned size;
};

class Directory 
{
public:
    Directory(const std::string& name) : name(name), parent(nullptr), dirSize(0) {}
    Directory(const std::string& name, Directory* parent) : name(name), parent(parent), dirSize(0) {}

    Directory* parent;
    std::string name;
    std::vector<File> files;
    std::vector<Directory> subdirectories;
    unsigned dirSize;
};

Directory BuildDirTree(std::ifstream& input)
{    
    Directory root("/");
    Directory* pCurDir = &root;

    while(input)
    {
        std::string line;
        std::getline(input, line);

        if(line == "$ cd /")
        {
            continue;
        }
        else if(line == "$ cd ..")
        {
            pCurDir = pCurDir->parent;        
        }
        else if(line.substr(0, 4) == "$ cd")
        {
            auto dirName = line.substr(5);
            for(auto& dir : pCurDir->subdirectories)
            {
                if(dir.name == dirName)
                {
                    pCurDir = &dir;
                    break;
                }
            }
        }
        else if(line.find("$ ls") != std::string::npos)
        {
            continue;
        }
        else if(line.substr(0, 3) == "dir")
        {
            Directory dir(line.substr(4), pCurDir);
            pCurDir->subdirectories.push_back(dir);
        }
        else
        {
            unsigned fileSize;
            std::string fileName;
            std::istringstream ss(line);
            ss >> fileSize >> fileName;

            File file(fileName, fileSize); 
            
            pCurDir->dirSize += fileSize;

            Directory* tmp = pCurDir;
            while(tmp->parent)
            {
                tmp = tmp->parent;
                tmp->dirSize += fileSize;
            }

            pCurDir->files.push_back(file);                               
        }
    }

    return root;
}

unsigned GetDirSize(Directory& tree, unsigned limit)
{
    unsigned result = 0;
    if(tree.dirSize < limit)
    {
        result += tree.dirSize;
    }
    for(auto& subDir : tree.subdirectories)
    {
        if(subDir.dirSize < limit)
        {
            result += subDir.dirSize;
        }
        else
        {
            result += GetDirSize(subDir, limit);
        }
    }

    return result;
}

void main_part1(Directory root)
{
    unsigned limit = 100000;
    unsigned result = GetDirSize(root, limit);

    std::cout << "Day 7, part 1, answer is: " << result << std::endl;
}

void main_part2()
{
    std::cout << "Day 7, part 2, answer is: " << 0 << std::endl;
}

int main(void)
{
    std::ifstream input("../2022/day7/data/day7_input.txt");

    if(input.is_open())
    {
        auto treeRoot = BuildDirTree(input);

        main_part1(treeRoot);
        main_part2();
    }
   
    return 0;
}