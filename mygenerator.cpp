#include "mygenerator.hpp"
#include <ics46/factory/DynamicFactory.hpp>

ICS46_DYNAMIC_FACTORY_REGISTER(MazeGenerator, mygenerator, "My Generator (Required)");

void mygenerator::myrecursion(Maze& maze, int x, int y, vector<bool>& visited, std::default_random_engine& eng){
    
    //Mark current cell as visited
    int index = x + y*maze.getWidth();
    visited[index] = true;

    //what direction do we go? Initialize 
    std::uniform_int_distribution<int> dis{1, 4};
    int direction = dis(eng);

    
    //Find a possible direction to go to, if there is still a possible direction to go in
    while (checksurrounded(maze, x, y, visited)==false){
        direction = dis(eng);
        while (checkvaliddirection(maze, x,y,direction, visited)==false){
            direction = dis(eng);
        
        }
        //Get the next coordinates of the cell we're going to 
        int nextx = x;
        int nexty = y;
        if(direction==1){
            nextx-=1;
        }
        if(direction==2){
            nexty-=1;
        }
        if(direction==3){
            nextx+=1;
        }
        if(direction==4){
            nexty+=1;
        }
        //Break the wall in that direction and call recursion on that cell
        breakwall(maze,x,y,direction);
        myrecursion(maze,nextx,nexty, visited, eng);
    }
    

    
}
    
        
bool mygenerator::checkvaliddirection(Maze& maze, int x, int y, int dir, vector<bool>& visited){
    //Checks if the x and y value could possibly go in the corresponding int direction(not off the maze)
        //1 is left, 2 is up, 3 is right, 4 is down
    //Also checks if the cell in that direction is visited
    //Returns true if we can go in that direction, false otherwise
    if(x==0 & dir == 1){
        return false;
    }
    if(x==(maze.getWidth()-1) && (dir == 3)){
        return false;
    }
    if(y==0 & dir == 2){
        return false;
    }
    if(y==(maze.getHeight()-1) && (dir == 4)){
        return false;
    }

    int nextx = x;
    int nexty = y;
    if(dir==1){
        nextx-=1;
    }
    if(dir==2){
        nexty-=1;
    }
    if(dir==3){
        nextx+=1;
    }
    if(dir==4){
        nexty+=1;
    }
    int nextindex = nextx+nexty*maze.getWidth();
    if(visited[nextindex]==true){
        return false;
    }
    return true;
    

}



bool mygenerator::checksurrounded(Maze& maze, int x, int y, vector<bool>& visited){
    //If the cell is surrounded with visited cells or edges of the maze, return true, otherwise return false
    if(checkvaliddirection(maze, x, y, 1, visited)){
        return false;
    }
    if(checkvaliddirection(maze, x, y, 2, visited)){
        return false;
    }
    if(checkvaliddirection(maze, x, y, 3, visited)){
        return false;
    }
    if(checkvaliddirection(maze, x, y, 4, visited)){
        return false;
    }
    return true;

}

void mygenerator::breakwall(Maze& maze, int x, int y, int dir){
    //Breaks the wall in the corresponding direction of the int, seen below
    if(dir==1){
        maze.removeWall(x,y,Direction::left);
    }
    if(dir==2){
        maze.removeWall(x,y,Direction::up);
    }
    if(dir==3){
        maze.removeWall(x,y,Direction::right);
    }
    if(dir==4){
        maze.removeWall(x,y,Direction::down);
    }
}


void mygenerator::generateMaze(Maze& maze){
    //basically the main function, starts the recursion
    int width = maze.getWidth();
    int height = maze.getHeight();
    vector<bool> visited (width*height,false);
    maze.addAllWalls();

    std::random_device device;
    std::default_random_engine engine{device()};
   
    myrecursion(maze,0,0, visited, engine);
    
    
}