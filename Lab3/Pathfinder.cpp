#include "Pathfinder.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Pathfinder::Pathfinder(){//Calls rand, fills maze with 1's
	srand(time(NULL));
	for(int level = 0; level < LEVEL_SIZE; level++){
		for(int row = 0; row < ROW_SIZE; row++){
			for(int col = 0; col < COL_SIZE; col++){
				maze_grid[row][col][level] = 1;
			}
		}
	}
}

Pathfinder::~Pathfinder(){}

string Pathfinder::toString() const{
	stringstream ss;
	for(int level = 0; level < LEVEL_SIZE; level++){
		for(int row = 0; row < ROW_SIZE; row++){
			for(int col = 0; col < COL_SIZE; col++){
				ss << maze_grid[row][col][level];
				if(col < COL_SIZE - 1){
					ss << " ";
				}
			}
			ss << endl;
		}
		if(level < LEVEL_SIZE - 1){
			ss << endl;
		}
	}
	return ss.str();
}

void Pathfinder::createRandomMaze(){
	    int maze[ROW_SIZE][COL_SIZE][LEVEL_SIZE];
        for(int row = 0; row < ROW_SIZE; row++){
			for(int col = 0; col < COL_SIZE; col++){
                for(int level = 0; level < LEVEL_SIZE; level++){
                    maze[row][col][level] = rand() % 2;
                }
            }
        }
        //Changes first and last cells to 1
        maze[0][0][0] = 1;
        maze[ROW_SIZE - 1][COL_SIZE - 1][LEVEL_SIZE - 1] = 1;
	    this->toString();
}

bool Pathfinder::importMaze(string file_name){
	
	ifstream file(file_name.c_str()); //Open file
	if(file.is_open()){
		string line;
		for(int level = 0; level < LEVEL_SIZE; level++){
			for(int row = 0; row < ROW_SIZE; row++){
				getline(file, line);
				stringstream ss(line);
				for(int col = 0; col < COL_SIZE; col++){
					int value;
					ss >> value;
					if(ss.fail()){
						ss.clear();
						return false;
					}
					if(!(value == 0 || value == 1)){ //Checks for bad characters
						return false;
					}
					//Adds values to temp maze
					temp_maze_grid[row][col][level] = value;
					
				}
				if(file.eof() && level < LEVEL_SIZE - 1){ //Bad file length
					return false;
				}
			}
			getline(file, line);
		}

	}
	else{ //File didn't open
		return false;
	}
    if(temp_maze_grid[0][0][0] == 0 || temp_maze_grid[ROW_SIZE - 1][COL_SIZE - 1][LEVEL_SIZE - 1] == 0){ //Checks for good start and end
		return false;
	}
	if(!file.eof()){
		return false;
	}
	//Passed all tests, modifies maze
	for(int level = 0; level < LEVEL_SIZE; level++){
		for(int row = 0; row < ROW_SIZE; row++){
			for(int col = 0; col < COL_SIZE; col++){
				maze_grid[row][col][level] = temp_maze_grid[row][col][level];
			}
		}
	}
	return true;
}

bool Pathfinder::find_maze_path(int grid[ROW_SIZE][COL_SIZE][LEVEL_SIZE], int r, int c, int l){
    //Base cases
	if(r < 0 || c < 0 || l < 0 || r >= ROW_SIZE || c >= COL_SIZE || l >= LEVEL_SIZE){
		return false;      // Cell is out of bounds.
	}
	else if(grid[r][c][l] != BACKGROUND){
		return false;      // Cell is on barrier or dead end.
	}
	else if(r == ROW_SIZE - 1 && c == COL_SIZE - 1 && l == LEVEL_SIZE - 1){
		grid[r][c][l] = PATH;         // Cell is on path.
		reverse_solution.push_back("(" + to_string(c) + ", " + to_string(r) + ", " + to_string(l) + ")");

		return true;               // and is maze exit.
	}
	else{
		// Recursive case.
		// Attempt to find a path from each neighbor.
		// Tentatively mark Cell as on path.
		grid[r][c][l] = PATH;
		if(find_maze_path(grid, r - 1, c, l)
			|| find_maze_path(grid, r + 1, c, l)
			|| find_maze_path(grid, r, c - 1, l)
			|| find_maze_path(grid, r, c + 1, l)
			|| find_maze_path(grid, r, c, l - 1)
			|| find_maze_path(grid, r, c, l + 1)){
			reverse_solution.push_back("(" + to_string(c) + ", " + to_string(r) + ", " + to_string(l) + ")");
			return true;
		}
		else{
			grid[r][c][l] = TEMPORARY;  // Dead end.
			return false;
		}
	}
}

vector<string> Pathfinder::solveMaze(){
    //Remove old solutions if any
	reverse_solution.clear();
	solution.clear();

	int new_maze_grid[ROW_SIZE][COL_SIZE][LEVEL_SIZE]; 

	for(int level = 0; level < LEVEL_SIZE; level++){//Create new maze copied from the original
		for(int row = 0; row < ROW_SIZE; row++){
			for(int col = 0; col < COL_SIZE; col++){
				new_maze_grid[row][col][level] = maze_grid[row][col][level];
			}
		}
	}
	find_maze_path(new_maze_grid, 0, 0, 0);

	int solution_size = reverse_solution.size();
	for(int i = 0; i < solution_size; i++){
		solution.push_back(reverse_solution.back());
		reverse_solution.pop_back();
	}
	return solution;
}