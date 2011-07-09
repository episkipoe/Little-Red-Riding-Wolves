#ifndef WOLF_H
#define WOLF_H

#include <drawable.h>
class Wolf : public Drawable {
	public:
		Wolf (int x, int y)  { 
			location.x = x;
			location.y = y;
		}

		void draw() {
			glColor3f(0.8, 0.8, 0.8);
			glPointSize(4);
			glBegin(GL_POINTS);
			glVertex3f(location.x, location.y, location.z);
			glEnd();
		}		

		
};

#endif
