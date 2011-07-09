#ifndef RED_H
#define RED_H

#include <drawable.h>
#include <images/textures.h>
class Red : public Drawable {
	public:
		void draw() {
			int size = 2;
			glColor3f(1,0,0);
			glBegin(GL_TRIANGLES);
				glVertex3f(location.x-size, location.y-size, location.z);
				glVertex3f(location.x+size, location.y-size, location.z);
				glVertex3f(location.x, location.y+size, location.z);
			glEnd();

			draw_texture("tree", location);

		}
};

#endif
