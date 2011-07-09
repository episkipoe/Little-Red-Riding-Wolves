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
			speed=40;
			radius=20;//TODO:tweak this to fit sprite
			viewDistance=5;//Red can see 5 times her radius
		}

		void draw() {
			draw_texture("red", location, 10);
		}

		void resetLocation() {
			location.x = 80;
			location.y = -60;
			location.z = 0;
			lastLoc = location;
			onPath=false;
			beingChased=false;
			avoidanceList.clear();
			pathPosition=0;
		}

		void chase(vector<Wolf>& wolvesVector, Point housePos) {
			if (beingChased) { //beign chased. Run away from wolves, avoid objects, target house
				moveVector.x=0;
				moveVector.y=0;
				//first, factor in all the wolves
				for (size_t i=0; i<wolvesVector.size(); i++){
					Point wolfPos = wolvesVector[i].getLocation();
					moveVector.addVector(location.angle(wolfPos),-30.0/location.distance(wolfPos));
				}

				//next, factor in all the avoidance points
				for (size_t i=0; i<avoidanceList.size(); i++){
					moveVector.addVector(location.angle(avoidanceList[i]),pow(20.0/location.distance(avoidanceList[i]),3));
				}

				//finally, add the house pull
				moveVector.addVector(location.angle(housePos),pow(50.0/location.distance(housePos),2));

				moveVector.normalize();

			} else if (pathPoints.size() > 0) { //following the path

				if (location.distance(pathPoints[pathPosition])<15) pathPosition++; //advance the pathPoints list if at the corner
				if (pathPosition<pathPoints.size()) {
					follow(pathPoints[pathPosition]);
				} else {
					beingChased=true; //ran out of path points. Set to beingChased so red will still try to get to house
				}
			} else {
				follow(housePos);
			}

		}

		void addAvoidancePoint(Point p) {
			avoidanceList.push_back(p);
		}


		void follow(Point followPoint) {
			moveVector = followPoint + (location * -1);
			moveVector.normalize();
		}

		void beginChase() { beingChased=true; }

		void setOnPath(bool isOnPath) { onPath = isOnPath; }

		void update(float frameTime) {
			lastLoc = location;
			location = location + moveVector * speed * frameTime;
		}

private:
	Point moveVector;
	float speed;
	bool onPath;
	bool beingChased;
	vector<Point> avoidanceList;
	vector<Point> pathPoints;
	size_t pathPosition;
};

#endif
