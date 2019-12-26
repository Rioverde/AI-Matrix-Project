#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <list>
#include <vector>

///////////////////////////////////////////////////////////////////////////////
//       Grid struct represents each cell in a grid, each cell contains      //
//          a cell number and a value (available or not)                     //
///////////////////////////////////////////////////////////////////////////////

struct Grid{
    int cell_number, value;
};

///////////////////////////////////////////////////////////////////////////////
//     -visited vector stores the cells that has been visited, it is         //
//          used in checkVisitor() function against a cell number.           //
//     -storedEdges[2] vector stores every parent and child nodes available. //
//     -path vector stores the path taken to reach the goal.                 //
///////////////////////////////////////////////////////////////////////////////

std::vector<int> visited, storedEdges[2], path;
const int sizeOfGrid = 8, up=-2, down=2, left=-1, right=3;

// Used to find x,y coordinates using grid cell number in coordinatesFinder() function.

int coordinates[2];

// GoalFound bool is used while mapping the graph
// GoadCheck bool is used while DFS is finding the shortest distance

bool GoalFound = false, GoalCheck = false;
int count = 0;

// Creating a grid

Grid myGrid[sizeOfGrid][sizeOfGrid];

void SolutionCreator();

// Reads gridStatus to set value in grid the created grid.

void SetGrid(){
    std::ifstream ReadGrid("gridStatus.txt");
    if(!ReadGrid.is_open()) exit(55);
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

////////////////////////////////////////////////////////////////////////////////
//                      Implementation of DFS algorithm                       //
////////////////////////////////////////////////////////////////////////////////

class Graph{
private:
    int verticesVariable;                                 // Number of nodes in graph
    std::list<int> *adj;                                  // Stores adjacent nodes in list
    void DFS_helper(int s, bool *visitedBool, int goal);  // Traverses through the graph and marks the visited nodes
public:
    explicit Graph(int vertices);                         // Constructor to initialize a graph
    ~Graph();                                             // Destructor to deallocate memory once done
    void addEdge(int parent_vertex, int child_vertex);    // Used to make a parent child relation in a graph
    void DFS(int start_vertex, int goal);                 // Main entry point for DFS, provide start node and end node
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

void Graph::DFS_helper(int s, bool *visitedBool, int goal){
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
    }
    visitedBool[s] = true;
    for(auto i = adj[s].begin(); i != adj[s].end(); i++){
        if(GoalCheck) return;
        if(!visitedBool[*i]){
            std::cout << "Going to vertex " << *i << " from vertex " << s << std::endl;
            DFS_helper(*i, visitedBool, goal);
        }
    }
}

void Graph::DFS(int s, int goal){
    bool *visitedBool = new bool[verticesVariable];
    for(int i = 0; i < verticesVariable; i++) visitedBool[i] = false;
    DFS_helper(s, visitedBool, goal);
}


bool checkVisitor(int cellNumber){                          // Checks with storage is cell is visited or not.
    for(int i : visited)
        if(cellNumber == i) return true;
    return false;
}                       
int EdgeCounter(int starter[1], int finisher[1]){           // Counts and stores the number of nodes available.
    if(count>552) return count;
    int up_digit = myGrid[starter[0] + up][starter[1]].cell_number, down_digit = myGrid[starter[0] + down][starter[1]].cell_number,
            left_digit = myGrid[starter[0]][starter[1] + left].cell_number, right_digit = myGrid[starter[0]][starter[1] + right].cell_number,
            end_digit = myGrid[finisher[0]][finisher[1]].cell_number, parent = myGrid[starter[0]][starter[1]].cell_number;
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
        EdgeCounter(init, finisher);
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
        EdgeCounter(init, finisher);
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
        EdgeCounter(init, finisher);
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
        EdgeCounter(init, finisher);
    }

    return count;
}
void EdgeAdder(Graph& g){                                   // Adds the edges to graph from storage before running DFS
    for(int i=0;i<storedEdges[0].size() || i< storedEdges[1].size(); i++){
        int parent = storedEdges[0].at(i), child = storedEdges[1].at(i);
        std::cout << "Parent: " << parent << " Child: " << child << std::endl;
        g.addEdge(parent, child);
    }
}
int* CoordinateFinder(int num){                             // Takes a cell number as a parameter and return x,y coordinates
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
void SolutionCreator(){                                     // Creates solution.txt as per requirement and ArdSolution.txt for serial input to arduino
    std::ofstream solutionFile, forArduino;
    forArduino.open("ArdSolution.txt", std::ios_base::app);
    solutionFile.open("solution.txt", std::ios_base::app);
    solutionFile << path.size() - 1 << " ";
    for(int i = 0; i<path.size(); i++){
        int* arr = CoordinateFinder(path.at(i));
        solutionFile << "(" << arr[0] << "," << arr[1] << ")";
        if(i != path.size()-1)
            forArduino << "(" << arr[0] << "," << arr[1] << "),";
        else
            forArduino << "(" << arr[0] << "," << arr[1] << ")|";
        
    }
    solutionFile << std::endl;
    forArduino << std::endl;
    solutionFile.close();
    forArduino.close();

}

///////////////////////////////////////////////////////////////////////////
//    Takes File name and problem number to be solved as parameter.      //
//    Creates a graph, counts the  number of nodes, finds shortest       //
//          path using DFS and then appends to solution.txt and          //
//          ArdSolution.txt                                              //
///////////////////////////////////////////////////////////////////////////

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
    visited.clear();                                                            // For 8x8 grid, we have 112 Nodes
    Graph g(EdgeCounter(start, end)+112);
    EdgeAdder(g);
    g.DFS(myGrid[start[0]][start[1]].cell_number, myGrid[end[0]][end[1]].cell_number);
    std::cout << myGrid[end[0]][end[1]].cell_number << std::endl;
    if(GoalCheck) SolutionCreator();
    else std::cout<<"Goal Not Found!"<<std::endl;
    return 1;
}

int main(int argc, char** argv){
    int x = strtol(argv[1], nullptr, 0);
    return EntryPoint("coordinates.txt", x);;
}
