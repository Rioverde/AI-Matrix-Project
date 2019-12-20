#include <iostream>
#include <fstream>
#include <string>
#include <sstream>

const int SizeOfGrid=12;
int Grid[SizeOfGrid][SizeOfGrid];

void GridStatus(int grid[][SizeOfGrid]) {
    std::ofstream output_file("GridStatusByDFS.txt");
    for (int i = 0; i < SizeOfGrid; i++)
    {
        output_file << "[";
        for (int j = 0; j < SizeOfGrid; j++)
        {
            if (output_file.is_open())
            {
                if (j != SizeOfGrid - 1)
                    output_file << grid[i][j] << ",";
                else
                    output_file << grid[i][j];
            }
        }
        output_file << "]" << std::endl;
    }
    output_file.close();
}

void dfs_brain();

void solutionCreator();

int main(){
    std::ifstream ReadGrid("gridStatus.txt");
    std::string line;
    for (int i = 0; i < SizeOfGrid; i++){
        getline(ReadGrid, line);
        std::stringstream ss(line.substr(1));
        std::string s;
        for (int j = 0; getline(ss, s, ','); j++)
        {
            Grid[i][j] = std::stoi(s);
        }
        line.clear();
    }
    GridStatus(Grid);
    return 0;
}