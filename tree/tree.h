#ifndef TREE_H
#define TREE_H

#include <drawable.h>

class Tree : public Drawable {
	public:
		Tree (Point & loc) { location = loc; }
		void draw() {
			draw_texture("tree", location, 8, 18);
		}
		float getRadius() { return 6; }
};

#endif

