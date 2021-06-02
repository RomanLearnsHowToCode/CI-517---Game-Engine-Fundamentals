#ifndef __X_CUBE_2D_H__
#define __X_CUBE_2D_H__

#include <string>
#include <vector>
#include <memory>
#include <iostream>

#include "GraphicsEngine.h"
#include "AudioEngine.h"
#include "EventEngine.h"
#include "PhysicsEngine.h"
#include "ResourceManager.h"
#include "Timer.h"
#include "AlphaStar.h" // included A* engine subsystem 
#include "AchievementsEngine.h" // included AchievementsSystem engine subsystem

const int _ENGINE_VERSION_MAJOR = 0;
const int _ENGINE_VERSION_MINOR = 1;

using namespace std;

class XCube2Engine {
	private:
		static std::shared_ptr<XCube2Engine> instance;
		std::shared_ptr<GraphicsEngine> gfxInstance;
		std::shared_ptr<AudioEngine> audioInstance;
		std::shared_ptr<EventEngine> eventInstance;
		std::shared_ptr<PhysicsEngine> physicsInstance;
		std::shared_ptr<AiEngine> AiInstance; // added Ai instance
		std::shared_ptr<AchievementsEngine> achievementsInstance; // added Achievements instance


		XCube2Engine();
	public:
		/**
		* @return the instance of game engine
		* @exception throws EngineException if init of any submodules failed
		*/
		static std::shared_ptr<XCube2Engine> getInstance();
		~XCube2Engine();

		/**
		* Quits the engine, closes all the subsystems
		*
		* All subsequent calls to any of subsystems will have undefined behaviour
		*/
		static void quit();

		/**
		* Subsystems can only be accessed via the following accessors
		* @return approriate subsystem of the engine
		*/
		std::shared_ptr<GraphicsEngine> getGraphicsEngine() { return gfxInstance; }
		std::shared_ptr<AudioEngine> getAudioEngine() { return audioInstance; }
		std::shared_ptr<EventEngine> getEventEngine() { return eventInstance; }
		std::shared_ptr<PhysicsEngine> getPhysicsEngine() { return physicsInstance; }
		std::shared_ptr<AiEngine> getAiEngine() { return AiInstance; } // this line of code allow the subsystem to be accesed.
		// this line of code allow the subsystem to be accesed.
		std::shared_ptr<AchievementsEngine> getAchievementsEngine() { return achievementsInstance; } 
		
		
};

typedef XCube2Engine XEngine;

#endif