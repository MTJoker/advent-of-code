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

    std::string line;

    while(std::getline(input, line))
    {
        if(line == "$ cd /")
        {
            continue;   // ignore
        }
        else if(line == "$ cd ..")
        {
            if(pCurDir->parent)
            {
                pCurDir = pCurDir->parent;
            }
            else throw;       
        }
        else if(line.substr(0, 4) == "$ cd")
        {
            bool haveDir = false;
            auto dirName = line.substr(5);

            for(auto& dir : pCurDir->subdirectories)
            {
                if(dir.name == dirName)
                {
                    haveDir = true;
                    pCurDir = &dir;
                    break;
                }
            }

            if(!haveDir) throw;
        }
        else if(line.find("$ ls") != std::string::npos)
        {
            continue;   // ignore
        }
        else if(line.substr(0, 3) == "dir")
        {
            Directory dir(line.substr(4), pCurDir);
            pCurDir->subdirectories.push_back(dir);
        }
        else
        {
            if(!std::isdigit(line[0])) 
            {
                throw;
            }
            unsigned fileSize;
            std::string fileName;
            std::istringstream ss(line);
            ss >> fileSize >> fileName;

            if(fileSize == 0) throw;

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

unsigned GetTotalSizeLimited(Directory& tree, unsigned limit)
{
    unsigned result = 0;
    if(tree.dirSize <= limit)
    {
        result += tree.dirSize;
    }
    for(auto& subDir : tree.subdirectories)
    {
        result += GetTotalSizeLimited(subDir, limit);
    }

    return result;
}

void GetDirecorySizesBiggerThan(Directory& tree, unsigned size, std::vector<unsigned>& sizes)
{
    if(tree.dirSize >= size)
    {
        sizes.push_back(tree.dirSize);

        for(auto& subDir : tree.subdirectories)
        {
            GetDirecorySizesBiggerThan(subDir, size, sizes);
        }
    }
}

void main_part1(Directory root)
{
    unsigned limit = 100000;
    unsigned result = GetTotalSizeLimited(root, limit);

    std::cout << "Day 7, part 1, answer is: " << result << std::endl;
}

void main_part2(Directory root)
{
    unsigned freeSpace = 70000000 - root.dirSize;
    unsigned neededAdditionalSpace = 30000000 - freeSpace;

    std::vector<unsigned> sizes;
    GetDirecorySizesBiggerThan(root, neededAdditionalSpace, sizes);

    std::sort(sizes.begin(), sizes.end(), std::greater<unsigned>());

    std::cout << "Day 7, part 2, answer is: " << sizes.back() << std::endl;
}

int main(void)
{
    std::ifstream input("../2022/day7/data/day7_input.txt");

    if(input.is_open())
    {
        auto root = BuildDirTree(input);

        main_part1(root);
        main_part2(root);
    }
   
    return 0;
}