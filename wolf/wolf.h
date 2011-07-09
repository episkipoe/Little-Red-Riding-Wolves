#ifndef WOLF_H
#define WOLF_H

#include <drawable.h>

class Wolf : public Drawable {
	public:
		Wolf (Point loc)  { 
			location = loc;
			speed=30;
            radius = 20;//TODO:Tweak radius for collision
            viewDistance = 3;//Wolves can see 3 times their raidus away from themselves
		}

		void draw() {
#ifdef DEBUG
			printf("drawing at %g, %g\n", location.x, location.y);
#endif
            draw_texture("wolf", location, 10);
		}		

		void chase(Point red) {
			moveVector.x=red.x-location.x;
			moveVector.y=red.y-location.y;
			moveVector.normalize();
		}

		void update(float frameTime) {
			lastLoc = location;
			location = location + moveVector * speed * frameTime;
		}

protected:
	Point moveVector;
	float speed;
};

#endif
