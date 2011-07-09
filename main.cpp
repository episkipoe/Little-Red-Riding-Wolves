#include <GL/glut.h>
#include <vector>
#include <time.h>
#include "display.h"
#include "input.h"

bool is_paused=false;

#define MSG_TIMER 0
#define DISPLAY_TIMER 1
void timer(int val) {
	if(val==DISPLAY_TIMER) {
		glutTimerFunc(100,  timer, val);  
		input::timer();
		glutPostRedisplay();
		return;
	} 
	glutTimerFunc(200,  timer, val);  
	if(is_paused) return;
}


int main(int argc, char** argv) //finaly the main function
{
	//initialise glut
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH) ;

    #if defined(_WIN32)
        srand(time(NULL));
    #else
     	srandom(time(NULL));
    #endif

	glutInit(&argc,argv);
	initialize_display();
	glutTimerFunc(200,  timer, MSG_TIMER);  
	glutTimerFunc(100, timer, DISPLAY_TIMER);  
	glutMainLoop() ;

	return 0;
}
