#ifndef RED_H
#define RED_H

#include <drawable.h>
#include <images/textures.h>
#include <wolf/wolf.h>
#include <vector>
class Red : public Drawable {
	public:
		Red () {
			resetLocation();
			speed=1;
		}

		void draw() {
			int size = 2;
			glColor3f(1,0,0);
			glBegin(GL_TRIANGLES);
				glVertex3f(location.x-size, location.y-size, location.z);
				glVertex3f(location.x+size, location.y-size, location.z);
				glVertex3f(location.x, location.y+size, location.z);
			glEnd();
		}

		void resetLocation() {
			location.x = 40;
			location.y = location.z = 0;
			lastLoc = location;
		}

		void chase(vector<Wolf>& wolvesVector, Point housePos) {

			for (unsigned int i=0; i<wolvesVector.size(); i++){
				Point wolfPos = wolvesVector[i].getLocation();
				moveVector = moveVector + (location + wolfPos * -1);
			}

			moveVector = moveVector + (housePos + location * -1)*3;

			moveVector.normalize();

		}

		void follow(Point followPoint) {
			moveVector = followPoint + (location * -1);
			moveVector.normalize();
		}

		void update(float frameTime) {
			lastLoc = location;
			location = location + moveVector * speed * frameTime;
		}

private:
	Point moveVector;
	float speed;
};

#endif
