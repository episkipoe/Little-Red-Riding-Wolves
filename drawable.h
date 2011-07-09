#ifndef DRAWABLE_H
#define DRAWABLE_H

#include <graphics/graphics.h>
#include <common/point.h>
#include <images/textures.h>

class Drawable {
	public:
		virtual void draw() = 0;
		virtual float getRadius() = 0;

		Point getLocation() { return location; }

		virtual void update(float) {};
        
		bool touches(Drawable *target) {
			if(location.distance(target->location) < (target->getRadius() + getRadius())) {
				return true;
			}else{
				return false;
			}
		};

		bool sees(Drawable *target) {
			if(location.distance(target->location) < target->getRadius() + getRadius() * viewDistance) {
				return true;
			}else{
				return false;
			}
		};

		void moveBack() {
			location = lastLoc;
		}

	protected:
		Point location;
		Point lastLoc;
		float viewDistance;
};

#endif
