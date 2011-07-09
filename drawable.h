#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <common/point.h>
#include <GL/gl.h>

class Drawable {
	public:
		virtual void draw() = 0;

		Point getLocation() { return location; }

	protected:
		Point location;
};

#endif
