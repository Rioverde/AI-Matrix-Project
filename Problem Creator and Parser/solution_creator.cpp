#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <vector>

struct Grid{
    int cell_number, value;
};

std::vector<int> visited;
const int sizeOfGrid = 12, up=-2, down=2, left=-1, right=3;
int start[] = {8, 5}, end[] = {1, 2};
int storeCell[sizeOfGrid][sizeOfGrid];
bool GoalFound = false;
int count = 0;
Grid myGrid[sizeOfGrid][sizeOfGrid];

void SetGrid(){
    std::ifstream ReadGrid("gridStatus.txt");
    if(!ReadGrid.is_open()) exit(1);
    std::string line;
    int count = 1;
    for(int i=0;i<sizeOfGrid; i++)
        for(int j=0;j<sizeOfGrid; j++,count++)
            myGrid[i][j].cell_number=count;

    for (int i = 0; i < sizeOfGrid; i++){
        getline(ReadGrid, line);
        std::stringstream ss(line.substr(1));
        std::string s;
        for (int j = 0; getline(ss, s, ','); j++)
            myGrid[i][j].value = std::stoi(s);
        line.clear();
    }
}

bool isOdd(int n){
    return n % 2 != 0;
}

class Graph{
    private:
        std::list<int> *adj;
        void DFS_helper(int s, bool *visited);
    public:
        int verticesVariable;
        Graph(int vertices);
        void addEdge(int parent_vertex, int child_vertex);
        void DFS(int start_vertex);
};

Graph::Graph (int vertices){
    verticesVariable = vertices;
    adj = new std::list<int>[vertices];
}

void Graph::addEdge(int parent_vertex, int child_vertex){
    adj[parent_vertex].push_back(child_vertex);
}

void Graph::DFS_helper(int s, bool *visited){
    std::cout<< "Visiting Node " << s << std::endl;
    visited[s] = true;
    for(auto i = adj[s].begin(); i != adj[s].end(); i++){
        if(!visited[*i]){
            std::cout << "Going to vertex " << *i << " from vertex " << s << std::endl;
            DFS_helper(*i, visited);
        }
    }
}

void Graph::DFS(int s){
    bool *visited = new bool[verticesVariable];
    for(int i = 0; i < verticesVariable; i++) visited[i] = false;
    DFS_helper(s, visited);
}


bool checkVisitor(int cellNumber){
    for(unsigned int i = 0; i<visited.size(); i++)
        if(cellNumber == visited.at(i)) return true;
    return false;
}

int EdgeCounter(int start[1], int end[1]){
    if(count>552) return count;
    int up_digit = myGrid[start[0]+up][start[1]].cell_number, down_digit = myGrid[start[0]+down][start[1]].cell_number,
            left_digit = myGrid[start[0]][start[1]+left].cell_number, right_digit = myGrid[start[0]][start[1]+right].cell_number,
            end_digit = myGrid[end[0]][end[1]].cell_number;

    if(GoalFound) return count;

    std::cout<< up_digit << " :Going upper" << std::endl;

    if((up_digit > 0 && up_digit < 145)){
        count++;
        if(up_digit == end_digit) {
            GoalFound = true;
            std::cout << "Goal Found" << std::endl;
            return count;
        }
        if(checkVisitor(up_digit)) {
            std::cout << up_digit << " :Similarities found!" << std::endl;
            goto downer;
        }
        visited.push_back(up_digit);
        std::cout << up_digit << " pushed and up " << count << std::endl;
        int init[] = {start[0]+up, start[1]};
        EdgeCounter(init, end);
    }

    downer:

    std::cout<< down_digit << " :Going down" << std::endl;

    if(down_digit > 0 && down_digit < 145){
        count++;
        if(down_digit == end_digit) {
            GoalFound = true;
            std::cout << "Goal Found" << std::endl;
            return count;
        }
        if(checkVisitor(down_digit)) {
            std::cout << down_digit << " :Similarities found!" << std::endl;
            goto lefter;
        }
        visited.push_back(down_digit);
        std::cout << down_digit << " pushed and down " << count << std::endl;
        int init[] = {start[0]+down, start[1]};
        EdgeCounter(init, end);
    }

    lefter:

    std::cout<< left_digit << " :Going lefter" << std::endl;

    if(left_digit > 0 && left_digit < 145){
        count++;
        if(left_digit == end_digit) {
            GoalFound = true;
            std::cout << "Goal Found" << std::endl;
            return count;
        }
        if(checkVisitor(left_digit)) {
            std::cout << left_digit << " :Similarities found!" << std::endl;
            goto righter;
        }
        visited.push_back(left_digit);
        std::cout << left_digit << " pushed and down " << count << std::endl;
        int init[] = {start[0], start[1]+left};
        EdgeCounter(init, end);
    }

    righter:

    std::cout << right_digit << " :Going righter" << std::endl;

    if(right_digit > 0 && right_digit < 145){
        count++;
        if(right_digit == end_digit) {
            GoalFound = true;
            std::cout << "Goal Found" << std::endl;
            return count;
        }
        if(checkVisitor(right_digit)) {
            std::cout << right_digit << " :Similarities found!" << std::endl;
            return count;
        }
        visited.push_back(right_digit);
        std::cout << right_digit << " pushed and down " << count << std::endl;
        int init[] = {start[0], start[1]+right};
        EdgeCounter(init, end);
    }

    return count;
}
void EdgeAdder(Graph& g);
void SolutionCreator();

int main(){                                                                     // 2n^2-2n is the formula for number of nodes in a grid(nxn)
    SetGrid();                                                                  //  where 'n' is number of cells on each side.
    // For 12x12 grid, we have 552 Nodes
    visited.clear();
    Graph g(EdgeCounter(start, end));
//    EdgeAdder(g);
//    g.DFS(myGrid[s])
    std::cout << myGrid[start[0]][start[1]].cell_number << std::endl;
    return 0;
}