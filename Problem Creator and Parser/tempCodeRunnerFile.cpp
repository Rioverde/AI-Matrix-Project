while(myGrid[start[0]+down][start[1]].value  > 0 && myGrid[end[0]][end[1]].cell_number != myGrid[start[0]+down][start[1]].cell_number){
        if(checkVisitor(myGrid[start[0]+down][start[1]].cell_number)) return count;
        count++;
        std::cout << myGrid[start[0]+down][start[1]].cell_number << " and " << count << std::endl;
        visited.push_back(myGrid[start[0]+down][start[1]].cell_number);
        start[0] += down;
        return EdgeCounter(start, end);
    }