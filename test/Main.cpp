#include "TestGame.h"
#include "Windows.h"
#include <iostream>

using namespace std;

int main(int argc, char * args[]) {
	
	

	try {
		TestGame game;
		std::cout << "Game Started" << endl;
		game.runMainLoop();
		
	} catch (EngineException & e) {
		std::cout << e.what() << std::endl;
		getchar();
	}

	return 0;
}