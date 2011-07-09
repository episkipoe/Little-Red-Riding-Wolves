#include <GL/glut.h>
#include <vector>

void display(void)
{
  	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);          // clear screen
  	gEye.setView();
  	glutSwapBuffers();
}

int main(int argc, char** argv) //finaly the main function
{
	//initialise glut
	glutInitDisplayMode(GLUT_DOUBLE | GLUT_RGB | GLUT_DEPTH) ;
	glutInitWindowSize(screenWidth,screenHeight) ;

    #if defined(_WIN32)
        srand(time(NULL));
    #else
     	srandom(time(NULL));
    #endif

	glutInit(&argc,argv);
	glutCreateWindow("Red Riding Wolves") ;
	input::register_callbacks();
	glutIgnoreKeyRepeat(1);
	glutMainLoop() ;

	return 0;
}
