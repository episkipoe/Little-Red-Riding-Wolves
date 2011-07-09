#include <graphics/text.h>
#include <GL/glut.h>
#include <tree/tree.h>
#include "world.h"

extern Point look;

namespace {
	//TODO:  boundaries on the world
	void processOneEvent(World & world, Red & red) { 
		if (world.overlapsWithHouse(red.getLocation())) {
			if(world.phase == PLAYER_RED) {
				world.playerWins();
			} else if(world.phase == PLAYER_RED) {
				world.playerLoses("Robot red has reached the house");
			}
		}

		if(world.phase != AI_RED) { return ; }

		//TODO head towards house
	}

	void processOneEvent(World & world, Wolf & wolf) { 
		if(world.phase == PLACE_WOLF) return;
		//TODO head towards Red
		if(world.overlapsWithRed(wolf.getLocation())) {
			if(world.phase == AI_RED) {
				world.switchPhase(PLAYER_RED);
			} else if(world.phase == PLAYER_RED) {
				world.playerLoses("You have been eaten.");
			}
		}
	}
}

void World::switchPhase(Phase new_phase) {
	//playerLoses("Robot red has reached the house");
	phase = new_phase;
	if(new_phase == AI_RED) {
		saved_wolves = wolves;
	} else if(new_phase == PLAYER_RED) {
		red.resetLocation();
		wolves = saved_wolves;
	}
}

void World::display() {
	house.draw();
	for(size_t i=0; i<obstacles.size(); i++) {
		obstacles[i]->draw();
	}
	for(size_t i=0; i<wolves.size(); i++) {
		wolves[i].draw();
	}
	red.draw();

	if(phase==GAME_OVER) {
		drawText(0, 0, game_over_message, Font());
	}
}

void World::processOneEvent() {
	for(size_t i=0; i<wolves.size(); i++) {
		::processOneEvent(*this, wolves[i]);
	}
	::processOneEvent(*this, red);
}

void World::playerWins() {
	game_over_message = "A winnar is you!";
	switchPhase(GAME_OVER);
}

void World::playerLoses(const string & reason) {
	game_over_message = reason;
	switchPhase(GAME_OVER);
}


void World::handleMouse(int button, int state, int x, int y) {
	if(phase != PLACE_WOLF) return; 
	if(state==GLUT_DOWN) return;

	//TODO  translate scr coords to world coords
	//Make sure space is empty

	if (button == GLUT_LEFT_BUTTON) {
		Wolf wolf(look);
		addWolf(wolf);
	} else {
		obstacles.push_back(new Tree(look));
	}
}

void World::handleKeyboard(unsigned char key, int x, int y) {
	switch(key) {
		case ' ':
			if(phase==PLACE_WOLF) switchPhase(AI_RED);
	}
}

