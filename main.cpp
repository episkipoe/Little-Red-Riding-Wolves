#include <GL/glut.h>
#include <vector>
#include "display.h"
#include "input.h"
#include "world.h"

World world;

#define MSG_TIMER 0
#define DISPLAY_TIMER 1
#define GAME_TIMER 2
void timer(int val) {
	if(val==DISPLAY_TIMER) {
		glutTimerFunc(25,  timer, val);  
		input::timer();
		glutPostRedisplay();
		return;
	} 

	if(val==GAME_TIMER) {
		glutTimerFunc(50,  timer, val);  
		world.processOneEvent();
		glutPostRedisplay();
		return;
	} 

	glutTimerFunc(200,  timer, val);  
}


int main(int argc, char** argv) //finaly the main function
{
	//initialise glut
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH) ;

	glutInit(&argc,argv);
	initialize_display();
	glutTimerFunc(200, timer, MSG_TIMER);  
	glutTimerFunc(100, timer, DISPLAY_TIMER);  
	glutTimerFunc(100, timer, GAME_TIMER);  
	glutFullScreen();
	glutMainLoop() ;

	return 0;
}
