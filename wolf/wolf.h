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
			if(moveVector.x>=0.1) {
				draw_texture("wolf_right", location, 6, 6);
			} else {
				draw_texture("wolf_left", location, 6, 6);
			}
		}		

		float getRadius() { return 3; }

		void chase(Point red, vector<Wolf>& wolvesVector) {
			moveVector.x = 0;	
			moveVector.y = 0;
			moveVector.addVector(location.angle(red), 1.0);
			for (size_t i=0; i<wolvesVector.size(); i++) {
				if (&wolvesVector[i] != this) {
					Point wolfPos = wolvesVector[i].getLocation();
					if(location.distance(wolfPos) > 40) continue;
					moveVector.addVector(location.angle(wolfPos),pow(-15.0/location.distance(wolfPos),3));
				}
			}
			moveVector.normalize();
		}

		void setOnObstacle(bool on) { onObstacle = on; }

		void update(float frameTime) {
			lastLoc = location;
			float movementSpeed = (onObstacle ? speed * 0.6 : speed) ; 
			location = location + moveVector * movementSpeed * frameTime;
		}

protected:
	Point moveVector;
	float speed;
	bool onObstacle;
};

#endif
