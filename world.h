#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <red/red.h>
#include <wolf/wolf.h>
#include <house/house.h>

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

		void handleMouse(int button, int state, int x, int y);
		void handleKeyboard(unsigned char key, int x, int y);
		void placeObject(int button, int x, int y);
	
		void addWolf(const Wolf & newWolf) { wolves.push_back(newWolf); }
		vector<Wolf> & getWolves() { return wolves; }
		Red getRed() { return red; }
		House getHouse() {return house; }
	
		bool overlapsWithHouse(Point location) { return house.getLocation().inRange(location, 5); }		
		bool overlapsWithRed(Point location) { return red.getLocation().inRange(location, 5); }		

	private:
		std::string game_over_message;

		//things in the world
		std::vector<Wolf> wolves;
		std::vector<Wolf> saved_wolves;
		std::vector<Drawable *> obstacles;
		Red red;	
		House house;
};

#endif
