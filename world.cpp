#include <graphics/text.h>
#include <GL/glut.h>
#include <tree/tree.h>
#include <vector>
#include <algorithm>
#include <tree/bush.h>
#include <tree/grass.h>
#include <time.h>
#include "world.h"
#include "textures.h"

extern Point look;

namespace {
    Point screenToWorld(int x, int y) {
        int viewport[4];
        double projection[16];
        double modelview[16];
        glGetIntegerv(GL_VIEWPORT,viewport);
        glGetDoublev(GL_PROJECTION_MATRIX,projection);
        glGetDoublev(GL_MODELVIEW_MATRIX , modelview);

        double worldX, worldY, worldZ;
        gluUnProject( x, viewport[3]-y, 0, modelview, projection, viewport, &worldX, &worldY, &worldZ );
        return Point(worldX,worldY,0);
    }
}

void World::processOneEvent() {
	if(!isPaused){
		processWolfEvent();
		processRedEvent();
	}
}

void World::processRedEvent() { 
	if (red.touches(&house)) {
		if(phase == PLAYER_RED)  playerWins();
		if(phase == AI_RED) playerLoses("Robot red has reached the house");
		return;
	}
	red.setTouching(false);

	bool onPath = false;
	for(size_t j=0; j<paths.size(); j++) {
		if(red.touches(paths[j])) {
			onPath=true;
			break;
		}
	}
	red.setOnPath(onPath);

	for(size_t i=0; i<obstacles.size(); i++) {
		if(red.sees(obstacles[i])) {
			red.avoid(obstacles[i]);
		}
		if(red.touches(obstacles[i])) {
			red.beginChase();
			if(phase == PLAYER_RED) {
				red.moveBack();
			}
			red.setTouching(true);
		}
	}

	if(phase == AI_RED)
		red.chase(wolves,house.getLocation());

	red.update(.01);
}

void World::processWolfEvent() { 
	if(phase == PLACE_WOLF ||
	   phase == GAME_OVER) return;

	bool onObstacle = false;
	for(size_t i=0; i<wolves.size(); i++) {

		for(size_t j=0; j<obstacles.size(); j++) {
			if(wolves[i].touches(obstacles[j])) {
				onObstacle=true;
				break;
			}
		}
		wolves[i].setOnObstacle(onObstacle);


		if(wolves[i].touches(&red)) {
			if(phase == AI_RED) {
				switchPhase(PLAYER_RED);
			} else if(phase == PLAYER_RED) {
				red.eat();
				playerLoses("You have been eaten.");
			}
		}

		wolves[i].chase(red.getLocation(),wolves);
		wolves[i].update(.01);
	}
}

void World::switchPhase(Phase new_phase) {
	//playerLoses("Robot red has reached the house");
	phase = new_phase;
	if(new_phase == PLACE_WOLF) {
	} else if(new_phase == AI_RED) {
		saved_wolves = wolves;
	} else if(new_phase == PLAYER_RED) {
		red.resetLocation();
		wolves = saved_wolves;
		isPaused = true;
	} else if (new_phase == GAME_OVER) {
		red.stop();
		wolves = saved_wolves;
	}
}

void World::display() {
	draw_texture("bg", Point(0,0,0) , 200, 200);
	for(size_t i=0; i<decorations.size(); i++) {
		decorations[i]->draw();
	}
	for(size_t i=0; i<paths.size(); i++) {
		paths[i]->draw();
	}
	for(size_t i=0; i<obstacles.size(); i++) {
		obstacles[i]->draw();
	}
	for(size_t i=0; i<wolves.size(); i++) {
		wolves[i].draw();
	}
	house.draw();
	red.draw();

	if(phase==GAME_OVER) {
		drawText(-50, 0, game_over_message, Font());
	}
	if(isPaused)
		drawText(-50, -50, "Paused", Font());
}

void World::playerWins() {
	game_over_message = "A winnar is you!";
	victory=true;
	switchPhase(GAME_OVER);
}

void World::playerLoses(const string & reason) {
	game_over_message = reason;
	victory=false;
	switchPhase(GAME_OVER);
}

void World::placeObject(int button, int x, int y) {
	Point clicked = screenToWorld(x,y);
	if (button == GLUT_LEFT_BUTTON) {
		Wolf wolf(clicked);
		if(!red.sees(&wolf))
			addWolf(wolf);
	} else {
		obstacles.push_back(new Tree(clicked));
	}
}

void World::guideRed(int button, int x, int y) {
	Point clicked = screenToWorld(x,y);
	if (button == GLUT_LEFT_BUTTON) {
		red.follow(clicked);
	} else {
	}
}

void World::handleMouse(int button, int state, int x, int y) {
	if(state==GLUT_DOWN) return;

	if(phase == PLACE_WOLF) placeObject(button, x, y); 
	if(phase == PLAYER_RED) guideRed(button, x, y);
}

void World::moveMouse(int x, int y) {
	if(phase == PLAYER_RED) guideRed(GLUT_LEFT_BUTTON, x, y);
}

void World::handleKeyboard(unsigned char key, int x, int y) {
	switch(key) {
		case ' ':
			if(phase==PLACE_WOLF)
				switchPhase(AI_RED);
			break;
		case 's':
			if(phase==PLACE_WOLF)
				switchPhase(AI_RED);
			if(phase==AI_RED)
				switchPhase(PLAYER_RED);
			if(phase==PLAYER_RED)
				switchPhase(GAME_OVER);
			if(phase==GAME_OVER)
				switchPhase(PLACE_WOLF);
			break;
		case 'r':
			reset();
			break;
		case 'p':
			isPaused = !isPaused;
			break;
	}
}

void World::reset(){
	wolves.clear();
	saved_wolves.clear();
	switchPhase(PLACE_WOLF);
	red.resetLocation();
	decorations.clear();
	paths.clear();
	obstacles.clear();
	genWorld();
}

bool World::overlaps(Point &pos) {
	if (pos.distance(red.getLocation())<15) return true;
	if (pos.distance(house.getLocation())<30) return true;
	for (size_t j=0; j<paths.size(); j++) {
		if (pos.distance(paths[j]->getLocation())<8) return true;
	}
	return false;
}

void World::genWorld() {
        srand(time(NULL));

	vector<Drawable> placedObjects();

	//door y:50 x:-60
	//red  y:-60 x:80

	//first, create the path
	//int numTurns = rand()%3+1;
	int numTurns = 2;
	Point currentPos(80,-60);
	Point housePos(-60,50);


	vector<float> yPositions;
	for (int i=0; i<numTurns; i++) {
		yPositions.push_back((float) (rand()%11-6)*10);
	}
	sort(yPositions.begin(),yPositions.end());

	for (size_t i=yPositions.size()-1; i>=0 && i<yPositions.size(); i-=1) {

		Point end(currentPos.x,yPositions[i]);
		currentPos=drawPath(currentPos,end,true);
		red.addPathNode(currentPos);

		//printf("%f\n",-60 + (110.0/yPositions.size())*i);
		end.x = -60 + (110.0/yPositions.size())*i;
		currentPos=drawPath(currentPos,end,false);
		red.addPathNode(currentPos);
	}

	drawPath(currentPos,housePos,true);
	red.addPathNode(housePos);

	for (int i=0; i<40; i++) {
		Point pos(rand()%301-150,rand()%301-150);
		if(overlaps(pos)) continue;
		obstacles.push_back(new Tree(pos));
	}
	for (int i=0; i<80; i++) {
		Point pos(rand()%301-150,rand()%301-150);
		if(overlaps(pos)) continue;
		obstacles.push_back(new Bush(pos));
	}

	obstacles.push_back(new Fence(95, 99, BACKSLASH_A));
	obstacles.push_back(new Fence(95, -99, FORWARDSLASH_A));
	obstacles.push_back(new Fence(-95, -99, BACKSLASH_B));
	obstacles.push_back(new Fence(-95, 99, FORWARDSLASH_B));
	for (int i=-10; i<10; i++){
		Point pos(i*10-2,-100);
		if(pos.x > -100){
			if(rand()%100 > 80)
				obstacles.push_back(new Fence(pos, GATE));
			else
				obstacles.push_back(new Fence(pos, HORIZONTAL));
			pos.y=100;
			if(rand()%100 > 80)
				obstacles.push_back(new Fence(pos, GATE));
			else
				obstacles.push_back(new Fence(pos, HORIZONTAL));
		}
		pos.x=-97;
		pos.y=i*10+3;
		obstacles.push_back(new Fence(pos, VERTICAL));
		pos.x=97;
		obstacles.push_back(new Fence(pos, VERTICAL_B));
	}
}

//assumes end it further north and west than start
Point World::drawPath(Point start, Point end, bool goUp) {
	//start.show();
	//end.show();
	if (goUp) {
		while (start.y<end.y) {
			Point p(start.x,start.y);
			paths.push_back(new Path(p));
			start.y=start.y+10;
		}
	} else {
		while (start.x>end.x) {
			Point p(start.x,start.y);
			paths.push_back(new Path(p));
			start.x=start.x-10;
		}
	}
	/*while (start.x>end.x || start.y<end.y) {
	  Point p(start.x,start.y);
	  paths.push_back(new Path(p));
	  start.addVector(angle,10);
	  }*/
	return start;
}

