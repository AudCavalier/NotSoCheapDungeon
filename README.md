# NotSoCheapDungeon

![Screenshot](https://imgur.com/a/rh1O3Ru)

OldSchool "3D" ray-casting rendering exercise, generating a random maze
The idea is based on the MMORPG Final Fantasy XIV's mini game "Cheap Dungeon", which is basically the same idea, but it had a small puzzle to solve
In the original (Cheap Dungeon) you could only move square per square, here I decided to implement the idea using the algorithm Wolfenstein used 
with the power of modern OpenGL and a recursive back-tracker to procedurally generate the maze (check my Cheap Maze generator repository: https://github.com/AudCavalier/Cheap_Maze_Generator).

The game itself is no big deal, just walk through a random dungeon and when you reach certain tile you'll go to next level,
after a while it feels monotonous and boring, but some sort of "Hello World" for making a small game in OpenGL nonetheless.

Based on the ray-casting description provided by this tutorial: https://lodev.org/cgtutor/raycasting.html
also this helped me understand most of the algorithm: https://permadi.com/1996/05/ray-casting-tutorial-table-of-contents (for my own taste still lacks some descriptions, but gives a great general overview on how this works).
