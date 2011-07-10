#ifndef GRASS_H
#define GRASS_H

#include <drawable.h>

class Grass : public Drawable {
	public:
		Grass (Point & loc) { location = loc; }
		void draw() {
			draw_texture("grass", location, 4, 4);
		}
		float getRadius() { return 2; }
};

#endif

