#ifndef WORLD_H
#define WORLD_H

#include <vector>
#include <red/red.h>
#include <wolf/wolf.h>
#include <house/house.h>

class World {
	public:
		World() { 
			phase = PLACE_WOLF;
		}

		enum Phase {PLACE_WOLF, AI_RED, PLAYER_RED};
		void display();
		
		void addWolf(const Wolf & newWolf) { wolves.push_back(newWolf); }
		//TODO vector<Point> getWolfLocations() 

	private:
		Phase phase;

		//things in the world
		std::vector<Wolf> wolves;
		Red red;	
		House house;
};

#endif
