#include "mysolver.hpp"
#include <ics46/factory/DynamicFactory.hpp>

ICS46_DYNAMIC_FACTORY_REGISTER(MazeSolver, mysolver, "My Solver (Required)");

void mysolver::solverecursion(const Maze& maze, int x, int y, vector<bool>& visited, MazeSolution& mazeSolution){
    //If we're done, STOP
    if(mazeSolution.isComplete()){
        return;
    }

    //Mark current cell as visited
    int index = x + y*maze.getWidth();
    visited[index] = true;
    //Check if all sides are surrounded by walls or visited cells
    //If u are then back it up, remove most recent by using backUp(), end function prematurely
    //If u aren't then check which direction u can head to and extend in all of those directions with recursion after extension
    //It's possible the maze was solved in one of these recursions, check again before backing up
    if (checkValidDirection(maze, x, y, visited, 1)){
        mazeSolution.extend(Direction::left);
        solverecursion(maze, x-1, y, visited, mazeSolution);
    }
    if(mazeSolution.isComplete()){
        return;
    }

    if (checkValidDirection(maze, x, y, visited, 2)){
        mazeSolution.extend(Direction::up);
        solverecursion(maze, x, y-1, visited, mazeSolution);
    }
    if(mazeSolution.isComplete()){
        return;
    }

    if (checkValidDirection(maze, x, y, visited, 3)){
        mazeSolution.extend(Direction::right);
        solverecursion(maze, x+1, y, visited, mazeSolution);
    }
    if(mazeSolution.isComplete()){
        return;
    }

    if (checkValidDirection(maze, x, y, visited, 4)){
        mazeSolution.extend(Direction::down);
        solverecursion(maze, x, y+1, visited, mazeSolution);
    }
    if(mazeSolution.isComplete()){
        return;
    }
        //If we're at the starting cell after all that and haven't finished, then we failed to find a solution. No more backing up
    if(mazeSolution.getCurrentCell()==mazeSolution.getStartingCell()){
        return;
    }

    mazeSolution.backUp();
    return;
    


}



bool mysolver::checkValidDirection(const Maze& maze, int x, int y, vector<bool>& visited, int direction){
    //Checks if the solver can go in the given direction represented by int
    //1 is left, 2 is up, 3 is right, 4 is down
    //returns true if we can go that direction, false othewrise
    if(direction==1){
        if (!maze.wallExists(x,y,Direction::left)){
            int index = x-1 + y*maze.getWidth();
            return !visited[index]; 
        }
        return false;
    }
    if(direction==2){
        if (!maze.wallExists(x,y,Direction::up)){
            int index = x + (y-1)*maze.getWidth();
            return !visited[index]; 
        }
        return false;
    }
    if(direction==3){
        if (!maze.wallExists(x,y,Direction::right)){
            int index = x+1 + y*maze.getWidth();
            return !visited[index]; 
        }
        return false;
    }
    if(direction==4){
        if (!maze.wallExists(x,y,Direction::down)){
            int index = x + (y+1)*maze.getWidth();
            return !visited[index]; 
        }
        return false;
    }
    return false;
}


void mysolver::solveMaze(const Maze& maze, MazeSolution& mazeSolution){
    //Basically the main function, starts the recursion off

    int width = maze.getWidth();
    int height = maze.getHeight();
    vector<bool> visited (width*height,false);
    pair<int, int> xy = mazeSolution.getStartingCell();
    int x = xy.first;
    int y = xy.second;
    solverecursion(maze, x, y, visited, mazeSolution);
}