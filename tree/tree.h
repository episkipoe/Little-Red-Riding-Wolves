#ifndef TREE_H
#define TREE_H

#include <drawable.h>

class Tree : public Drawable {
	public:
		Tree (Point & loc) { location = loc; }
		void draw() {
			glColor3f(0.8,0.8,0.8);
			draw_texture("tree", location, 10, 10);
		}
		float getRadius() { return 4; }
};

#endif

