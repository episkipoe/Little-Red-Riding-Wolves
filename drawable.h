#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <graphics/graphics.h>
#include <common/point.h>
#include <images/textures.h>


class Drawable {
	public:
		virtual void draw() = 0;

		Point getLocation() { return location; }

		virtual void update(float) {};

	protected:
		Point location;
		Point lastLoc;
};

#endif
