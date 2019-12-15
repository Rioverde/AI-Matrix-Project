## Welcome COMP415 Artificial Intelligence Project 5

### Project Deadline is on **23 December 2019**

### This project is expected to be ready by **20 December 2019**.

We aim to implement Depth First Search (DFS) on a grid, program will accept a _problem text file_ and output a _solution text file_.

An example of problem text file (_problem.txt_):
```
1. (0,6)(5,1)...(6,9) // List of available spaces in the grid.
2. 4                  // Number of problems in this file.
3. 10 11 9 0          // Problem #1, first pair is start position, second pair is end position.
4. 3 2 4 4            // Problem #2
5. 2 7 9 11           // Problem #3
6. 1 1 11 11          // Problem #4
```
An example of solution text file (_solution.txt_):
```
1. 10 (10,11)(9,11)(7,8)(6,6)...(9,0) // First integer stands for minimum number of moves 'n'.
2. 3  (3,2)...(4,4)                   // Following the first integer is the coordinates of
3. 9  (3,2)...(4,4)                   // the path taken to reach from start coordinate to
4. 15 (1,1)...(11,11)                 // end destiation
```
