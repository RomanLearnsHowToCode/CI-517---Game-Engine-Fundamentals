#include "AchievementsEngine.h"
#include <iostream>


using namespace std;

// This function is to confirm that achievementsEngine subsystem is loaded successfully (will write to a console) 
// REDUNDANT, serve only a proof of progression
void AchievementsEngine::achievementsEngine()
{
	cout << "Achievements Engine Active" << endl;
}

/*
This function will take as input an integer value parsed from TestGame,
will check if value is valid and first will throw a console message,

*/
void AchievementsEngine::progressvalueachievements(int Apoint) 
{
	Apoint;
	cout <<Apoint<< std::endl;

	if (Apoint == 200) {
		
		cout << "Achievement unlocked: The first Encounter" << endl;


	}
	else if( Apoint == 400){

		cout << "Achievement unlocked: Greedy!" << endl;

	}
		// integer size is size of achievementLevel array 
		int size;
		size = sizeof(achievementLevel) / sizeof(*achievementLevel);
		cout << size << endl;
		/*
		 if achievement level is not achieved then add parsed points to the currentscore
		 and check with target score if they equal, if yes then achieved is true
		 and index equals to i and i is parsed to achievementLevel and value changed to the
		 currentAchievement. Timer is used to measure elapsed time.
		*/
		for (int i = 0; i < size; i++)
		{
			achievement currentAchievement = achievementLevel[i];
			if(!currentAchievement.achieved){
				currentAchievement.currentScore += Apoint;
				if (currentAchievement.currentScore == currentAchievement.targetScore) {
					currentAchievement.achieved = true;
					achievementIndex = i;
					showTimer->measure();
				} 
			cout << currentAchievement.achievementTitle << endl;
			}
			// In currentAchievement is a copy of an array !!
			achievementLevel[i] = currentAchievement;
		}	
}

// This function is to display a Achievement Level text
void AchievementsEngine::achievementOverlay(std::shared_ptr<GraphicsEngine> gfx) {

	if (showTimer->getTime()> 0 && showTimer->getElapsed()<showTime){
		achievement currentAchievement = achievementLevel[achievementIndex];
		gfx->drawText("Achievement level "+currentAchievement.achievementTitle, 0, 500);
		cout << "Achievement Level " +currentAchievement.achievementTitle +" unlocked" << endl;
	}
}








