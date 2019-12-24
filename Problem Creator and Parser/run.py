import subprocess

with open('coordinates.txt') as problem_finder:
    numberOfIssues= int(problem_finder.readline())


solution = open('solution.txt', 'w')
ard_solution = open('ArdSolution.txt', 'w')

# grid_size = int(input("Enter Grid Size: "))
# problems_to_be_generated = int(input("Problems to be generated: "))
# print("Running problem creator...\n")
# problem_creator = subprocess.call(["python problem_file_creator.py"])
print("Running Problem File Parser")
problem_parser = subprocess.call(["./problem_file_parser"])

for num in range(1,numberOfIssues+1):
    my_process = subprocess.call(["./solution_creator", f"{num}"])

solution.close()
ard_solution.close()
