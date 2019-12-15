import random
import os


def print_grid():
    for x in range(grid_size):
        print("[", end='')
        for y in range(grid_size):
            if y != grid_size-1:
                print(f"{myGrid[x][y]}", end=', ')
            else:
                print(f"{myGrid[x][y]}]")


def print_grid_address():
    result = ''
    unavailable_spaces = int((grid_size**2)*0.1)       # Taking 15% of unavailable cells
    for x in range(grid_size):
        for y in range(grid_size):
            if unavailable_spaces > 0:
                if random.randint(0,50) > 44:          # Randomization is more spread out
                    unavailable_spaces = unavailable_spaces-1
                    print(f"Closed Cells: {unavailable_spaces}: ({x}, {y})")
                else:
                    result = result + '(' + str(x) + ',' + str(y) + ')'
            else:
                result = result + '(' + str(x) + ',' + str(y) + ')'
    return result

################################################
#     Generating start and end coordinates     #
################################################


def problem_generator(size):
    result = '\n' + size + '\n'
    for iterate in range(int(size)):
        result = result + str(random.randint(0, grid_size-1)) + ' ' + str(random.randint(0, grid_size-1)) + ' ' \
                 + str(random.randint(0, grid_size-1)) + ' ' + str(random.randint(0, grid_size-1)) + ' \n'
    return result


grid_size = int(input('Please specify grid size (N x N): '))
myGrid = [[0 for x in range(grid_size)] for y in range(grid_size)]
print("Grid with 90% available cells has been generated successfully!")
problem_size = input('Number of problems to be generated: ')


#################################################
#    Creating and writing into 'problem.txt'    #
#################################################

if os.path.exists("problem.txt"):
    os.remove("problem.txt")

file = open('problem.txt', 'wt')
file.write(print_grid_address())
file.write(problem_generator(problem_size))
file.close()

##################################################
#                 END OF CODE                    #
##################################################
