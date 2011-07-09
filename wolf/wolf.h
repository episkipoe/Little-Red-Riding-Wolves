#ifndef WOLF_H
#define WOLF_H

#include <drawable.h>

class Wolf : public Drawable {
	public:
		Wolf (Point loc)  { 
			location = loc;
			speed=30;
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
            draw_texture("wolf", location, 10);
		}		

		void chase(Point red) {
			moveVector.x=red.x-location.x;
			moveVector.y=red.y-location.y;
			moveVector.normalize();
		}

		void update(float frameTime) {
			lastLoc = location;
			location = location + moveVector * speed * frameTime;
		}

protected:
	Point moveVector;
	float speed;

		
};

#endif
