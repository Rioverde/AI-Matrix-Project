#include <fstream>
#include <iostream>
#include <string>
#include <sstream>

using namespace std;

/*
Grid Rules:
From a position, you can only move
- UP    : 2 squares
- DOWN  : 2 squares
- LEFT  : 1 square
- Right : 3 squares

*/
const int sizeOfGrid=12; // Size of Grid
int x = -1; // 'x' is a variable for the each grid cell which is always modifiable.
int grid[sizeOfGrid][sizeOfGrid];
/////////////////////////////////////////////////////////////////////////////////
//          GridStatus() displays values in every cell.                        //
//          Invoke a call to GridStatus if necessary, such as,                 //
//              debugging.                                                     //
//          When this function is invoked it will create a file                //
//              ('gridStatus.txt') in its current working directory.           //
/////////////////////////////////////////////////////////////////////////////////

void GridStatus(int grid[][sizeOfGrid]){
    ofstream output_file("gridStatus.txt");
    for (int i = 0; i < sizeOfGrid; i++){
        output_file<<"[";
        for (int j = 0; j < sizeOfGrid; j++){
            if(output_file.is_open()){
                if (j != sizeOfGrid-1) output_file << grid[i][j]<<",";
                else output_file<< grid[i][j];
            }
        }
        output_file<<"]"<<endl;
    }
    output_file.close();
}

////////////////////////////////////////////////////////////////////////////////
//      FileParser() function parses the problem.txt.                         //
//      Integrate this function with your DFS algorithm to create             //
//          'solution.txt' file.                                              //
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//============================================================================//
//      DO NOT MAKE EDITS TO THE CODE BELOW THIS LINE UNLESS IMPROVING IT!    //

void ParseCoordinates(){
    string line;
    int e_pos=0, b_pos=0, key_coordinates;
    ifstream import_data("problem.txt");
    if(import_data.is_open()){
        getline(import_data, line);
        while((line.length() != e_pos) || key_coordinates == 1) {
            int x_cord, y_cord;
            b_pos = line.find("(", b_pos);
            e_pos = line.find(")", e_pos);
            if(e_pos == -1 || b_pos == -1) break;
            if(line.at(b_pos+2) == ',' && line.at(e_pos-2) == ',') {
                x_cord = line.at(b_pos+1) -48; y_cord = line.at(e_pos-1) -48;
                grid[x_cord][y_cord] = 1;
            }
            else if(line.at(b_pos+3) == ',' && line.at(e_pos-3) == ','){
                string data="";
                data += line.at(b_pos+1);
                data += line.at(b_pos+2);
                istringstream(data) >> x_cord;
                data.clear();
                data += line.at(b_pos+4);
                data += line.at(b_pos+5);
                istringstream(data) >> y_cord;
                grid[x_cord][y_cord] = 1;
            }
            else if(line.at(b_pos+3) == ',' && line.at(e_pos-2) == ','){
                string data="";
                data += line.at(b_pos+1);
                data += line.at(b_pos+2);
                istringstream(data) >> x_cord;
                data.clear();
                data += line.at(b_pos+4);
                istringstream(data) >> y_cord;
                grid[x_cord][y_cord] = 1;
            }
            else if(line.at(b_pos+2) == ',' && line.at(e_pos-3) == ','){
                string data="";
                data += line.at(b_pos+1);
                istringstream(data) >> x_cord;
                data.clear();
                data += line.at(b_pos+3);
                data += line.at(b_pos+4);
                istringstream(data) >> y_cord;
                grid[x_cord][y_cord] = 1;
            }
            ++b_pos; ++e_pos;
            if (e_pos >= line.length()) key_coordinates=1;
        }
    }
    GridStatus(grid);                                           // Instrustions for this function ('GridStatus()') provided above. 
    import_data.close();
}

int QuantityOfProblemsFinder(){
    string line;
    int problem_in_digits;
    ifstream import_data("problem.txt");
    for(int i=0; i<2;i++) getline(import_data, line);
    istringstream(line)>>problem_in_digits;
    import_data.close();
    return problem_in_digits;
}

void ProblemCoordinates(){
    ifstream import_data("problem.txt");
    string buf, line;
    int x_coordinate0, y_coordinate0, 
        x_coordinate1, y_coordinate1, problem_in_digits = QuantityOfProblemsFinder();
    for(int i=0; i<2;i++) getline(import_data, line);
    while(problem_in_digits>0){
        int count=0, tracker=0;
        getline(import_data, line);
        for(tracker=0; line.length() > count; count++){
            if(isdigit(line.at(count))) buf += line.at(count);
            if(!isdigit(line.at(count))){
                tracker++;
                if(tracker==1) istringstream(buf) >> x_coordinate0;
                else if(tracker==2) istringstream(buf) >> y_coordinate0;
                else if(tracker==3) istringstream(buf) >> x_coordinate1;
                else if(tracker==4) istringstream(buf) >> y_coordinate1;
                buf.clear();
            }
        }
    problem_in_digits--;
    cout << "Coordinates: ("<< x_coordinate0 << ", " << y_coordinate0 << ")\t" << "===>\t("<< x_coordinate1 << ", " << y_coordinate1 << ")"  << endl;       // <------- Make changes here as needed
    }
    import_data.close();
}

int main(){
    for(int i=0;i<sizeOfGrid;i++)                               //  <--- This loop creates the grid
        for(int j=0;j<sizeOfGrid;j++) grid[i][j] = x;           //  <-----------------
    ParseCoordinates();                                         //  <--- Loop Ends
    cout << QuantityOfProblemsFinder() << endl;
    ProblemCoordinates();
    return 0;
}