#include "cheaper_mazegen.h"

Maze::Maze() {
	xsize=11; //max_row size (11 by default)
	ysize=11; //max_col size (11 by default)
}
Maze::Maze(int x, int y) {
	xsize = x;
	ysize = y;
}
void Maze::Init() {
	srand(time(0)); //Plant random seed
	//Init maze
	for (int y = 0; y < ysize; y++) {
		std::vector<Cell> row;
		for (int x = 0; x < xsize; x++) {
			row.push_back(Cell(y, x));
		}
		maze.push_back(row);
	}
	//Select a cell, make it current cell and mark as visited (gonna go 0, 0)
	maze[0][0].setVal();
	maze[0][0].setVisited();
	Cell current = maze[0][0];
	//Add cell to visited stack
	visited_stack.push(current);
	//The actual maze generation algorithm
	//While there are unvisited cells
	while (!visited_stack.empty()) {
		//First let's empty neighbors vector
		neighbors.clear();
		//Get current cell pos and store into an array
		int *cPos = current.getPos();
		//Check if current cell has unvisited neighbors: searching UP, DOWN, LEFT, RIGHT
		//NOTE, IN THIS VERSION WE TAKE 2 STEPS AT A TIME, SO WE CAN GET AN ALL NUMERIC-VALUE MAZE
		if ((cPos[0] - 2 > -1) && maze[cPos[0] - 2][cPos[1]].isVisited() == false) {
			neighbors.push_back(maze[cPos[0] - 2][cPos[1]]);
		}
		if ((cPos[0] + 2 < ysize) && maze[cPos[0] + 2][cPos[1]].isVisited() == false) {
			neighbors.push_back(maze[cPos[0] + 2][cPos[1]]);
		}
		if ((cPos[1] - 2 > -1) && maze[cPos[0]][cPos[1] - 2].isVisited() == false) {
			neighbors.push_back(maze[cPos[0]][cPos[1] - 2]);
		}
		if ((cPos[1] + 2 < xsize) && maze[cPos[0]][cPos[1] + 2].isVisited() == false) {
			neighbors.push_back(maze[cPos[0]][cPos[1] + 2]);
		}
		//IF THERE WERE NEIGHBORS FOUND
		if (!neighbors.empty()) {
			int random = rand() % neighbors.size();
			//Select a random neighbor to visit, make it current and push to visited stack
			//visited_stack.push();
			int *nPos = neighbors[random].getPos();
			int nx = nPos[1], ny = nPos[0];
			//std::cout << nPos[0] << ", " << nPos[1] << "\n";
			//How did we moved?
			int dx = nPos[1] - cPos[1];
			int dy = nPos[0] - cPos[0];
			if (nPos[0] == cPos[0]) { //we are in same row
				if (dx == -2) { //we moved left
					maze[cPos[0]][cPos[1] - 1].setVisited();
					maze[cPos[0]][cPos[1] - 1].setVal();
				}
				else if (dx == 2) {//we moved right
					maze[cPos[0]][cPos[1] + 1].setVisited();
					maze[cPos[0]][cPos[1] + 1].setVal();
				}
				else {
					//SOMETHING REALLY BAD HAPPENED
					std::cout << "ILLEGAL MOVE : ROW : EXITING\n";
				}
			}
			else if (nPos[1] == cPos[1]) { //we are in same column
				if (dy == -2) { //we moved up
					maze[cPos[0] - 1][cPos[1]].setVisited();
					maze[cPos[0] - 1][cPos[1]].setVal();
				}
				else if (dy == 2) {//we moved down 
					maze[cPos[0] + 1][cPos[1]].setVisited();
					maze[cPos[0] + 1][cPos[1]].setVal();
				}
				else {
					//SOMETHING REALLY BAD HAPPENED
					std::cout << "ILLEGAL MOVE : COLUMN EXITING\n";
				}
			}
			current = maze[ny][nx];
			maze[ny][nx].setVisited();
			maze[ny][nx].setVal(); //break wall
			visited_stack.push(current);
		}
		else {
			//POP TOP CELL FROM STACK
			current = visited_stack.top();
			visited_stack.pop();
		}
	}
}

std::vector<std::vector<GLuint>> Maze::getMaze() {
	//Utility function to turn maze into a 2D array
	std::vector<std::vector<GLuint>> maze_arr;
	std::vector<GLuint> row;

	//Fill upper walls
	for (int x = 0; x < xsize + 2; x++) {	
		row.push_back(1);
	}
	maze_arr.push_back(row);

	//Add maze data 
	for (int y = 0; y < ysize; y++) {
		row.clear();
		row.push_back(1);
		for (int x = 0; x < xsize; x++) {
			row.push_back(maze[y][x].getVal());
		}
		row.push_back(1);
		maze_arr.push_back(row);
	}
	row.clear();
	//Fill lower walls
	for (int x = 0; x < xsize + 2; x++) {
		row.push_back(1);
	}
	maze_arr.push_back(row);

	return maze_arr;
}