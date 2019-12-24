with serial.Serial(com_port_checker, 9600) as arduino_serial:
    problem_find = ard_solution.read()
    print(problem_find)
    arduino_serial.write(problem_find.encode())