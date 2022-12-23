#include "MazeSolver.hpp"
#include "Maze.hpp"
#include "MazeSolution.hpp"
#include <vector>
#include <random>
using namespace std;


#ifndef MYSOLVER_HPP
#define MYSOLVER_HPP


class mysolver : public MazeSolver{
public:
    void solveMaze(const Maze& maze, MazeSolution& mazeSolution) override;
    void solverecursion(const Maze& maze, int x, int y, vector<bool>& visited, MazeSolution& mazesolution);
    bool checkValidDirection(const Maze& maze, int x, int y, vector<bool>& visited, int direction);
};


#endif