#include "cheaper_mazegen_cell.h"

Cell::Cell() {
	//Temporarily initialize pos in (0, 0)
	pos[0] = 0;
	pos[1] = 0;
	val = 1; //Value of 1 (wall)
	visited = false; //Init visited to false
}
//Constructor setting cell value position
Cell::Cell(int y, int x) {
	pos[0] = y; //Y to indicate COLUMN index
	pos[1] = x; //X to indicate ROW index
	val = 1;
	visited = false;
}
//Setters and getters
void Cell::setVal() {
	//Once a wall is broken it won't be built up again
	val = 0;
}
void Cell::setVisited() {
	//Set visited value to true
	visited = true;
}
int* Cell::getPos() {
	return pos;
}
bool Cell::isVisited() {
	return visited;
}
int Cell::getVal() {
	return val;
}
