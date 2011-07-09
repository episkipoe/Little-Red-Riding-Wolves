#ifndef WOLF_H
#define WOLF_H

#include <drawable.h>
class Wolf : public Drawable {
	public:
		Wolf (Point loc)  { 
			location = loc;
		}

		void draw() {
#ifdef DEBUG
			printf("drawing at %g, %g\n", location.x, location.y);
#endif
			glColor3f(0.8, 0.8, 0.8);
			glPointSize(4);
			glBegin(GL_POINTS);
			glVertex3f(location.x, location.y, location.z);
			glEnd();
		}		

		
};

#endif
