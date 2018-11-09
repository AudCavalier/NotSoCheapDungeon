#pragma once
#ifndef MAZE_CELL_H
#define MAZE_CELL_H

/*
	Maze cell header
	Used to define the cell class in the cheaper maze generator
	Author: AudCavalier
*/

class Cell {
private:
	int pos[2]; //(Y, X) tuple, position of the cell
	int val; //Value which the cell can take (1 - "wall" ; 0 - "free")
	bool visited; //Bool to indicate if the current cell has been visited or not
public:
	Cell(); //Default Constructor
	Cell(int y, int x); //Constructor setting pos values
	void setVal(); //setter for cell value
	void setVisited(); //setter for visited
	int* getPos(); //getter for cell pos
	bool isVisited(); //getter for visited
	int getVal(); //getter for cell value
};

#endif // !MAZE_CELL_H
