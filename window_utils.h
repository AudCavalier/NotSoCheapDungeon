#pragma once
#ifndef WIN_UTILS_H
#define WIN_UTILS_H

/*
	WINDOW UTILS HEADER
	This is a simple class to define utility functions we'll be using for our window,
	also it'll help to add in here some includes needed
*/

#include "shader_class.h"
#include <GLFW/glfw3.h>
#include "cheaper_mazegen.h"

//The actual maze
Maze maze = Maze(11, 11);
std::vector<std::vector<GLuint>> maze_arr; 

float deltatime=0.0f, lastframe=0.0f;
float xPos, yPos, exitX, exitY; //Player and exit positions
float dirX=-1, dirY=0; //Player direction
float planeX = 0, planeY = 0.66; //Projection plane (which is a line perpendicular to the player point + direction vector
int win, level=0; //Variables to check win condition and level numbers
std::string strlvl;

void Init() {
	level++;
	win = 0;
	strlvl = "Level: " + std::to_string(level);
	maze.Init();
	maze_arr = maze.getMaze();
	xPos = rand() % 5 + 2, yPos = rand() % 5 + 2;
	while (maze_arr[xPos][yPos] == 1) {
		xPos = rand() % 5 + 2;
		yPos = rand() % 5 + 2;
	}
	exitX = rand() % 11 + 2, exitY = rand() % 11 + 2;
	while (maze_arr[exitX][exitY] == 1 || (exitX==xPos && exitY==yPos)) {
		exitX = rand() % 11 + 2;
		exitY = rand() % 11 + 2;
	}
	//Little "debug", Since rendering text is a little bit too confusing, I'll leave it so console says what level we are in
	std::cout << "Level: " << level << "\n";
}

void proccess_key(GLFWwindow* window) {
	//"character" Movement and rotation speed
	double moveSpeed = 2*deltatime;
	double rotSpeed = 2*deltatime;
	
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);

	//Actual controller
	if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
		if (maze_arr[int(xPos + dirX * moveSpeed)][yPos] == 0)
			xPos += dirX * moveSpeed;
		if (maze_arr[xPos][int(yPos + dirY * moveSpeed)] == 0)
			yPos += dirY * moveSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
		if (maze_arr[int(xPos - dirX * moveSpeed)][yPos] == 0)
			xPos -= dirX * moveSpeed;
		if (maze_arr[xPos][int(yPos - dirY * moveSpeed)] == 0)
			yPos -= dirY * moveSpeed;
	}
	if (glfwGetKey(window, GLFW_KEY_A)==GLFW_PRESS){
		double oldDirX = dirX;
		dirX = dirX * cos(rotSpeed) - dirY * sin(rotSpeed);
		dirY = oldDirX * sin(rotSpeed) + dirY * cos(rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(rotSpeed) - planeY * sin(rotSpeed);
		planeY = oldPlaneX * sin(rotSpeed) + planeY * cos(rotSpeed);
	}
	if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
		double oldDirX = dirX;
		dirX = dirX * cos(-rotSpeed) - dirY * sin(-rotSpeed);
		dirY = oldDirX * sin(-rotSpeed) + dirY * cos(-rotSpeed);
		double oldPlaneX = planeX;
		planeX = planeX * cos(-rotSpeed) - planeY * sin(-rotSpeed);
		planeY = oldPlaneX * sin(-rotSpeed) + planeY * cos(-rotSpeed);
	}
}

#endif // !WIN_UTILS_H
