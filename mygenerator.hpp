#include "MazeGenerator.hpp"
#include "Maze.hpp"
#include <vector>
#include <random>
using namespace std;



#ifndef MYGENERATOR_HPP
#define MYGENERATOR_HPP


class mygenerator : public MazeGenerator{
public:
    void generateMaze(Maze& maze) override;
    void myrecursion(Maze& maze, int x, int y, vector<bool>& visit, std::default_random_engine& eng);
    void breakwall(Maze& maze, int x, int y, int dir);
    bool checksurrounded(Maze& maze, int x, int y, vector<bool>& visited);
    bool checkvaliddirection(Maze& maze, int x, int y, int dir, vector<bool>& visited);
};


#endif