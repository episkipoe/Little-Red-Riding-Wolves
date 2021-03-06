#include <stdio.h>
#include <stdlib.h>
#include "display.h"
#include "world.h"

extern World world;

namespace input {

	bool left, right, up, down, in, out;  //motion keys

	void specialDown(int theKey, int x, int y) {
		switch(theKey)  {
			case GLUT_KEY_LEFT:
				left = true;
				break;
			case GLUT_KEY_RIGHT:
				right = true;
				break;
			case GLUT_KEY_UP:
				up = true;
				break;
			case GLUT_KEY_DOWN:
				down = true;
				break;
			case GLUT_KEY_PAGE_UP:
				in = true;
				break;
			case GLUT_KEY_PAGE_DOWN:
				out = true;
				break;
			case GLUT_KEY_HOME:
				reset_eye();
				break;	
		}
	}

	void specialUp(int theKey, int x, int y) {
		switch(theKey)  {
			case GLUT_KEY_LEFT:
				left = false;
				break;
			case GLUT_KEY_RIGHT:
				right = false;
				break;
			case GLUT_KEY_UP:
				up = false;
				break;
			case GLUT_KEY_DOWN:
				down = false;
				break;
			case GLUT_KEY_PAGE_UP:
				in = false;
				break;
			case GLUT_KEY_PAGE_DOWN:
				out = false;
				break;
		}
	}

	void movePassive(int x, int y) {
		world.moveMouse(x, y);
	}

	void keyboard (unsigned char key, int x, int y) {
		switch(key) {
			case 'q':
				exit(0);
			case 'p': 
			default:
				world.handleKeyboard(key, x, y);
		}
	}

	void mouse(int button, int state, int x, int y) {
		world.handleMouse(button, state, x, y);			
	}

	void register_callbacks(void) {
		left=right=up=down=in=out=false;

		glutMouseFunc(mouse) ;
		glutPassiveMotionFunc(movePassive);
		glutKeyboardFunc(keyboard);
		glutSpecialFunc(specialDown);
		glutSpecialUpFunc(specialUp);
	}

	void timer(void) {
		//move_eye(left, right, up, down, in, out);
	}

}
