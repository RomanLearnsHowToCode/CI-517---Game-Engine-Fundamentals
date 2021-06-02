#pragma once
#include <array>
#include <string>
#include "GraphicsEngine.h"
#include "ResourceManager.h"
#include "Timer.h"

#ifndef __ACHIEVEMENTS_ENGINE_H__
#define __ACHIEVEMENTS_ENGINE_H__

/*
STRUCT VS CLASS

Struct is going to the stack, Class is going to the HEAP
both heap and stack are having their own advantages and dissadvantages.
Struct behaves more as integer
*/

// STRUCT of achievement
struct achievement {
	
	int currentScore;
	int targetScore;
	bool achieved;
	std::string achievementTitle;
};

/*
	FRIEND CLASS:
	This class can access private and protected members of other classes in which it is declared as a friend.
	* Useful to allow a particular class to access private members of other classes.
*/


class AchievementsEngine {
	friend class XCube2Engine;


private:
// Timer in Achievement Engine is used to show the achievementTitle for certain time
	Timer* showTimer = new Timer();
	int showTime = 1000;
	int achievementIndex;

public:
// Achievement Engine functions 	
	void achievementsEngine();
	void progressvalueachievements(const int);
	void achievementOverlay(std::shared_ptr<GraphicsEngine> gfx);


// Achievement array and values for achievement stages
	achievement achievementLevel[2] = {

		{0,200,false,"1"},
		{0,600,false,"2"}

	};

};

#endif