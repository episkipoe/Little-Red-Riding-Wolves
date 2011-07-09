#include <drawable.h>
class Red : public Drawable {
	public:
		void draw() {
			int size = 5;
			glColor3f(1,0,0);
			glBegin(GL_TRIANGLES);
				glVertex3f(location.x-size, location.y-size, location.z);
				glVertex3f(location.x+size, location.y-size, location.z);
				glVertex3f(location.x, location.y+size, location.z);
			glEnd();
		}
};
