#include <iostream>
#include <fstream>
#include <vector>
#include <stack>

struct Grid{
    int cell_number, value;
};

const int sizeOfGrid = 12;
Grid myGrid[sizeOfGrid][sizeOfGrid];

void ReadToGrid();

int visitedInVector(std::vector<int>& visitedNodes, int digit){
    for(unsigned int i=0;i<visitedNodes.size(); i++)
        if(visitedNodes.at(i) == digit) return 1;
    return 0;
}

std::vector<int> DfsAlgorithm(int start[], int end[], Grid myGrid[][sizeOfGrid]){
    std::vector<int> visitedNodes;
    std::stack<int> stack;
    int up=2, down=2, left=-1, right=3, nodes[500];
    int start = myGrid[start[0]][start[1]].cell_number;
    int end = myGrid[end[0]][end[1]].cell_number;
    visitedNodes.push_back(*start);
    while(true){
        int i=0;
        for(int j=i,k; j<4;)
    }

}

int main(){
    int count=1;
    for(int i=0;i<sizeOfGrid; i++){
        for(int j=0;j<sizeOfGrid; j++){
            myGrid[i][j].cell_number=count;
            count++;
        }
    }
    return 0;
}