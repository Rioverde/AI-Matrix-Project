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
//      fileParser() function parses the problem.txt.                         //
//      Integrate this function with your DFS algorithm to create             //
//          'solution.txt' file.                                              //
////////////////////////////////////////////////////////////////////////////////
//                                                                            //
//============================================================================//
//      DO NOT MAKE EDITS TO THE CODE BELOW THIS LINE UNLESS IMPROVING IT!    //

void fileParser(){
    ifstream import_data("problem.txt");
    string line;
    int b_pos=0, e_pos=0, key_coordinates=0, key_problems=0, problem_in_digits=0;
    if(import_data.is_open()){
        while(!import_data.eof()) {
            getline(import_data, line);
            while((line.length() != e_pos) || key_coordinates == 1) {
                int x_cord, y_cord;
                b_pos = line.find("(", b_pos);
                e_pos = line.find(")", e_pos);
                if(e_pos == -1 || b_pos == -1) break;
                if(line.at(b_pos+2) == ',' && line.at(e_pos-2) == ',') {
                    x_cord = line.at(b_pos+1) -48; y_cord = line.at(e_pos-1) -48;
                    cout << "(" << x_cord << ", " << y_cord << ")" << endl;
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
                    cout << "(" << x_cord << ", " << y_cord << ")" << endl;
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
                    cout << "(" << x_cord << ", " << y_cord << ")" << endl;
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
                    cout << "(" << x_cord << ", " << y_cord << ")" << endl;
                    grid[x_cord][y_cord] = 1;
                }
                ++b_pos; ++e_pos;
                if (e_pos >= line.length()) key_coordinates=1;
            }
            if(!key_problems){
                getline(import_data, line);
                problem_in_digits = stoi(line) - 1;
                cout << "Number of problems in this file: " << problem_in_digits+1 << endl;
                key_problems=1;
            }
            while(problem_in_digits >= 0){
                getline(import_data, line);
                int x_coordinate0, y_coordinate0, 
                    x_coordinate1, y_coordinate1, count=0, tracker=0;
                string buf;
                for(tracker=0; line.length() > count; count++){
                    if(isdigit(line.at(count))){
                        buf += line.at(count);
                    } 
                    if(!isdigit(line.at(count))){
                        tracker++;
                        if(tracker==1) x_coordinate0=stoi(buf);
                        else if(tracker==2)y_coordinate0=stoi(buf);
                        else if(tracker==3)x_coordinate1=stoi(buf);
                        else if(tracker==4)y_coordinate1=stoi(buf);
                        buf.clear();
                    }
                }
                problem_in_digits--;
                // ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^
                //  DO NOT MAKE EDITS TO THE CODE ABOVE THIS LINE UNLESS YOU ARE IMPROVING IT.
                //  x_coordinate0 & y_coordinate0 are START COORDINATES.
                //  x_coordinate1 & y_coordinate1 are END COORDINATES.
                //  These coordinates are available each time loop iterates, make sure to store them in a
                //      safe place before operating on it.
                cout << "Start Coordinates\t: ("<< x_coordinate0 << ", " << y_coordinate0 << ")" << endl;       // <------- Make changes here as needed
                cout << "End Coordinates\t\t: ("<< x_coordinate1 << ", " << y_coordinate1 << ")" << endl;       // <------- Make changes here as needed
                //  ^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^^  //
                //                             MAKE CHANGES AS NEEDED HERE                             //
            }
        }
    } else perror("Error opening file!\n");
    import_data.close();
}

int main(){
    for(int i=0;i<sizeOfGrid;i++)           //  <--- This loop creates the grid
        for(int j=0;j<sizeOfGrid;j++){      //  <-----------------
            grid[i][j] = x;                 //  <-----------------
        }                                   //  <--- Loop Ends
    fileParser();
    GridStatus(grid);                       // Instrustions for this function ('GridStatus()') provided above. 
    return 0;
}