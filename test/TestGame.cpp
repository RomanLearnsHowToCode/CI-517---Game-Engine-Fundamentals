#include "TestGame.h"





TestGame::TestGame() : AbstractGame(), score(0), lives(3), keys(5), gameWon(false), box(5, 5, 30, 30)
{	
	// Loading an MP3 file (wav) 
	Mix_Music * music = ResourceManager::loadMP3("../res/sounds/Arcade_Kid.wav");
	// Looping the loaded music file 
	sfx->playMP3(music,-1);
	// Loading the image
	SDL_Texture* img1 = ResourceManager::loadTexture("../res/images/confetti.png",SDL_COLOR_BLACK);

	gfx->setVerticalSync(true);

	gen = new MazeGenerator(10, 10);
	gen->generateMaze(0, 0);

	int dist = 40;

	for (int i = 0; i < gen->y; ++i) {

		int y = i * dist;

		for (int j = 0; j < gen->x; ++j) {

			int x = j * dist;

			if ((gen->maze[j][i] & 1) == 0) {
				lines.push_back(std::make_shared<Line2i>(Point2(x, y), Point2(x + dist, y)));
			}

			if ((gen->maze[j][i] & 8) == 0) {
				lines.push_back(std::make_shared<Line2i>(Point2(x, y), Point2(x, y + dist)));
			}

			if (keys > 0 && getRandom(0, 100) <= 5) {
				std::shared_ptr<GameKey> k = std::make_shared<GameKey>();
				k->alive = true;
				k->pos = Point2(j*dist + dist / 2, i*dist + dist / 2);
				points.push_back(k);
				keys--;
			}
		}

		lines.push_back(std::make_shared<Line2i>(Point2(gen->x*dist, y), Point2(gen->x*dist, y + dist)));
	}

	for (int j = 0; j < gen->x; j++) {
		int x = j * dist;
		lines.push_back(std::make_shared<Line2i>(Point2(x, gen->y * dist), Point2(x + dist, gen->y * dist)));
	}

	keys = 5;
}

TestGame::~TestGame() {
	delete gen;
}

void TestGame::handleKeyEvents() {
	int speed = 3;

	if (eventSystem->isPressed(Key::W)) {
		velocity.y = -speed;
	}

	if (eventSystem->isPressed(Key::S)) {
		velocity.y = speed;
	}

	if (eventSystem->isPressed(Key::A)) {
		velocity.x = -speed;
	}

	if (eventSystem->isPressed(Key::D)) {
		velocity.x = speed;
	}
}

void TestGame::update() {

	// Loading Sound resource used in this function
	Mix_Chunk * collectKey = ResourceManager::loadSound("../res/sounds/collect.wav");
	
	box.x += velocity.x;
	for (auto line : lines) {
		if (box.intersects(*line)) {
			box.x -= velocity.x;			
			break;
		}
	}

	box.y += velocity.y;
	for (auto line : lines) {
		if (box.intersects(*line)) {
			box.y -= velocity.y;
			break;
		}
	}

	for (auto key : points) {
		if (key->alive && box.contains(key->pos)) {
			score += 200;
			// there is the magic happening, I am parsing int of value 200 to the progressvalueachievements function
			achievementEngine->progressvalueachievements(200);
			key->alive = false;
			// If collected point, play sound
			sfx->playSound(collectKey);
			keys--;			
		}
	}

	velocity = Vector2i(0, 0);

	// If there are no more keys, then change the value of gameWon boolean to TRUE
	if (keys == 0) {

		gameWon = true;
	}

}


void TestGame::render() {
	gfx->setDrawColor(SDL_COLOR_WHITE);
	for (auto line : lines)
			gfx->drawLine(line->start, line->end);

	gfx->setDrawColor(SDL_COLOR_RED);
	gfx->drawRect(box);

	gfx->setDrawColor(SDL_COLOR_YELLOW);
	for (auto key : points)
		if (key->alive)
		gfx->drawPoint(key->pos);
}


void TestGame::renderUI() {

	// Usage and implementation of fonts, In this project I am using two fonts, first is used by score variable and second by GAME WON text

	TTF_Font * font = ResourceManager::loadFont("res/fonts/arial.ttf", 72);
	TTF_Font * font2 = ResourceManager::loadFont("../res/fonts/truelies.ttf", 50);
	gfx->useFont(font);

	// Creating a Rectangle called dst to represent the area for image to be drawn into
	SDL_Rect dst = { 200, 0, 500, 500 };
	SDL_Texture* img1 = ResourceManager::getTexture("../res/images/confetti.png");
	
	// Score text implementation
	gfx->setDrawColor(SDL_COLOR_AQUA);
	std::string scoreStr = std::to_string(score);
	gfx->drawText(scoreStr, 780 - scoreStr.length() * 50, 25);

	if (gameWon){

		// YOU WON text implementation
		gfx->useFont(font2);
		gfx->setDrawColor(SDL_COLOR_WHITE);
		gfx->drawText("YOU WON", 250, 500);
		// Draw the loaded image into the dst rectangle
		gfx->drawTexture(img1,&dst);
	}
	
		// This is to draw gfx in achievementOverlay (drawing Achievement levels)
		achievementEngine->achievementOverlay(gfx);
	
}

