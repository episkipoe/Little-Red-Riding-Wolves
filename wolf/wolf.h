#ifndef WOLF_H
#define WOLF_H

#include <drawable.h>
#include <vector>

class Wolf : public Drawable {
	public:
		Wolf (Point loc)  { 
			location = loc;
			speed=30;
			viewDistance = 3;//Wolves can see 3 times their raidus away from themselves
		}

		void draw() {
#ifdef DEBUG
			printf("drawing at %g, %g\n", location.x, location.y);
#endif
			draw_texture("wolf", location, 10, 10);
		}		

		float getRadius() { return 4; }

		void chase(Point red, vector<Wolf>& wolvesVector) {
			moveVector.x=(red.x-location.x)*2;
			moveVector.y=(red.y-location.y)*2;
			for (int i=0; i<wolvesVector.size(); i++) {
				if (&wolvesVector[i] != this) {
					Point wolfPos = wolvesVector[i].getLocation();
					moveVector.addVector(location.angle(wolfPos),pow(-4.0/location.distance(wolfPos),3)/wolvesVector.size());
				}
			}
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
