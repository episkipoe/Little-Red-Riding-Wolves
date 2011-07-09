#include "world.h"

void World::display() {
	house.draw();
	red.draw();
	for(size_t i=0; i<wolves.size(); i++) {
		wolves[i].draw();
	}
}

