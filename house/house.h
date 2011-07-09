#include <common/point.h>
class House: public Drawable {
	public:
		House() {
			location.x = -20;
			location.y = 40;
		}

		void draw() {
			glColor3f(0.6, 0.26, 0.12);
			glPointSize(100);
			glBegin(GL_POINTS);
			glVertex3f(location.x, location.y, location.z);
			glEnd();
		}	
};

