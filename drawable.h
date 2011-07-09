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
        
        bool touches(Drawable *target) {
            if(location.distance(target->location) < target->radius + radius) {
                return true;
            }else{
                return false;
            }
        };

        bool sees(Drawable *target) {
            if(location.distance(target->location) < target->radius + radius * viewDistance) {
                return true;
            }else{
                return false;
            }
        };

	protected:
		Point location;
		Point lastLoc;
        float radius;
        float viewDistance;
        float width;
        float height;
};

#endif
