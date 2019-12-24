#include <fstream>
#include <iostream>
#include <string>
#include <sstream>


/*
Grid Rules:
From a position, you can only move
- UP    : 2 squares
- DOWN  : 2 squares
- LEFT  : 1 square
- Right : 3 squares

*/
const int sizeOfGrid=8; // Size of Grid
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
    std::ofstream output_file("gridStatus.txt");                                    //
    for (int i = 0; i < sizeOfGrid; i++){
        output_file<<"[";
        for (int j = 0; j < sizeOfGrid; j++){
            if(output_file.is_open()){
                if (j != sizeOfGrid-1) output_file << grid[i][j]<<",";
                else output_file<< grid[i][j];
            }
        }
        output_file<<"]"<<std::endl;
    }
    output_file.close();
}

////////////////////////////////////////////////////////////////////////////////
//      ParseCoordinates() function parses the first line of problem.txt.     //
//      It sets to 1 for all the available cells parsed from first line       //
//          into gridStatus.txt                                               //
////////////////////////////////////////////////////////////////////////////////

void ParseCoordinates(){
    std::string line;
    int e_pos=0, b_pos=0, key_coordinates;
    std::ifstream import_data("problem.txt");
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
                std::string data="";
                data += line.at(b_pos+1);
                data += line.at(b_pos+2);
                std::istringstream(data) >> x_cord;
                data.clear();
                data += line.at(b_pos+4);
                data += line.at(b_pos+5);
                std::istringstream(data) >> y_cord;
                grid[x_cord][y_cord] = 1;
            }
            else if(line.at(b_pos+3) == ',' && line.at(e_pos-2) == ','){
                std::string data="";
                data += line.at(b_pos+1);
                data += line.at(b_pos+2);
                std::istringstream(data) >> x_cord;
                data.clear();
                data += line.at(b_pos+4);
                std::istringstream(data) >> y_cord;
                grid[x_cord][y_cord] = 1;
            }
            else if(line.at(b_pos+2) == ',' && line.at(e_pos-3) == ','){
                std::string data="";
                data += line.at(b_pos+1);
                std::istringstream(data) >> x_cord;
                data.clear();
                data += line.at(b_pos+3);
                data += line.at(b_pos+4);
                std::istringstream(data) >> y_cord;
                grid[x_cord][y_cord] = 1;
            }
            ++b_pos; ++e_pos;
            if (e_pos >= line.length()) key_coordinates=1;
        }
    }
    GridStatus(grid);                                           // Instrustions for this function ('GridStatus()') provided above. 
    import_data.close();
}

////////////////////////////////////////////////////////////////////////////////
//  QuantityOfProblemsFinder() function parses the second line of problem.txt //
//      It returns the number of problems available in this file              //
////////////////////////////////////////////////////////////////////////////////

int QuantityOfProblemsFinder(){
    std::string line;
    int problem_in_digits;
    std::ifstream import_data("problem.txt");
    for(int i=0; i<2;i++) getline(import_data, line);
    std::istringstream(line)>>problem_in_digits;
    import_data.close();
    return problem_in_digits;
}

////////////////////////////////////////////////////////////////////////////////
//      ProblemCoordinates() function parses all the problems that are        //
//          available in the file into coordinates.txt                        //
////////////////////////////////////////////////////////////////////////////////

void ProblemCoordinates(){
    std::ofstream export_coordinates("coordinates.txt");
    export_coordinates << QuantityOfProblemsFinder() << std::endl;
    std::ifstream import_data("problem.txt");
    std::string buf, line;
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
                if(tracker==1) std::istringstream(buf) >> x_coordinate0;
                else if(tracker==2) std::istringstream(buf) >> y_coordinate0;
                else if(tracker==3) std::istringstream(buf) >> x_coordinate1;
                else if(tracker==4) std::istringstream(buf) >> y_coordinate1;
                buf.clear();
            }
        }
    problem_in_digits--;
    export_coordinates << x_coordinate0 << "," << y_coordinate0 << ","<< x_coordinate1 << "," << y_coordinate1 << std::endl;       // <------- Make changes here as needed
    }
    import_data.close();
}

int main(){
    for(int i=0;i<sizeOfGrid;i++)                               //  <--- This loop creates the grid
        for(int j=0;j<sizeOfGrid;j++) grid[i][j] = x;           //  <-----------------
    ParseCoordinates();                                         //  <--- Loop Ends
    ProblemCoordinates();
    return 0;
}