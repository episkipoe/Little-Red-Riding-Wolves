#include <graphics/text.h>
#include <GL/glut.h>
#include <tree/tree.h>
#include "world.h"

extern Point look;

namespace {
    //TODO:  boundaries on the world
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
    processWolfEvent();
    processRedEvent();
}

void World::processRedEvent() { 
    if (red.touches(&house)) {
        if(phase == PLAYER_RED) {
            playerWins();
        } else if(phase == PLAYER_RED) {
            playerLoses("Robot red has reached the house");
        }
    }

    if(phase == PLAYER_RED) { red.update(.01); }
    if(phase != AI_RED) { return ; }

    red.chase(wolves,house.getLocation());
    red.update(.01);
}

void World::processWolfEvent() { 
    for(size_t i=0; i<wolves.size(); i++) {
        Wolf wolf = wolves[i];
        if(phase == PLACE_WOLF) return;

        if(wolf.touches(&red)) {
            if(phase == AI_RED) {
                switchPhase(PLAYER_RED);
            } else if(phase == PLAYER_RED) {
                playerLoses("You have been eaten.");
            }
        }

        wolf.chase(red.getLocation());
        wolf.update(.01);
    }
}

void World::switchPhase(Phase new_phase) {
    //playerLoses("Robot red has reached the house");
    phase = new_phase;
    if(new_phase == PLACE_WOLF) {
        glClearColor(0.0f,0.0f,0.0f,1.0f); 
    } else if(new_phase == AI_RED) {
        glClearColor(0.3f,1.0f,0.3f,1.0f); 
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
        (victory ? glColor3f(0,0,0) : glColor3f(1,0,0));
        drawText(0, 0, game_over_message, Font());
    }
}

void World::playerWins() {
    glClearColor(1,1,1,1);
    game_over_message = "A winnar is you!";
    victory=true;
    switchPhase(GAME_OVER);
}

void World::playerLoses(const string & reason) {
    glClearColor(0,0,0,1);
    game_over_message = reason;
    victory=false;
    switchPhase(GAME_OVER);
}

void World::placeObject(int button, int x, int y) {
    Point clicked = screenToWorld(x,y);
    if (button == GLUT_LEFT_BUTTON) {
        Wolf wolf(clicked);
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

void World::handleKeyboard(unsigned char key, int x, int y) {
    switch(key) {
        case ' ':
            if(phase==PLACE_WOLF) {
                switchPhase(AI_RED);
                return;
            }
            if(phase==AI_RED) {
                switchPhase(PLAYER_RED);
                return;
            }
            if(phase==PLAYER_RED) {
                switchPhase(GAME_OVER);
                return;
            }
            if(phase==GAME_OVER) {
                switchPhase(PLACE_WOLF);
                return;
            }
    }
}

