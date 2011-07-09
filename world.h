#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <red/red.h>
#include <wolf/wolf.h>
#include <house/house.h>
#include <path.h>

enum Phase {PLACE_WOLF, AI_RED, PLAYER_RED, GAME_OVER};

/**
 *  The world manages a number of Drawables
*/
class World {
	public:
		World() { 
			phase = PLACE_WOLF;
		}

		Phase phase;
		void switchPhase(Phase new_phase);

		void display();
		void processOneEvent();

		void playerWins();
		void playerLoses(const string & reason);

		void genWorld();

		void handleMouse(int button, int state, int x, int y);
		void handleKeyboard(unsigned char key, int x, int y);
		void placeObject(int button, int x, int y);
		void guideRed(int button, int x, int y);
	
		void addWolf(const Wolf & newWolf) { wolves.push_back(newWolf); }
		vector<Wolf> & getWolves() { return wolves; }
		Red getRed() { return red; }
		House getHouse() {return house; }

	private:
		void processRedEvent();
		void processWolfEvent();
		void collideObstacles();

		std::string game_over_message;

		//things in the world
		std::vector<Wolf> wolves;
		std::vector<Wolf> saved_wolves;
		std::vector<Drawable *> obstacles;
		std::vector<Path *> paths;
		Red red;	
		House house;

		bool victory;
};

#endif
