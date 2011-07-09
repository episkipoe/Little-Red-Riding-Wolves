#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <GL/gl.h>
#include <GL/glut.h>
#include <common/point.h>
#include <images/textures.h>


class Drawable {
	public:
		virtual void draw() = 0;

		Point getLocation() { return location; }

	protected:
		Point location;
};

#endif
