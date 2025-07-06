// main.cpp
#include <iostream>
#include "maze.h"

int main() {
	Maze maze;
	if (maze.title() == 1) {
		return 0;
	}

	for (int i = 1; i <= 4; i++) {
		maze.GameLoop(i);
	}

	return 0;
}