#include "TestMazeGenerator.h"

// What??
Dir::Dir() {}
// What? but it's contrustor of something.. 
Dir::Dir(const Dir & other) : bit(other.bit), dx(other.dx), dy(other.dy),
opposite(other.opposite) {}
// looks like generating the maze
MazeGenerator::MazeGenerator(const int & x, const int & y) : x(x), y(y) {
	// North.bit = 1 , North direction x = 0, North direction y = -1, opposite of North = pointer South
	N.bit = 1;
	N.dx = 0;
	N.dy = -1;
	N.opposite = &S;
	// South.bit = 2, South direction x = 0, South direction y = 1, opposite of South = pointer North
	S.bit = 2;
	S.dx = 0;
	S.dy = 1;
	S.opposite = &N;
	// East.bit = 4, East direction x = 1, East direction y = -0, opposite of East = pointer West
	E.bit = 4;
	E.dx = 1;
	E.dy = -0;
	E.opposite = &W;
	// West.bit = 8, West direction x = -1, West direction y = 0, opposite of West = pointer East 
	W.bit = 8;
	W.dx = -1;
	W.dy = 0;
	W.opposite = &E;

	maze = new int*[x];
	// so i will increment until the size of X would be achieved , it means that if X is 15, then it will run 15x times..
	for (int i = 0; i < x; ++i)
		maze[i] = new int[y];
	// okay basically two dimensional array, it looks like I is X axis and J is Y axis 
	for (int i = 0; i < x; ++i) {
		for (int j = 0; j < y; ++j) {
			maze[i][j] = 0;
		}
	}
}

MazeGenerator::~MazeGenerator() {
	for (int i = 0; i < x; ++i)
		delete[] maze[i];
	delete[] maze;
}

// Looks like a declaration of generate maze function there are two int values, CX and CY , it use Directions 
void MazeGenerator::generateMaze(int cx, int cy) {
	Dir * dirs = new Dir[4]{ N, S, E, W };


	for (int i = 0; i < 4; ++i) {
		int index;
		do {
			index = getRandom(0, 3);
		} while (index == i);

		Dir tmp = dirs[i];
		dirs[i] = dirs[index];
		dirs[index] = tmp;
	}

	
	for (int i = 0; i < 4; ++i) {
		Dir dir = dirs[i];
		int nx = cx + dir.dx;
		int ny = cy + dir.dy;
		if (between(nx, x) && between(ny, y) && (maze[nx][ny] == 0)) {
			maze[cx][cy] |= dir.bit;
			maze[nx][ny] |= dir.opposite->bit;
			generateMaze(nx, ny);
		}
	}
}
