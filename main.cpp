/*
	Not So Cheap Dungeon
	main.cpp - Main class with inits and window call, noting fancy, just a starting point to run the game
	Author: AudCavalier
*/
#include "window_utils.h"
#include "stb_image.h"

#define M_PI 3.14159265358979323846

const GLint W_WIDTH = 800, W_HEIGHT = 600;

float DegToRadians(float deg) {
	return deg * (M_PI / 180);
}

int main() {
	//He we get the maze and player initial position
	Init();
	srand(time(0));
	glfwInit(); //init glfw
	//window hints for glfw
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	//create window
	GLFWwindow* window = glfwCreateWindow(W_WIDTH, W_HEIGHT, "Not-so-cheap Dungeon", NULL, NULL);
	
	if (window==NULL) {
		std::cout << "ERROR CREATING WINDOW, EXITING\n";
		return -1;
	}
	glfwMakeContextCurrent(window);
	//init glad
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
		std::cout << "ERROR LOADING GLAD, EXITING\n";
		return -1;
	}
	glViewport(0, 0, W_WIDTH, W_HEIGHT);

	glEnable(GL_CULL_FACE);
	glEnable(GL_BLEND);
	glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
	//Getting the shader
	Shader myShader = Shader("vertex.shader", "fragment.shader");
	float vertices[] = {
		//Vertices coords   tex coords		color values
		0.0f, 0.0f,			0.0f, 0.0f,		0.1f, 0.1f, 0.1f,
		0.0f, 0.0f,			0.0f, 0.0f,		0.1f, 0.1f, 0.1f
	};
	//LAST MINUTE EDIT: COLOR VALUES MAKES THE MAZE LOOK A LITTLE BIT MORE INTERESTING

	unsigned int VAO, VBO;
	glGenVertexArrays(1, &VAO);	
	glBindVertexArray(VAO);
	
	glGenBuffers(1, &VBO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(2 * sizeof(float)));
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(2, 3, GL_FLOAT, GL_FALSE, 7 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(2);
	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(VAO);


	//=============================== TEXTURES STUFF ============================
	unsigned int texture;
	int tex_w, tex_h, nrChannels;
	//Generate texture
	glGenTextures(1, &texture);
	glBindTexture(GL_TEXTURE_2D, texture);
	//TEXTURES PARAMETERS
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);

	stbi_set_flip_vertically_on_load(true);
	//WARNING: WALL TEXTURE NOT INCLUDED
	unsigned char *data = stbi_load("wall.png", &tex_w, &tex_h, &nrChannels, 0);
	if (data) {
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, tex_w, tex_h, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else {
		std::cout << "Error loading texture\n";
	}
	stbi_image_free(data);

	//Setting the fragment shader color to blue
	myShader.use();
	myShader.setInt("tex", 0);

	float FOV = DegToRadians(60.0f);//FIELD OF VIEW = 60 degrees : Remember C++ works with radians so change to radians
	float projPlane_dist = (W_WIDTH/2)/tan(FOV/2); //Distance from player to projection plane
	int projX = 0, projY = 0.66; //Projection plane x and Y coords, remember this is perpendicular to direction

	xPos += 0.5;
	yPos += 0.5;
	//GLFW loop
	float currentFrame;
	while (!glfwWindowShouldClose(window)) {
		//Calculate deltatime
		currentFrame = glfwGetTime();
		deltatime = currentFrame - lastframe;
		lastframe = currentFrame;
		proccess_key(window);

		glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);

		//DO THE ACTUAAL RAYCASTING CALCULATIONS
		
		//One calc for every vertical stripe: Ray starts at player position
		for (int x = 0; x < W_WIDTH; x++) {
			//first we want camera plane to go from -1 to 1
			double camX = 2 * x / (double)W_WIDTH - 1;
			double rayDirX = dirX + planeX * camX; //x direction of the ray
			double rayDirY = dirY + planeY * camX; //y direction of the ray

			int Px = (int)xPos, Py = (int)yPos; //map coordinates position (integer)
			float sdX, sdY; //length of ray
			float dDX = std::abs(1 / rayDirX), dDY = std::abs(1 / rayDirY);
			float wallDist;

			int stepX, stepY; //direction in x or y coordinates the ray is moving
			int hit = 0; //to check if we hit a wal
			int side; //which wall side we hit

			//initialize values for distance calculation
			if (rayDirX < 0) { //is THIS RAY facing left?
				stepX = -1;
				sdX = (xPos - Px) * dDX; //euclidean distance calculation
			}
			else {
				stepX = 1;
				sdX = (Px + 1.0 - xPos) * dDX;
			}
			if (rayDirY < 0) { //is THIS RAY facing up?
				stepY = -1;
				sdY = (yPos - Py) * dDY;
			}
			else {
				stepY = 1;
				sdY = (Py + 1.0 - yPos) * dDY;
			}
			//check if we hit a wall
			while (hit == 0) {
				/*
					Basically the ray "jumps" one square at a time, depending on the shortest distance
					if shortest distance is sdX then ray moves "1 step" into it's corresponding X
					same goes for Y
				*/
				if (sdX < sdY) {
					sdX += dDX;
					Px += stepX;
					side = 0; //we hit a wall in EAST-WEST direction
				}
				else {
					sdY += dDY;
					Py += stepY;
					side = 1; //we hit a wall in NORTH-SOUTH direction
				}
				//Every "step" we check if the maze position we fell in is a wall then we finish calculating
				if (maze_arr[Px][Py] > 0)
					hit = 1;
			}
			//Now that we have the result we check the distance from player position to wall
			if (side == 0) {
				//If we hit a wall in EAST-WEST dir
				wallDist = (Px - xPos + (1 - stepX) / 2)/rayDirX;
			}
			else {
				//If we hit a wall in NORTH-SOUTH dir
				wallDist = (Py - yPos + (1 - stepY) / 2)/rayDirY;
			}
			//Calculate wall slice height
			float wallH = (float)W_HEIGHT / wallDist;
			float p1 = (float)wallH / 2;
			
			//Modify the vertices array to actually draw the walls
			vertices[0] = camX;
			vertices[1] = p1 / (float)W_HEIGHT;
			vertices[7] = camX;
			vertices[8] = -p1 / (float)W_HEIGHT; 

			//check where the wall was hit in "world" coordinates, used for texture coordinate "u"
			double wallX;
			if (side == 0) {
				wallX = yPos + wallDist * rayDirY;
			}
			else {
				wallX = xPos + wallDist * rayDirX;
			}
			
			//Modify the texture coordinates (u will remain the same for each ray, as it is drawn as a vertical stripe)
			//(v will always be 0 on the first value, and 1 on the second, for actual stripe texturing)
			vertices[2] = wallX;
			vertices[3] = 0;
			vertices[9] = wallX;
			vertices[10] = 1;
			
			//I did this almost "blind" trusting my intuition, not sure if this is right,
			//but like king crimson: "IT JUST WORKS B=<"
			glBindBuffer(GL_ARRAY_BUFFER, VBO);
			glBufferSubData(GL_ARRAY_BUFFER, 0, sizeof(vertices), vertices);
			glDrawArrays(GL_LINES, 0, 2);
		}
		if (win == 1) {
			Init();
		}
		if ((int)xPos == exitX && (int)yPos == exitY) {
			win = 1;
		}
		glfwSwapBuffers(window);
		glfwPollEvents();
	}
	glDeleteBuffers(1, &VBO);
	glDeleteVertexArrays(1, &VAO);

	glfwTerminate();
	return 0;
}