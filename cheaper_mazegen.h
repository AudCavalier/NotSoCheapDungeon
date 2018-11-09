#pragma once
#ifndef MAZE_GEN_H
#define MAZE_GEN_H

/*
	THE ACTUAL MAZE GENERATOR Header
	This is used to actually generate the maze
	Author: AudCavalier
*/

#include "cheaper_mazegen_cell.h"

#include <glad/glad.h>
#include <iostream>
#include <string>
#include <stack>
#include <vector>
#include <random>
#include <time.h>

class Maze {
private:
	int xsize; //max_row size
	int ysize; //max_col size
	std::vector<std::vector<Cell>> maze; //The actual maze
	std::stack<Cell> visited_stack; //Stack for visited cells
	std::vector<Cell> neighbors; //Vector to store neighbors of a cell
public:
	Maze(); //default constructor
	Maze(int x, int y); //constructor setting row and col sizes
	void Init(); //Utility function to create the maze the maze
	std::vector<std::vector<GLuint>> getMaze(); //Utility function to get maze as a 2D array
};


#endif // !MAZE_GEN_H
