#pragma once
#include <iostream>
#include <string>
#include <vector>
#include "PathfinderInterface.h"
#include <fstream>
#include <sstream>
#include <stdlib.h>
#include <time.h>
#include <random>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

const int ROW_SIZE = 5;
const int COL_SIZE = 5;
const int LEVEL_SIZE = 5;
const int BACKGROUND = 1;
const int TEMPORARY = 2;
const int PATH = 3;

class Pathfinder : public PathfinderInterface {
public:
	Pathfinder();
	virtual ~Pathfinder();
	virtual string toString() const;
	virtual void createRandomMaze();
	virtual bool importMaze(string file_name);
	virtual vector<string> solveMaze();
private:
	vector<string> reverse_solution;
	vector<string> solution;
    int maze_grid[ROW_SIZE][COL_SIZE][LEVEL_SIZE];
	int temp_maze_grid[ROW_SIZE][COL_SIZE][LEVEL_SIZE]; //used to preserve the original maze
	bool find_maze_path(int grid[ROW_SIZE][COL_SIZE][LEVEL_SIZE], int r, int c, int l);
};
