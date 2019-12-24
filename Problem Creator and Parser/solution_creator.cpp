#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <vector>

struct Grid{
    int cell_number, value;
};

std::vector<int> visited, storedEdges[2], path;
const int sizeOfGrid = 8, up=-2, down=2, left=-1, right=3;
int storeCell[sizeOfGrid][sizeOfGrid], coordinates[2];
bool GoalFound = false, GoalCheck = false;
int count = 0;
Grid myGrid[sizeOfGrid][sizeOfGrid];

void SolutionCreator();
void SetGrid(){
    std::ifstream ReadGrid("gridStatus.txt");
    if(!ReadGrid.is_open()) exit(1);
    std::string line;
    int counting = 1;
    for(auto & i : myGrid)
        for(int j=0;j<sizeOfGrid; j++,counting++)
            i[j].cell_number=counting;

    for (auto & i : myGrid){
        getline(ReadGrid, line);
        std::stringstream ss(line.substr(1));
        std::string s;
        for (int j = 0; getline(ss, s, ','); j++)
            i[j].value = std::stoi(s);
        line.clear();
    }
}
bool isOdd(int n){
    return n % 2 != 0;
}

class Graph{
private:
    int verticesVariable;
    std::list<int> *adj;
    void DFS_helper(int s, bool *visited, int goal);
public:
    explicit Graph(int vertices);
    ~Graph();
    void addEdge(int parent_vertex, int child_vertex);
    void DFS(int start_vertex, int goal);
};

Graph::Graph (int vertices){
    verticesVariable = vertices;
    adj = new std::list<int>[vertices];
}
Graph::~Graph(){
    delete [] adj;
}

void Graph::addEdge(int parent_vertex, int child_vertex){
    adj[parent_vertex].push_back(child_vertex);
}

void Graph::DFS_helper(int s, bool *visited, int goal){
    if(GoalCheck) return;
    std::cout<< "Visiting Node " << s << std::endl;
    path.push_back(s);
    if (s == goal) {
        GoalCheck = true;
        std::cout << "Found Goal: " << goal << std::endl;
        for(int i=0; i < path.size(); i++){
            if(i==path.size()-1){
                std::cout<< path.at(i) << " == END"<< std::endl;
                break;
            }
            std::cout<< path.at(i) << " ==> ";
        }
        ;
    }
    visited[s] = true;
    for(auto i = adj[s].begin(); i != adj[s].end(); i++){
        if(GoalCheck) return;
        if(!visited[*i]){
            std::cout << "Going to vertex " << *i << " from vertex " << s << std::endl;
            DFS_helper(*i, visited, goal);
        }
    }
}

void Graph::DFS(int s, int goal){
    bool *visited = new bool[verticesVariable];
    for(int i = 0; i < verticesVariable; i++) visited[i] = false;
    DFS_helper(s, visited, goal);
}


bool checkVisitor(int cellNumber){
    for(unsigned int i = 0; i<visited.size(); i++)
        if(cellNumber == visited.at(i)) return true;
    return false;
}                       // Checks with storage is cell is visited or not.
int EdgeCounter(int starter[1], int ender[1]){
    if(count>552) return count;
    int up_digit = myGrid[starter[0] + up][starter[1]].cell_number, down_digit = myGrid[starter[0] + down][starter[1]].cell_number,
            left_digit = myGrid[starter[0]][starter[1] + left].cell_number, right_digit = myGrid[starter[0]][starter[1] + right].cell_number,
            end_digit = myGrid[ender[0]][ender[1]].cell_number, parent = myGrid[starter[0]][starter[1]].cell_number;
    int up_value = myGrid[starter[0] + up][starter[1]].value, down_value = myGrid[starter[0] + down][starter[1]].value,
            left_value = myGrid[starter[0]][starter[1] + left].value, right_value = myGrid[starter[0]][starter[1] + right].value;
    if(GoalFound) return count;

    std::cout<< up_digit << " :Going upper" << std::endl;

    if(up_digit > 0 && up_digit < 145 && up_value > 0){
        count++;
        if(up_digit == end_digit) {
            GoalFound = true;
            storedEdges[0].push_back(parent);
            storedEdges[1].push_back(up_digit);
            std::cout << "Goal Found" << std::endl;
            return count;
        }
        if(checkVisitor(up_digit)) {
            std::cout << up_digit << " :Similarities found!" << std::endl;
            goto downer;
        }
        visited.push_back(up_digit);
        storedEdges[0].push_back(parent);
        storedEdges[1].push_back(up_digit);
        std::cout << up_digit << " pushed and up " << count << std::endl;
        int init[] = {starter[0] + up, starter[1]};
        EdgeCounter(init, ender);
    }

    downer:

    std::cout<< down_digit << " :Going down" << std::endl;

    if(down_digit > 0 && down_digit < 145 && down_value > 0){

        count++;
        if(down_digit == end_digit) {
            GoalFound = true;
            storedEdges[0].push_back(parent);
            storedEdges[1].push_back(down_digit);
            std::cout << "Goal Found" << std::endl;
            return count;
        }
        if(checkVisitor(down_digit)) {
            std::cout << down_digit << " :Similarities found!" << std::endl;
            goto lefter;
        }
        visited.push_back(down_digit);
        storedEdges[0].push_back(parent);
        storedEdges[1].push_back(down_digit);
        std::cout << down_digit << " pushed and down " << count << std::endl;
        int init[] = {starter[0] + down, starter[1]};
        EdgeCounter(init, ender);
    }

    lefter:

    std::cout<< left_digit << " :Going lefter" << std::endl;

    if(left_digit > 0 && left_digit < 145 && left_value > 0){

        count++;
        if(left_digit == end_digit) {
            GoalFound = true;
            storedEdges[0].push_back(parent);
            storedEdges[1].push_back(left_digit);
            std::cout << "Goal Found" << std::endl;
            return count;
        }
        if(checkVisitor(left_digit)) {
            std::cout << left_digit << " :Similarities found!" << std::endl;
            goto righter;
        }
        visited.push_back(left_digit);
        storedEdges[0].push_back(parent);
        storedEdges[1].push_back(left_digit);
        std::cout << left_digit << " pushed and down " << count << std::endl;
        int init[] = {starter[0], starter[1] + left};
        EdgeCounter(init, ender);
    }

    righter:

    std::cout << right_digit << " :Going righter" << std::endl;

    if(right_digit > 0 && right_digit < 145 && right_value > 0){

        count++;
        if(right_digit == end_digit) {
            GoalFound = true;
            storedEdges[0].push_back(parent);
            storedEdges[1].push_back(right_digit);
            std::cout << "Goal Found" << std::endl;
            return count;
        }
        if(checkVisitor(right_digit)) {
            std::cout << right_digit << " :Similarities found!" << std::endl;
            return count;
        }
        visited.push_back(right_digit);
        storedEdges[0].push_back(parent);
        storedEdges[1].push_back(right_digit);
        std::cout << right_digit << " pushed and down " << count << std::endl;
        int init[] = {starter[0], starter[1] + right};
        EdgeCounter(init, ender);
    }

    return count;
}           // Counts and stores the number of edges
void EdgeAdder(Graph& g){
    for(int i=0;i<storedEdges[0].size() || i< storedEdges[1].size(); i++){
        int parent = storedEdges[0].at(i), child = storedEdges[1].at(i);
        std::cout << "Parent: " << parent << " Child: " << child << std::endl;
        g.addEdge(parent, child);
    }
}                                // Adds the edges to graph from storage before running DFS
int* CoordinateFinder(int num){
    for(int i=0; i<sizeOfGrid; i++)
        for(int j=0; j<sizeOfGrid; j++){
            if(myGrid[i][j].cell_number == num) {
                coordinates[0] = i;
                coordinates[1] = j;
                return coordinates;
            }
        }
    return nullptr;
}
void SolutionCreator(){
    std::ofstream solution_file, for_arduino;
    for_arduino.open("ArdSolution.txt", std::ios_base::app);
    solution_file.open("solution.txt", std::ios_base::app);
    solution_file << path.size()-1 << " ";
    for(int i : path){
        int* arr = CoordinateFinder(i);
        solution_file << "(" << arr[0] << "," << arr[1] << ")";
        for_arduino << "(" << arr[0] << "," << arr[1] << ")";
    }
    solution_file << std::endl;
    for_arduino << std::endl;

}
int EntryPoint(const std::string& fileName, int problemNumber){
    int start[2],end[2];
    std::ifstream problemFile(fileName);
    std::string liner, number;
    getline(problemFile, liner);
    int numberOfProblems = std::stoi(liner);
    if (numberOfProblems>=problemNumber && problemNumber != 0)
        for(int k=0;k<problemNumber;k++) getline(problemFile, liner);
    else return 1;
    std::stringstream myStream(liner);
    for(int j=0; getline(myStream, liner, ','); j++){
        if(j<2) start[j] = std::stoi(liner);
        if(j>=2) end[j-2] = std::stoi(liner);
    }
    std::cout<<start[0]<<"," <<start[1]<<std::endl;
    std::cout<<end[0]<<"," <<end[1]<<std::endl;
    GoalCheck=false;
    GoalFound=false;                                                            // 2n^2-2n is the formula for number of nodes in a grid(nxn)
    SetGrid();                                                                  //  where 'n' is number of cells on each side.
    visited.clear();                                                            // For 12x12 grid, we have 552 Nodes
    Graph g(EdgeCounter(start, end)+552);
    EdgeAdder(g);
    g.DFS(myGrid[start[0]][start[1]].cell_number, myGrid[end[0]][end[1]].cell_number);
    std::cout << myGrid[end[0]][end[1]].cell_number << std::endl;
    if(GoalCheck) SolutionCreator();
    else std::cout<<"Goal Not Found!"<<std::endl;
    return 2;
}

int main(int argc, char** argv){
    int x = strtol(argv[1], nullptr, 0);
    return EntryPoint("coordinates.txt", x);;
}