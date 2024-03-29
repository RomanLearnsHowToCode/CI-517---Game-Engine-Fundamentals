#ifndef __TEST_GAME_H__
#define __TEST_GAME_H__

#include "../engine/AbstractGame.h"
#include "TestMazeGenerator.h"


struct GameKey {
	Point2 pos;
	bool alive;
};

class TestGame : public AbstractGame {
private:
	Rect box;
	

	Vector2i velocity;

	MazeGenerator * gen;

	std::vector<std::shared_ptr<Line2i>> lines;
	std::vector<std::shared_ptr<Rectangle2>> Square;
	std::vector<std::shared_ptr<GameKey>> points;

	/* GAMEPLAY */
	int score, lives;
	bool gameWon;
	void handleKeyEvents();
	void update();
	void render();
	void renderUI();
public:
	int keys;
	TestGame();
	~TestGame();
};

#endif