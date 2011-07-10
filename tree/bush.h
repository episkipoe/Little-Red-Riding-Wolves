#ifndef BUSH_H
#define BUSH_H

#include <drawable.h>

class Bush : public Drawable {
	public:
		Bush (Point & loc) { location = loc; }
		void draw() {
			draw_texture("bush", location, 4, 4);
		}
		float getRadius() { return 2; }
};

#endif

