import subprocess
import serial


#####################################################################
#   Opens coordinates.txt to find out number of problems in file    #
#   Truncates & opens soultion.txt & ArdSolution.txt                #
#   Executes the .cpp files and gets an input on the previously     #
#       2 opened files.                                             #
#####################################################################

with open('coordinates.txt') as problem_finder:
    numberOfIssues= int(problem_finder.readline())


solution = open('solution.txt', 'w')
ard_solution = open('ArdSolution.txt', 'w+')

# grid_size = int(input("Enter Grid Size: "))
# problems_to_be_generated = int(input("Problems to be generated: "))
# print("Running problem creator...\n")
# problem_creator = subprocess.call(["python problem_file_creator.py"])

print("Running Problem File Parser")
problem_parser = subprocess.run(["./problem_file_parser"])

for num in range(1,numberOfIssues+1):
    my_process = subprocess.run(["./solution_creator", f"{num}"])

ard_solution.seek(0, 2)
ard_solution.write('#')

#########################################################################
#       Opens a serial port using the provided COM Port and writes      #
#           it into the Arduino serial monitor.                         #
#########################################################################

com_port_string = "/dev/ttyACM0"

ard_solution.seek(0)
problem_find = ard_solution.read()
print(problem_find)

with serial.Serial(com_port_string, 9600, timeout=1) as arduino_serial:
    arduino_serial.write("c".encode())
    problem_find = ard_solution.read()
    print(problem_find)
    arduino_serial.write(problem_find.encode())

solution.close()
ard_solution.close()
